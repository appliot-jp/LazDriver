/* phy_ml7404.c - ml7404 hardware interface for lazurite
 *
 * Copyright (c) 2017  Lapis Semiconductor Co.,Ltd
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>
 */


#ifdef LAZURITE_IDE
	#include <common.h>
//	#include <stddef.h>
//	#include <stdint.h>
		#include "serial.h"
#else
	#include <linux/stddef.h>
	#include "../common-lzpi.h"
	#include "../hwif/random-lzpi.h"
#endif

#include "../phy.h"
#include "phy_ml7404.h"
#include "../hwif/hal.h"
#include "../errno.h"
#include "../endian.h"
#include "../common_subghz.h"

#ifndef LAZURITE_IDE
#undef PHY_HWIF_NOTHAVE_TIMER_DI
#endif


/*
 --------------------------------------------------------------
													Define section
 --------------------------------------------------------------
 */
//#define GAUSSIAN_PROFILE
//#define BPSK_40kCPS
//#define BPSK_80kCPS
//#define POWER_10MW_LOW
//#define SERIAL_DEBUG
//#define CCA_DEBUG
#define BUFFER_SIZE 256
#define DEIVE_ID_ROHM  0x90
#define DEIVE_ID_LAPIS 0xD0

/*
I convert floating point numerical value into Q format fixed-point numerical value

 n: Floating point numerical value (when it is not so to be a fixation level, a floating point arithmetic library is linked)
 q: Decimal point position
 type: Model of the return value
 A return value: Fixed-point numerical value
*/
#define FIXQ(n, q, type) ((type)((n) * ((type)1 << (q)) + .5))

/*
I acquire integer region of the fixed-point numerical value
 * n: Fixed-point numerical value
 * q: Decimal point position
 * A return value: Integer part
 */
#define INTQ(n, q) ((n) >> (q))

/* headware interrupt */
#define HW_EVENT_ALL_MASK			0x000000	/* Interrupt all mask */
#define HW_EVENT_CLK_DONE			0x000001
#define HW_EVENT_VCO_CAL_DONE 0x000002
#define HW_EVENT_PLL_UNLOCK		0x000004
#define HW_EVENT_RF_STATUS		0x000008
#define HW_EVENT_FIFO_EMPTY		0x000010
#define HW_EVENT_FIFO_FULL		0x000020
#define HW_EVENT_WAKEUP				0x000040
#define HW_EVENT_CLK_CAL			0x000080

#define HW_EVENT_RX_DONE			0x000100
#define HW_EVENT_CRC_ERROR		0x000200
#define HW_EVENT_DIVERSITY		0x000400
#define HW_EVENT_RX_LEN_ERR		0x000800
#define HW_EVENT_RX_FIFO_ERR	0x001000
#define HW_EVENT_SYNC_WORD		0x002000
#define HW_EVENT_FIELD_CHECK	0x004000
#define HW_EVENT_SYNC_ERROR		0x008000

#define HW_EVENT_TX_DONE			0x010000
#define HW_EVENT_TX_FIFO_DONE 0x020000
#define HW_EVENT_CCA_DONE			0x040000
#define HW_EVENT_TX_LEN_ERR		0x080000
#define HW_EVENT_TX_FIFO_ERR	0x100000
#define HW_EVENT_CH_SAERCH		0x200000
#define HW_EVENT_GEM_TIMER1		0x400000
#define HW_EVENT_GEM_TIMER2		0x800000
#define HW_EVENT_TIMEOUT			0x000000

#define HW_INT_LEN						3

/* software interrupt */
#define SW_EVENT_SETUP	 1	/* Initialization */
#define SW_EVENT_RXSTART 2	/* Packet reception start */
#define SW_EVENT_RXSTOP  3	/* Packet reception stop */
#define SW_EVENT_TXSTART 4	/* Packet transmission start */
#define SW_EVENT_SLEEP	 5	/* Sleep */
#define SW_EVENT_WAKEUP  6	/* Wakeup */

#define PHY_REG_SET_TX_DONE_RX	 0x20
#define PHY_REG_SET_TX_DONE_OFF  0x03

#define UNIT_BAKOFF_PERIOD	300
#define DEFAUL_BAKOF				1000

#define PHY_MAX_BANK_SEL		11

#define PHY_FIFO_FULL_TRG		2
#define PHY_FIFO_EMPTY_TRG	    16	
#define PHY_FIFO_DATA_TRG		48
#define PHY_FIFO_DATA_READ	(PHY_FIFO_DATA_TRG - 1)
#define PHY_CRC_LEN					2
#define PHY_ADDR_TYPE6_LEN	9
#define PHY_DSSS_MULTI_CCA	3 // or 2
/*
 ---------------------------------------------------------------
												 Struct and Enum section
 ---------------------------------------------------------------
 */

static struct {
		volatile uint8_t lock;	// exclusion lock counter  
		uint8_t bank;						// back number
		uint8_t rdata[8];			// input buffer 
		uint8_t wdata[8];			// outpu buffer
		uint8_t rfifo[260];			// input buffer 
		uint8_t wfifo[260];			// outpu buffer
}reg = {
		0,		/* lock */
		0xff	/* bank */
};

static volatile struct {
		struct {											/* Timer-related parameter */
				void (*handler)(void);		/* Interrupt handler of the timer */
#ifdef PHY_HWIF_NOTHAVE_TIMER_DI
				enum {
						Disable=0,
						Enable
				} active;
				uint8_t call_count;				/* The handler summons number of times that interrupts it, and is prohibiting it */
#endif	/* #ifdef PHY_HWIF_NOTHAVE_TIMER_DI */
		} timer;
} hwif = {
		{
				NULL	/* timer.handler */
#ifdef PHY_HWIF_NOTHAVE_TIMER_DI
			, Disable,	/* timer.acvive */
				0					/* timer.call_count */
#endif	/* #ifdef PHY_HWIF_NOTHAVE_TIMER_DI */
		}
};



/* register setting fixed number */

typedef struct {
		uint8_t rate;								 /* rate setting */
		uint32_t freq[38];					 /* frequency setting */
		uint32_t chspc;							 /* bandwidth setting */
		uint32_t iffreq;						 /* IF frequency setting */ 
		uint32_t iffreq_cca;				 /* IF frequency setting (CCA) */
		uint16_t coef, ref;					 /* BPF setting */
		uint16_t coef_cca, ref_cca;  /* BPF setting (CCA) */
		uint16_t fdev;							 /* GFSK frequency shift setting */
		uint8_t reg1;								 /* Concealment of register setting */
		uint8_t div;								 /* diversity search setting */
} REGSET;


typedef enum{
		PHY_ST_FORCE_TRXOFF=0x03,
		PHY_ST_RXON=0x06,
		PHY_ST_TXON=0x09,
		PHY_ST_TRXOFF=0x08
} PHY_TRX_STATE;


typedef enum{
		PHY_FREQ_920_6,
		PHY_FREQ_920_7,
		PHY_FREQ_920_8,
		PHY_FREQ_920_9,
		PHY_FREQ_921_0 
} FIRST_CHANNEL;


static struct {
		uint16_t size;
		uint8_t modulation;
		uint8_t ctrl_reg;
		uint8_t sf_bit;
		uint8_t page;
		uint8_t cca_cnt;
}dsss_param;

static struct {
		uint16_t fifo_temp_len;
		uint8_t *fifo_temp_buf;
}fifo_param;

static uint8_t base_channel;
static uint8_t store_cca_sync_off;
static uint8_t pa_mode =	PHY_PA_MODE_NORMAL;
static uint8_t id_code = 0;
static uint8_t phy_cca_be;
static uint8_t channel_space[7][2]
					 = {
							{0x01,0x6C},		// 12.5kHz
						{0x02,0xD8},		// 25kHz
						{0x0B,0x61},		// 100kHz
						{0x11,0x11},		// 150kHz
						{0x16,0xC1},		// 200kHz
						{0x2D,0x83},		// 400kHz
						{0x2D,0x83}				// 5kHz
											 };

static const uint8_t cnv_regular_bank[PHY_MAX_BANK_SEL] = {
								0x11,		// bank0
								0x22,		// bank1
								0x44,		// bank2
								0x88,		// bank3
								0xff,		// bank4 done
								0xff,		// bank5 none
								0x33,		// bank6
								0x55,		// bank7
								0x66,		// bank8
								0x77,		// bank9
								0x99		// bank10
};


static PHY_PARAM phy;


/*
 ------------------------------------------------------------------
											Private function section
 ------------------------------------------------------------------
 */
#ifdef PHY_HWIF_NOTHAVE_TIMER_DI
static void timer_handler(void) {
		switch (hwif.timer.active) {
		case Enable:
				if (hwif.timer.handler != NULL)
						hwif.timer.handler();
				break;
		case Disable:
				++hwif.timer.call_count;
				break;
		}
}
#endif	/* #ifdef PHY_HWIF_NOTHAVE_TIMER_DI */
/******************************************************************************/
/*! @brief Register access of the ML7404 module
	 The reading and writing of the SPI bus
	 wdata[]: Data sequence to write in
	 size: The number of the data to read and write
	 rdata[]: Sequence to store the data which I began to read in
 ******************************************************************************/
static void ml7404_hwif_spi_transfer(const uint8_t *wdata, uint8_t *rdata, uint8_t size)
{
		uint8_t wsize, rsize;

		if(wdata[0]&REG_ADR_WRITE_BIT) {
						wsize = size;
						rsize = 0;
		}else{
						wsize = 1;
						rsize = size - wsize;
		}
		HAL_SPI_transfer(wdata, wsize, rdata, rsize);
}


/******************************************************************************/
/*! @brief change register back
 * valid 0 BANK0
 * valid 1 BANK1
 * valid 2 BANK2
 * valid 8 BANK0 + access enable
 * valid 9 BANK1 + access enable
 * valid 10 BANK2 + access enable
 * @exception ignore
 ******************************************************************************/
static void regbank(uint8_t bank_sel) {

		uint8_t bank;
		
		if(bank_sel <= PHY_MAX_BANK_SEL){
				bank = cnv_regular_bank[bank_sel];
		}else{
				bank = bank_sel;
		}

		if(bank == 0xff) {
				reg.lock = 0;
				reg.bank = bank;
		}else{
				if (bank != reg.bank) {
						reg.wdata[0] = (0x00<<1)|0x01, reg.wdata[1] = bank;
						ml7404_hwif_spi_transfer(reg.wdata, reg.rdata, 2);
						reg.bank = bank;
				}
		}
}


/******************************************************************************/
/*! @brief write register
 * bank: bank number
 * addr: write address
 * data: write data
 * size: data size
 ******************************************************************************/
static void reg_wr(uint8_t bank, uint8_t addr, const uint8_t *data, uint8_t size)
{
//	__DI();
		if (reg.lock++) {
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"REG LOCK ERR%s,%s,%d\n",__FILE__,__func__,reg.lock);
#endif
		}else{
				regbank(bank);
				reg.wdata[0] = (addr << 1) | 0x01;
				memcpy(reg.wdata + 1, data, size);
				ml7404_hwif_spi_transfer(reg.wdata, reg.rdata, size + 1);
		}
		--reg.lock;
/*
		while(1){
				if(reg.lock){
						__asm("nop");
				}else{
						break;
				}
		}
*/
//	__EI();
}


static void fifo_wr(uint8_t bank, uint8_t addr, uint8_t *p_addr, uint8_t *data, uint8_t size)
{
//	__DI();
		uint8_t *p_header = data - 1;

		if (reg.lock++) {
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"REG LOCK ERR%s,%s,%d\n",__FILE__,__func__,reg.lock);
#endif
		}else{
				regbank(bank);
				*p_header = (addr << 1) | 0x01;
				ml7404_hwif_spi_transfer(p_header, reg.rdata, size + 1);
		}
		--reg.lock;
//	__EI();
}


/******************************************************************************/
/*! @brief read register
 * bank: bank number
 * addr: read address
 * data: store readind data
 * size: data size
 ******************************************************************************/
static void reg_rd(uint8_t bank, uint8_t addr, uint8_t *data, uint8_t size)
{
//	__DI();
		if (reg.lock++) {
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"REG LOCK ERR%s,%s,%d\n",__FILE__,__func__,reg.lock);
#endif
		}else{
				regbank(bank);
				reg.rdata[0] = (addr << 1) | 0x00;
				memset(reg.rdata + 1, 0xff, size);
				ml7404_hwif_spi_transfer(reg.rdata, reg.rdata, size + 1);
				memcpy(data, reg.rdata, size);
		}
		--reg.lock;
/*
		while(1){
				if(reg.lock){
						__asm("nop");
				}else{
						break;
				}
		}
*/
//	__EI();
}

/*
 *	*p_addr:	write buffer pointer
 *	*data:		w
 */
static void fifo_rd(uint8_t bank, uint8_t addr, uint8_t *p_addr, uint8_t *data, uint8_t size)
{
//	__DI();
		uint8_t *p_header = p_addr - 1;

		if (reg.lock++) {
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"REG LOCK ERR%s,%s,%d\n",__FILE__,__func__,reg.lock);
#endif
		}else{
				regbank(bank);
				*p_header = (addr << 1) | 0x00;
				ml7404_hwif_spi_transfer(p_header, data, size + 1);
		}
		--reg.lock;
//	__EI();
}


static void phy_mesg(void)
{
		uint8_t reg_data[4];
#ifndef LAZURITE_IDE
		if(module_test & MODE_PHY_DEBUG) {

				reg_rd(REG_ADR_INT_EN_GRP1, reg_data, 3);
				printk(KERN_INFO"DEBUG PHY: %s,%s,EN1:%x,EN2:%x,EN3:%x\n",__FILE__,__func__,reg_data[0],reg_data[1],reg_data[2]);
				reg_rd(REG_ADR_INT_SOURCE_GRP1, reg_data, 3);
				printk(KERN_INFO"DEBUG PHY: %s,%s,IT1:%x,IT2:%x,IT3:%x\n",__FILE__,__func__,reg_data[0],reg_data[1],reg_data[2]);
				reg_rd(REG_ADR_RF_STATUS, reg_data, 1);
				printk(KERN_INFO"DEBUG PHY: %s,%s, RF_STATUS:%x\n",__FILE__,__func__,reg_data[0]);
		}
#else
		reg_rd(REG_ADR_INT_EN_GRP1, reg_data, HW_INT_LEN);
		reg_rd(REG_ADR_INT_SOURCE_GRP1, reg_data, HW_INT_LEN);
		reg_rd(REG_ADR_RF_STATUS, reg_data, 1);
#endif
}


/******************************************************************************/
/*! @brief Enable interrupt / Diseable interrupt
 * @detail Original function was REG_INTEN
 ******************************************************************************/
static void phy_inten(uint32_t inten)
{
		uint8_t reg_data[HW_INT_LEN];
		reg_data[0] = (uint8_t)((inten) >>	0);
		reg_data[1] = (uint8_t)((inten) >>	8);
		reg_data[2] = (uint8_t)((inten) >> 16);
		reg_wr(REG_ADR_INT_EN_GRP1, reg_data, HW_INT_LEN);
}


/******************************************************************************/
/*! @brief Clear interrupt 
 * @detail Original function was REG_INTCLR
 ******************************************************************************/
static void phy_intclr(uint32_t intclr)
{
		uint8_t reg_data[HW_INT_LEN];
		reg_data[0] = ~(uint8_t)((intclr) >>	0);
		reg_data[1] = ~(uint8_t)((intclr) >>	8);
		reg_data[2] = ~(uint8_t)((intclr) >> 16);
		reg_wr(REG_ADR_INT_SOURCE_GRP1, reg_data, HW_INT_LEN);
}


/******************************************************************************/
/*! @brief Clear interrupt 
 * @detail Original function was REG_DETECTION
 ******************************************************************************/
static bool phy_int_detection(uint32_t status)
{
		uint8_t reg_data[HW_INT_LEN];
		reg_rd(REG_ADR_INT_SOURCE_GRP1, reg_data, HW_INT_LEN);
		if (reg_data[0] & (uint8_t)((status) >>  0)) return true;
		if (reg_data[1] & (uint8_t)((status) >>  8)) return true;
		if (reg_data[2] & (uint8_t)((status) >> 16)) return true;
		return false;
}


static void phy_set_trx_state(PHY_TRX_STATE state) {
		uint8_t set_data,get_data,i;
		
		set_data = state;
		// @issue : provisional for REG LOCK
		for(i=0;i < 3;i++){
				reg_wr(REG_ADR_RF_STATUS, &set_data, 1);
				HAL_delayMicroseconds(200);
				reg_rd(REG_ADR_RF_STATUS, &get_data, 1);
				if(set_data == (get_data&0x0F)) break;
		}
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}


static void phy_rst(void)
{
		uint8_t reg_data;
		reg_data = 0x88;
		reg_wr(REG_ADR_RST_SET, &reg_data, 1);
}


static void vco_cal(void) {

		uint8_t reg_data;
		reg_data=0x01;
		reg_wr(REG_ADR_VCO_CAL_START, &reg_data,1);
	do {
				HAL_delayMicroseconds(500);
		} while (phy_int_detection(HW_EVENT_VCO_CAL_DONE) == false);
		phy_intclr(HW_EVENT_VCO_CAL_DONE);

#ifdef LAZURITE_IDE
#if 0
		reg_rd(REG_ADR_VCO_CAL, &reg_data, 1),
	Serial.print("VCO_CAL(B0 0x6E):0x");
	Serial.println_long((long)reg_data, HEX);	

		reg_rd(REG_ADR_VCO_CAL_MIN, &reg_data, 1),
	Serial.print("VCAL_MIN(B1 0x52):0x");
	Serial.println_long((long)reg_data, HEX);	

		reg_rd(REG_ADR_VCO_CAL_MAX, &reg_data, 1),
	Serial.print("VCAL_MAX(B1 0x53):0x");
	Serial.println_long((long)reg_data, HEX);	
#endif
#endif


}


static void phy_backoffTimer(void){

	uint16_t cca_wait;

	cca_wait = (rand()&phy_cca_be) * UNIT_BAKOFF_PERIOD;
	if (!cca_wait) cca_wait = DEFAUL_BAKOF;
	HAL_delayMicroseconds(cca_wait);
}


static void phy_set_zero_channel_req(FIRST_CHANNEL freq){

		uint8_t reg_data[4];

		reg_data[0] = 0x19; reg_data[1] = 0x09;

		switch (freq) {
		case PHY_FREQ_920_6:
				reg_data[2] = 0x27; reg_data[3] = 0xD2; // 920.6MHz
				break;
		case PHY_FREQ_920_7:
				reg_data[2] = 0x33; reg_data[3] = 0x33; // 920.7MHz
				break;
		case PHY_FREQ_920_8:
				reg_data[2] = 0x3E; reg_data[3] = 0x93; // 920.8MHz
				break;
		case PHY_FREQ_920_9:
				reg_data[2] = 0x49; reg_data[3] = 0xF4; // 920.9MHz
				break;
		case PHY_FREQ_921_0:
				reg_data[2] = 0x55; reg_data[3] = 0x55; // 921.0MHz
				break;
		default:
				reg_data[2] = 0x33; reg_data[3] = 0x33; // 920.7MHz
				break;
		}
		reg_wr(REG_ADR_TXFREQ_I,				reg_data, 4);
		reg_wr(REG_ADR_RXFREQ_I,				reg_data, 4);
}

/*
 -------------------------------------------------------------
										Public interrupt section
 -------------------------------------------------------------
 */
/******************************************************************************/
/*! @brief Interrupt handler registration of the ML7404 module
 * @detail Handler of the interrupt that SINTN terminal generates at 'L' level
 ******************************************************************************/
int phy_sint_handler(void (*func)(void))
{
		int status = -1;
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
		HAL_GPIO_setInterrupt(func);
		status = 0;
		return status;
}

/******************************************************************************/
/*! @brief Enable interrupt
 * @detail Interrupt permission delay cancellation of the ML7404 module
 ******************************************************************************/
int phy_sint_ei(void)
{
		int status = -1;
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
		HAL_GPIO_enableInterrupt();
		status = 0;
		return status;
}

/******************************************************************************/
/*! @brief Disable interrupt
 * @detail The delay that interrupt of the ML7404 module is prohibited in it.
 *				 I delay whether it is admitted again until I am cleared.
 ******************************************************************************/
int phy_sint_di(void)
{
		int status = -1;
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
		HAL_GPIO_disableInterrupt();
		status = 0;
		return status;
}

/******************************************************************************/
/*! @brief Time-out interrupt handler registration
 * @detail func: Interrupt handler function
 ******************************************************************************/
int phy_timer_handler(void (*func)(void))
{
		int status = -1;
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
		hwif.timer.handler = func;
		status = 0;
		return status;
}

/******************************************************************************/
/*! @brief Enable time-out interrupt
 * @detail func: The delay that time-out interrupt is prohibited in it.
					 I delay whether it is admitted again until I am cleared.
 ******************************************************************************/
int phy_timer_ei(void)
{
		int status = -1;
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
#ifdef PHY_HWIF_NOTHAVE_TIMER_DI
		switch (hwif.timer.active) {
		case Disable:
				hwif.timer.active = Enable;
				if (hwif.timer.call_count) {
						hwif.timer.call_count = 0;
						if (hwif.timer.handler != NULL)
								hwif.timer.handler();
				}
				break;
		case Enable:
				break;
		}
#else  /* #ifdef PHY_HWIF_NOTHAVE_TIMER_DI */
//			 HAL_TIMER_enableInterrupt();
#endif	/* #ifdef PHY_HWIF_NOTHAVE_TIMER_DI */
		status = 0;
		return status;
}

/******************************************************************************/
/*! @brief Disable time-out interrupt
 * @detail The delay that time-out interrupt is prohibited in it.
 I delay whether it is admitted again until I am cleared.
 ******************************************************************************/
int phy_timer_di(void)
{
		int status = -1;
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
#ifdef PHY_HWIF_NOTHAVE_TIMER_DI
		switch (hwif.timer.active) {
		case Disable:
				break;
		case Enable:
				hwif.timer.active = Disable;
				break;
		}
#else  /** #ifdef PHY_HWIF_NOTHAVE_TIMER_DI */
//		HAL_TIMER_disableInterrupt();
#endif	/* #ifdef PHY_HWIF_NOTHAVE_TIMER_DI */
		status = 0;
		return status;
}

/******************************************************************************/
/*! @brief time-out interrupt count start
 * @detail I produce an interrupt after progress at designation time
 * msec: Time before producing a time-out interrupt (appoint it by a msec unit)
 ******************************************************************************/
int phy_timer_start(uint16_t msec)
{
		int status = -1;
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
#ifdef PHY_HWIF_NOTHAVE_TIMER_DI
		HAL_TIMER_start(msec, timer_handler);
#else  /* #ifdef PHY_HWIF_NOTHAVE_TIMER_DI */
		HAL_TIMER_start(msec, hwif.timer.handler);
#endif	/* #ifdef PHY_HWIF_NOTHAVE_TIMER_DI */
		status = 0;
		return status;
}

/******************************************************************************/
/*! @brief time-out interrupt count start
 * @detail I produce an interrupt after progress at designation time
 * msec: Time before producing a time-out interrupt (appoint it by a msec unit)
 ******************************************************************************/
int phy_timer_stop(void)
{
		int status = -1;
		HAL_TIMER_stop();
		status = 0;
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
		return status;
}

/******************************************************************************/
/*! @brief Timer tick
 * @detail The acquisition of the elapsed time timer.
					 I acquire an elapsed time from neighboring device initialization.
					 msec: The elapsed time when acquired it (msec unit).
 ******************************************************************************/
int phy_timer_tick(uint32_t *msec)
{
		int status = -1;
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
		HAL_TIMER_getTick(msec);
		status = 0;
		return status;
}

/*
 -------------------------------------------------------------
										Public function section
 -------------------------------------------------------------
 */
void phy_wait_phy_event(void)
{
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
		HAL_wait_event(HAL_PHY_EVENT);
}


int phy_wait_mac_event(void)
{
		int status;
	status = HAL_wait_event(HAL_MAC_EVENT);
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
		return status;
}


void phy_wakeup_phy_event(void)
{
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
		HAL_wakeup_event(HAL_PHY_EVENT);
}


void phy_wakeup_mac_event(void)
{
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
		HAL_wakeup_event(HAL_MAC_EVENT);
}

void phy_config(uint8_t mod, uint8_t sf, uint16_t size)
{
	dsss_param.modulation = mod;
		if (sf == 0x08) {
			dsss_param.sf_bit = 0x03;		 // 8:0x03
		}else{
			dsss_param.sf_bit = sf >> 5; // 64:0x02,32:0x01,16:0x00
		}
		dsss_param.size = size + PHY_CRC_LEN;

		switch(dsss_param.size) {
	case 16:
		dsss_param.ctrl_reg = PHY_DSSS_SIZE_16;
		break;
	case 24:
		dsss_param.ctrl_reg = PHY_DSSS_SIZE_24;
		break;
	case 32:
		dsss_param.ctrl_reg = PHY_DSSS_SIZE_32;
		break;
	default:
		dsss_param.ctrl_reg = PHY_DSSS_SIZE_FREE;
		break;
	}
#if defined(LAZURITE_IDE)
    #if defined(SERIAL_DEBUG)
		Serial.print("SF:");
		Serial.println_long((long)dsss_param.sf_bit,HEX);
		Serial.print("DSSS_SIZE:");
		Serial.println_long((long)dsss_param.size,HEX);
    #endif
#else
	if(module_test & MODE_PHY_DEBUG) {
				printk(KERN_INFO"MODE:0x%x, PSDU:0x%x, DSSS_CTRL:0x%x, SF:0x%x, %s,%s,MODE\n",
								dsss_param.modulation,dsss_param.size,dsss_param.ctrl_reg,dsss_param.sf_bit,
								__FILE__,__func__);
		}
#endif
}

/******************************************************************************/
/*! @brief Register setting of phy
 * @detail 
	 Channel setting
	 Bandwidth setting
	 Communication rate setting
	 Transmission output setting
	 Setting peculiar to other devices
	 awaiting first clock stability and the last calibration practice are unnecessary
 ******************************************************************************/
int phy_setup(uint8_t page,uint8_t ch, uint8_t txPower,uint8_t antsw)
//int phy_setup(uint8_t page,uint8_t ch)
{
		uint16_t address;

		int status = -1;
		uint8_t reg_data[10];
	uint8_t i;

#ifdef POWER_10MW_LOW
		#ifdef BPSK_40kCPS
				static const uint8_t dsss_40kcps_profile[] =
		// BPSK_40kcps Power0xC0(b2_0x19=0x)
				{0x10, 0x04, 0x00, 0x10, 0x12, 0x12, 0x21, 0x34, 0x11, 0x23, 0x22, 0x22, 0x23, 0x34, 0x32, 0x46,
				 0x44, 0x64, 0x35, 0x56, 0x35, 0x45, 0x44, 0x47, 0x84, 0x83, 0x55, 0x46, 0x56, 0x24, 0x00, 0x00,
				 0x00, 0x00, 0x33, 0x65, 0x64, 0x85, 0x75, 0xA8, 0x84, 0x45, 0x44, 0x43, 0x34, 0x54, 0x43, 0x55,
				 0x53, 0x24, 0x22, 0x03, 0x34, 0x23, 0x11, 0x22, 0x11, 0x21, 0x21, 0x42, 0x00, 0x00, 0x00, 0x63,
				 0x03, 0x02, 0x00, 0x00, 0x04, 0x01};
		#endif
				static const uint8_t dsss_50kcps_profile[] =
		// BPSK_50kcps Power0xC0(b2_0x19=0x)
				{0x10, 0x03, 0x00, 0x20, 0x11, 0x12, 0x21, 0x33, 0x12, 0x31, 0x22, 0x12, 0x32, 0x23, 0x14, 0x33,
				 0x45, 0x44, 0x44, 0x46, 0x46, 0x44, 0x34, 0x44, 0x64, 0x74, 0x35, 0x48, 0x45, 0x74, 0x25, 0x14,
				 0x00, 0x00, 0x20, 0x54, 0x45, 0x56, 0x76, 0x75, 0x86, 0x66, 0x45, 0x34, 0x43, 0x34, 0x43, 0x43,
				 0x44, 0x54, 0x35, 0x22, 0x22, 0x12, 0x33, 0x32, 0x11, 0x21, 0x21, 0x11, 0x11, 0x32, 0x11, 0x63,
				 0x03, 0x02, 0x00, 0x00, 0x03, 0x01};
		#ifdef BPSK_80kCPS
				static const uint8_t dsss_80kcps_profile[] =
		// BPSK_80kcps Power0xC0(b2_0x19=0x)
				{0x10, 0x02, 0x00, 0x20, 0x21, 0x11, 0x32, 0x33, 0x11, 0x23, 0x13, 0x22, 0x33, 0x33, 0x32, 0x35,
				 0x55, 0x44, 0x47, 0x46, 0x45, 0x43, 0x54, 0x56, 0x56, 0x84, 0x64, 0x54, 0x47, 0x24, 0x00, 0x00,
				 0x00, 0x00, 0x20, 0x54, 0x55, 0x66, 0x67, 0x77, 0x77, 0x57, 0x45, 0x43, 0x34, 0x44, 0x43, 0x54,
				 0x64, 0x34, 0x23, 0x22, 0x22, 0x33, 0x13, 0x11, 0x12, 0x12, 0x21, 0x31, 0x13, 0x00, 0x00, 0x63,
				 0x00, 0x02, 0x40, 0x00, 0x02, 0x01};
		#endif
#else // POWER_10MW_LOW
		#ifdef BPSK_40kCPS
				static const uint8_t dsss_40kcps_profile[] =
				{0x10, 0x04, 0x00, 0x10, 0x12, 0x22, 0x21, 0x34, 0x21, 0x23, 0x22, 0x32, 0x23, 0x34, 0x33, 0x56,
				 0x44, 0x65, 0x45, 0x56, 0x37, 0x55, 0x44, 0x48, 0x85, 0x93, 0x56, 0x56, 0x66, 0x24, 0x00, 0x00,
				 0x00, 0x00, 0x33, 0x66, 0x65, 0x95, 0x76, 0xA9, 0x85, 0x46, 0x64, 0x43, 0x35, 0x54, 0x44, 0x56,
				 0x63, 0x24, 0x22, 0x13, 0x34, 0x23, 0x12, 0x22, 0x11, 0x21, 0x21, 0x43, 0x00, 0x00, 0x00, 0x63,
				 0x03, 0x02, 0x00, 0x00, 0x04, 0x01};
		#endif
				static const uint8_t dsss_50kcps_profile[] =
				{0x10, 0x03, 0x00, 0x20, 0x11, 0x13, 0x21, 0x33, 0x12, 0x32, 0x22, 0x12, 0x33, 0x23, 0x24, 0x33,
				 0x55, 0x44, 0x45, 0x56, 0x66, 0x44, 0x44, 0x44, 0x65, 0x84, 0x45, 0x48, 0x46, 0x75, 0x35, 0x14,
				 0x00, 0x00, 0x20, 0x55, 0x55, 0x56, 0x77, 0x76, 0x87, 0x67, 0x46, 0x54, 0x43, 0x44, 0x43, 0x53,
				 0x44, 0x55, 0x36, 0x22, 0x22, 0x13, 0x33, 0x32, 0x12, 0x21, 0x21, 0x11, 0x11, 0x33, 0x11, 0x63,
				 0x03, 0x02, 0x00, 0x00, 0x03, 0x01};
		#ifdef BPSK_80kCPS
				static const uint8_t dsss_80kcps_profile[] =
				#ifdef GAUSSIAN_PROFILE
				{0x30, 0x02, 0x00, 0x20, 0x12, 0x12, 0x22, 0x22, 0x22, 0x22, 0x33, 0x43, 0x43, 0x44, 0x34, 0x55,
				 0x65, 0x46, 0x67, 0x85, 0x66, 0x47, 0x66, 0x65, 0x66, 0x77, 0x58, 0x47, 0x53, 0x00, 0x00, 0x00,
				 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC3,
				 0x00, 0x02, 0x00, 0x00, 0x02, 0x01};
				#else
				{0x10, 0x02, 0x00, 0x20, 0x21, 0x12, 0x32, 0x33, 0x21, 0x23, 0x13, 0x32, 0x33, 0x33, 0x33, 0x45,
				 0x55, 0x45, 0x57, 0x66, 0x45, 0x44, 0x54, 0x57, 0x57, 0x85, 0x65, 0x64, 0x47, 0x25, 0x00, 0x00,
				 0x00, 0x00, 0x20, 0x55, 0x65, 0x76, 0x77, 0x87, 0x87, 0x67, 0x45, 0x45, 0x44, 0x44, 0x53, 0x54,
				 0x65, 0x35, 0x23, 0x22, 0x23, 0x33, 0x23, 0x11, 0x12, 0x12, 0x21, 0x41, 0x13, 0x00, 0x00, 0x63,
				 0x00, 0x02, 0x40, 0x00, 0x02, 0x01};
				#endif
		#endif
#endif // POWER_10MW_LOW
	static const uint8_t dsss_100kcps_profile[] =
		{0x10, 0x02, 0x00, 0x20, 0x22, 0x22, 0x44, 0x32, 0x33, 0x31, 0x34, 0x35, 0x64, 0x65, 0x66, 0x58,
		 0x78, 0x65, 0x55, 0x69, 0x59, 0x8A, 0x66, 0x58, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		 0x00, 0x00, 0x52, 0x67, 0x88, 0x8A, 0x9A, 0x8A, 0x66, 0x46, 0x46, 0x46, 0x76, 0x66, 0x35, 0x32,
		 0x43, 0x43, 0x13, 0x22, 0x12, 0x22, 0x53, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63,
		 0x03, 0x02, 0x00, 0x00, 0x02, 0x01};

	static const uint8_t dsss_200kbps_profile[] =
		{0x10, 0x01, 0x00, 0x20, 0x22, 0x22, 0x32, 0x22, 0x72, 0x65, 0x56, 0x76, 0x85, 0xA7, 0x99, 0x89,
		 0x48, 0x68, 0x77, 0x58, 0x68, 0x33, 0x23, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		 0x00, 0x00, 0x30, 0x34, 0x31, 0x33, 0x53, 0x84, 0x77, 0x86, 0x84, 0x98, 0x99, 0x7A, 0x58, 0x67,
		 0x65, 0x56, 0x27, 0x22, 0x23, 0x22, 0x22, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63,
		 0x03, 0x02, 0x00, 0x00, 0x01, 0x03};

	static const uint8_t sigfox_profile[] =
		{0x71, 0x74, 0x00, 0x20, 0x11, 0x11, 0x12, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x12, 0x11,
		 0x12, 0x11, 0x12, 0x21, 0x11, 0x22, 0x23, 0x23, 0x13, 0x23, 0x12, 0x12, 0x22, 0x32, 0x33, 0x23,
		 0x23, 0x22, 0x22, 0x32, 0x23, 0x24, 0x22, 0x32, 0x33, 0x23, 0x33, 0x33, 0x33, 0x33, 0x33, 0x32,
		 0x22, 0x23, 0x22, 0x32, 0x22, 0x22, 0x33, 0x03, 0x12, 0x22, 0x12, 0x22, 0x12, 0x11, 0x00, 0x00};

	dsss_param.page = page;

		phy_set_trx_state(PHY_ST_TRXOFF);

		phy_rst();

		phy_inten(HW_EVENT_ALL_MASK);
		phy_intclr(~(HW_EVENT_ALL_MASK));

#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s DRATE:%d\n",__FILE__,__func__,dsss_param.page);
#endif

		reg_data[0]=0x00; reg_wr(REG_ADR_SPI_EXT_PA_CTRL,			reg_data, 1);
		reg_data[0]=0xC3; reg_wr(REG_ADR_CLK_SET2,						reg_data, 1);		// TCXO:0xC3, XTAL:0x93
		reg_data[0]=0x02; reg_wr(REG_ADR_2DIV_CNTRL,					reg_data, 1);		// 2DIV_CTRL
		reg_data[0]=0x00; reg_wr(REG_ADR_GPIO1_CTRL,					reg_data, 1);		// EXT_CLK_OUT=OFF
		reg_rd(REG_ADR_ID_CODE, reg_data, 1),		id_code = reg_data[0];

/******************************************************************************
	Trimming parameters setting
	(BPF_OFFSET, VBG, IPTAT, IBG, RSSI_SLOPE,  RSSI_DC, PA_BIAS1, PA_BIAS2, PA_BIAS3, MAG_ADJ, PHASE_ADJ) combined data
 ******************************************************************************/
// non
/**************************************
		Fixed Parameters
 **************************************/
		//--------------------------
		// External PA(1W) ON
		//--------------------------

		if (pa_mode ==	PHY_PA_MODE_EXTERNAL){
				reg_data[0] = 0x07, reg_wr(REG_ADR_MON_CTRL,				 reg_data, 1);	// DMON=> SLEEP
				reg_data[0] = 0x86, reg_wr(REG_ADR_GPIO1_CTRL,			 reg_data, 1);	// GPIO1=>DMON
				reg_data[0] = 0x01, reg_wr(REG_ADR_GPIO2_CTRL,			 reg_data, 1);	// GPIO2=>TRX_SW
				reg_data[0] = 0x30, reg_wr(REG_ADR_GPIO3_CTRL,			 reg_data, 1);	// GPIO3=>High
		}

		//------------------------------------------------------------------------------
		//B2 0x24		 VCO_I_CTRL
		//------------------------------------------------------------------------------
		reg_data[0] = 0x0C, reg_wr(REG_ADR_VCO_I_CTRL,				 reg_data, 1);
		//------------------------------------------------------------------------------
		//B2 0x1C		 PLL_CP_ADJ
		//------------------------------------------------------------------------------
		reg_data[0] = 0x33, reg_wr(REG_ADR_PLL_CP_ADJ2,					reg_data, 1);
		reg_data[0] = 0x33, reg_wr(REG_ADR_PLL_CP_ADJ,					reg_data, 1);
		//------------------------------------------------------------------------------
		//B2 0x2A		 IFAMP_GAIN
		//------------------------------------------------------------------------------
		reg_data[0] = 0x1F, reg_wr(REG_ADR_IFAMP_GAIN,					reg_data, 1);
		//------------------------------------------------------------------------------
		//0x32		DSM_PHASE
		//------------------------------------------------------------------------------
		reg_data[0] = 0x4C, reg_wr(REG_ADR_RF_7345_RSV2,					reg_data, 1);
		//------------------------------------------------------------------------------
		//0x38		VBG_TRIM (注意: 基板毎に個別調整必要!!!) sendln 'WREG 38 19' ; REG_CORE=1.6V
		//------------------------------------------------------------------------------
		reg_data[0] = 0x19, reg_wr(REG_ADR_BIAS_T_TRIM,						reg_data, 1);

		reg_data[0] = 0x6E, reg_wr(REG_ADR_PA_CURR,							reg_data, 1);
		reg_data[0] = 0x5F, reg_wr(REG_ADR_LNA_RESERVE,					reg_data, 1);
		reg_data[0] = 0xA7, reg_wr(REG_ADR_PAREG_OLR2,					reg_data, 1);		// RFRX_RSV
//	reg_data[0] = 0x3E, reg_wr(REG_ADR_REGULATOR_CTRL,			reg_data, 1);

		reg_data[0] = 0x83; reg_wr(REG_ADR_ED_CNTRL, reg_data, 1);

		/* channel setting */
		base_channel = ch - 24;

		/* channel space setting */
		reg_data[0] = channel_space[PHY_CHSPACE_200K][0];
		reg_data[1] = channel_space[PHY_CHSPACE_200K][1];
												reg_wr(REG_ADR_CH_SPACE_H,					reg_data, 2);

		/**************************************
				SIGFOX uplink
		 **************************************/
	if (dsss_param.modulation == PHY_MODULATION_SIGFOX) {

#ifdef LAZURITE_IDE
				Serial.println("--------- RF MODE: DSSS 100bps for SIGFOX --------");
#endif
			reg_data[0] = 0x20, reg_wr(REG_ADR_CCA_LEVEL,						 reg_data, 1);

		reg_data[0] = 0x00, reg_wr(REG_ADR_PLL_DIV_SET,						 reg_data, 1);

				/* frequency setting */
				phy_set_zero_channel_req(PHY_FREQ_920_6);

				/*
				;------------------------------------------------------------------------------
				;0x1B-1E TXFREQ_I/FH/FM/FL
				;------------------------------------------------------------------------------
						sendln 'BWREG 1B 04 19 0A 4F A4' ; 923.2MHz
				;------------------------------------------------------------------------------
				;0x1F-22 RXFREQ_I/FH/FM/FL
				;------------------------------------------------------------------------------
						sendln 'BWREG 1F 04 19 09 DD DD' ; 922.2MHz
				*/
				//0x4d-51 VCAL RANGE	Frf_MIN:921.7(922.2-0.4)/Fref:36/1.5MHzCAL Range
				reg_data[0] = 0x19; reg_data[1] = 0x09; reg_data[2] = 0xB0; reg_data[3] = 0x5B; reg_data[4] = 0x02;
														reg_wr(REG_ADR_VCO_CAL_MIN_I,				 reg_data, 4);

				// Modulation Setting		BPSK=0x01, FSK=0x00
				// Uplink(BPSK) Downlink(FSK)
		reg_data[0] = 0x01, reg_wr(REG_ADR_MOD_CTRL,						reg_data, 1);
		reg_data[0] = 0x00, reg_wr(REG_ADR_DSSS_CTRL,						reg_data, 1);
		reg_data[0] = 0x00, reg_wr(REG_ADR_FEC_ENC_CTRL,				reg_data, 1);
		reg_data[0] = 0x00, reg_wr(REG_ADR_FEC_DEC_CTRL,				reg_data, 1);
		reg_data[0] = 0x03, reg_wr(REG_ADR_PKT_CTRL1,						reg_data, 1);
		reg_data[0] = 0x1C, reg_wr(REG_ADR_PKT_CTRL2,						reg_data, 1);
		reg_data[0] = 0x57, reg_wr(REG_ADR_CHFIL_BW,						reg_data, 1);		// 2.3kHz
		reg_data[0] = 0x15, reg_wr(REG_ADR_DC_FIL_ADJ,					reg_data, 1);
		reg_data[0] = 0x0A, reg_wr(REG_ADR_IQ_DEC_GAIN,					reg_data, 1);
		reg_data[0] = 0x33, reg_wr(REG_ADR_IF_FREQ,							reg_data, 1);		// 112.5kHz
		reg_data[0] = 0x01, reg_wr(REG_ADR_CHFIL_BW_CCA,				reg_data, 1);		// 200kHz
		reg_data[0] = 0x00, reg_wr(REG_ADR_DC_FIL_ADJ2,					reg_data, 1);
			reg_data[0] = 0x0E, reg_wr(REG_ADR_RSSI_MAG_ADJ,				reg_data, 1);
		reg_data[0] = 0x18, reg_wr(REG_ADR_DEC_GAIN_CCA,				reg_data, 1);
				reg_data[0] = 0x5B, reg_wr(REG_ADR_RSSI_ADJ2,						reg_data, 1);
				reg_data[0] = 0x8C, reg_data[1] = 0x3C, reg_data[2] = 0x8C;
				reg_data[3] = 0x3C, reg_data[4] = 0x8C; reg_data[5] = 0x3C;
				reg_data[6] = 0x2F, reg_data[7] = 0x55, reg_data[8] = 0x7F;
														reg_wr(REG_ADR_GAIN_HHTH,						reg_data, 9);
				//0x02-03 TX_RATE1/2 0.1kbps, 0x04-06 RX_RATE1/2 0.6kbps
		reg_data[0] = 0x8C; reg_data[1] = 0xA0; reg_data[2] = 0x00;
				reg_data[3] = 0xF0; reg_data[4] = 0x7D;
								reg_wr(REG_ADR_TX_RATE_H,						reg_data, 5);
//			reg_data[0] = 0x8F, reg_wr(REG_ADR_AFC_GC_CTRL,					reg_data, 1); // Nomal
		reg_data[0] = 0x8E, reg_wr(REG_ADR_AFC_GC_CTRL,					reg_data, 1); // CCA only
				// GFSK_DEV_H/L
		reg_data[0] = 0x00; reg_data[1] = 0x1D;
							reg_wr(REG_ADR_GFSK_DEV_H,					reg_data, 2);
				// 0x57-5F DEMOD_SET1-9
		reg_data[0] = 0x04; reg_data[1] = 0x01; reg_data[2] = 0x10;
		reg_data[3] = 0x00; reg_data[4] = 0x00; reg_data[5] = 0x1D;
		reg_data[6] = 0x02; reg_data[7] = 0x05; reg_data[8] = 0x13;
							reg_wr(REG_ADR_DEMOD_SET1,					reg_data, 9);
		reg_data[0] = 0x0C, reg_wr(REG_ADR_DEMOD_SET10,					reg_data, 1);
		reg_data[0] = 0x0C, reg_wr(REG_ADR_DEMOD_SET10,					reg_data, 1);
		reg_data[0] = 0x54, reg_wr(REG_ADR_DEMSET25,						reg_data, 1);
		reg_data[0] = 0x33, reg_wr(REG_ADR_DIF_SET0,						reg_data, 1);
		reg_data[0] = 0x04; reg_data[1] = 0x3F; reg_data[2] = 0x3F;
							reg_wr(REG_ADR_RAMP_CTRL1,					reg_data, 3);
		reg_data[0] = 0x01, reg_wr(REG_ADR_BPSK_PLL_CTRL,				reg_data, 1); // PLL_CTRL/CLK450kHz
		reg_data[0] = 0x03, reg_data[1] = 0x28;
														reg_wr(REG_ADR_BPSK_P_START_H,			reg_data, 1);
		reg_data[0] = 0x00, reg_data[1] = 0xE0;
														reg_wr(REG_ADR_BPSK_P_HOLD_H,				reg_data, 1);
				reg_data[0] = 0x77; reg_wr(REG_ADR_RSSI_STABLE_TIME,		reg_data, 1);
				for (i = 0; i < sizeof(sigfox_profile); i++) {
						reg_data[0] = sigfox_profile[i];
						reg_wr(REG_ADR_BPSK_STEP_CTRL+i,		 reg_data, 1);
				}
		/**************************************
				DSSS
		 **************************************/
		} else if (dsss_param.modulation == PHY_MODULATION_DSSS) {

				// Telec: 0x20
			reg_data[0] = 0x30, reg_wr(REG_ADR_CCA_LEVEL,						 reg_data, 1);

				// 0x67/68 PA_REG_ADJ_H/L 10dBm
#ifdef POWER_10MW_LOW
				reg_data[0] = 0x00; reg_data[1] = 0xC0;
#else
				reg_data[0] = 0x00; reg_data[1] = 0xD0;
#endif
														reg_wr(REG_ADR_PA_REG_ADJ_H,			 reg_data, 2);

				/* frequency band 920MHz */
			/* frequency setting */
				reg_data[0] = 0x00, reg_wr(REG_ADR_PLL_DIV_SET,					reg_data, 1);

				reg_data[0] = 0x19, reg_data[1] = 0x05; reg_data[2] = 0x05;
				reg_data[3] = 0xB0; reg_data[4] = 0x05;
														reg_wr(REG_ADR_VCO_CAL_MIN_I,				reg_data, 5);

		/* data rate setting */
		/* 50kcps */
				if (dsss_param.page == PHY_DATARATE_50K || dsss_param.page == PHY_DATARATE_100K) {
						if (dsss_param.page == PHY_DATARATE_100K){
#ifdef LAZURITE_IDE
								Serial.println("--------- RF MODE: DSSS 100kcps --------");
#else
							if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s RF MODE: DSSS 100kcps \n",__FILE__,__func__);
#endif
						}else{
#ifdef LAZURITE_IDE
								#ifdef BPSK_40kCPS
								Serial.println("--------- RF MODE: DSSS 40kcps --------");
								#else
								Serial.println("--------- RF MODE: DSSS 50kcps --------");
								#endif
#else
							if(module_test & MODE_PHY_DEBUG) {
										#ifdef BPSK_40kCPS
										printk(KERN_INFO"%s,%s RF MODE: DSSS 40kcps \n",__FILE__,__func__);
										#else
										printk(KERN_INFO"%s,%s RF MODE: DSSS 50kcps \n",__FILE__,__func__);
										#endif
								}
#endif
						}
						/* frequency setting */
						phy_set_zero_channel_req(PHY_FREQ_920_7);

#ifdef BPSK_40kCPS
			reg_data[0] = 0x99;	reg_wr(REG_ADR_DRATE_SET,				reg_data, 1);
#else
						// 100kcps
						if (dsss_param.page == PHY_DATARATE_100K){
								reg_data[0] = 0xBB;	reg_wr(REG_ADR_DRATE_SET,				reg_data, 1);
						}else{
								reg_data[0] = 0xAA;	reg_wr(REG_ADR_DRATE_SET,				reg_data, 1);
						}
#endif
			reg_data[0] = 0x02, reg_wr(REG_ADR_SYNC_CONDITION1, reg_data, 1);
			reg_data[0] = 0x01, reg_wr(REG_ADR_SYNC_CONDITION3, reg_data, 1);

			reg_data[0] = 0x04, reg_wr(REG_ADR_CHFIL_BW,				reg_data, 1); // 50kHz
			reg_data[0] = 0x15, reg_wr(REG_ADR_DC_FIL_ADJ,			reg_data, 1);
			reg_data[0] = 0x17, reg_wr(REG_ADR_IQ_DEC_GAIN,			reg_data, 1);
				reg_data[0] = 0x00, reg_wr(REG_ADR_IF_FREQ,					reg_data, 1); // 225kHz
				reg_data[0] = 0x81, reg_wr(REG_ADR_CHFIL_BW_CCA,		reg_data, 1); // 400kHz
			reg_data[0] = 0x00; reg_data[1] = 0x04;
																reg_wr(REG_ADR_RX_RATE1_H,			reg_data, 2);
				reg_data[0] = 0x0B, reg_wr(REG_ADR_RSSI_MAG_ADJ,		reg_data, 1);
			reg_data[0] = 0x18; reg_wr(REG_ADR_FSK_CTRL,				reg_data, 1); // BT=0.3
						// 100kcps
						if (dsss_param.page == PHY_DATARATE_100K){
							reg_data[0] = 0x0B, reg_wr(REG_ADR_BPSK_DLY_ADJ,		reg_data, 1);
						}else{
								reg_data[0] = 0x0F, reg_wr(REG_ADR_BPSK_DLY_ADJ,		reg_data, 1);
						}
				reg_data[0] = 0xE6, reg_wr(REG_ADR_LNA_RESERVE,			reg_data, 1);
				reg_data[0] = 0xE7, reg_wr(REG_ADR_PAREG_OLR2,			reg_data, 1);
				reg_data[0] = 0x52, reg_wr(REG_ADR_RSSI_ADJ2,				reg_data, 1);
					// 0x76		 AGC/RSSI_OFFSET
			reg_data[0] = 0x8B; reg_data[1] = 0x3C; reg_data[2] = 0x8B;
			reg_data[3] = 0x3C; reg_data[4] = 0x8B; reg_data[5] = 0x3C;
			reg_data[6] = 0x2B; reg_data[7] = 0x4D; reg_data[8] = 0x7D;
								reg_wr(REG_ADR_GAIN_HHTH,				reg_data, 9);

						// if (dsss_param.sf_bit == PHY_DSSS_SF_64) {
						{
								reg_data[0] = dsss_param.ctrl_reg | 0x05; reg_data[1] = 0x45; reg_data[2] = 0x00;
																		reg_wr(REG_ADR_DSSS_CTRL,						reg_data, 3);
								reg_data[0] = 0x00; reg_data[1] = 0x00; reg_data[2] = 0x22;
																		reg_wr(REG_ADR_FEC_INIT_STATE,			reg_data, 3);
								reg_data[0] = 0x05; reg_data[1] = 0x05;
																		reg_wr(REG_ADR_SS_AFC_RANGE_SYNC,		reg_data, 2);
//							reg_data[0] = 0x01; reg_data[1] = 0x67; reg_data[2] = 0x01; reg_data[3] = 0x67; // 18/18MHz // Telec certification
								reg_data[0] = 0x00; reg_data[1] = 0xB3; reg_data[2] = 0x00; reg_data[3] = 0xB3; // 18/18MHz // PER
																		reg_wr(REG_ADR_DSSS_RATE_SYNC_H,		reg_data, 4);
								reg_data[0] = 0x01; reg_data[1] = 0x0C; reg_data[2] = 0x01;
								reg_data[3] = 0x1C; reg_data[4] = 0x00; reg_data[5] = 0xD2; 
																		reg_wr(REG_ADR_SS_SYNC_BIT8_GATE_H, reg_data, 6);
								reg_data[0] = 0x01; reg_data[1] = 0x2C;
																		reg_wr(REG_ADR_SS_SYNC_BIT4_GATE_H, reg_data, 3);
								reg_data[0] = 0x14, reg_wr(REG_ADR_SS_SYNC_LOST_GATE,		reg_data, 1);
								reg_data[0] = 0x2A; reg_data[1] = 0x9C; reg_data[2] = 0x44; reg_data[3] = 0x25;
																		reg_wr(REG_ADR_AGC_AVE_OFST_SYNC,		 reg_data, 4);
								reg_data[0] = 0x01; reg_data[1] = 0xF4;
																		reg_wr(REG_ADR_BIT8_SPDET_TH_H,			reg_data, 2);
								reg_data[0] = 0x34, reg_data[1] = 0x14;
																		reg_wr(REG_ADR_DSSS_SET6,						reg_data, 2);
								reg_data[0] = 0x32, reg_data[1] = 0x25;
																		reg_wr(REG_ADR_DSSS_SET8,						reg_data, 2);
						}
						// 100kcps
						if (dsss_param.page == PHY_DATARATE_100K){
								for (i = 0; i < sizeof(dsss_100kcps_profile); i++) {
										reg_data[0] = dsss_50kcps_profile[i];
										reg_wr(REG_ADR_BPSK_STEP_CTRL+i,		 reg_data, 1);
								}
						}else{
#ifdef BPSK_40kCPS
								for (i = 0; i < sizeof(dsss_40kcps_profile); i++) {
#else
								for (i = 0; i < sizeof(dsss_50kcps_profile); i++) {
#endif
										reg_data[0] = dsss_50kcps_profile[i];
										reg_wr(REG_ADR_BPSK_STEP_CTRL+i,		 reg_data, 1);
								}
						}
#ifdef BPSK_80kCPS
		/* 80kcps */
				} else if (dsss_param.page == PHY_DATARATE_80K) {

#ifdef LAZURITE_IDE
		#ifdef GAUSSIAN_PROFILE
						Serial.println("--------- RF MODE: DSSS 80kcps (Gaussian Filter)--------");
		#else
						Serial.println("--------- RF MODE: DSSS 80kcps --------");
		#endif
#else
					if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s RF MODE: DSSS 80kcps \n",__FILE__,__func__);
#endif
						/* frequency setting */
						phy_set_zero_channel_req(PHY_FREQ_920_7);

			reg_data[0] = 0x02, reg_wr(REG_ADR_CHFIL_BW,						reg_data, 1);
			reg_data[0] = 0x15, reg_wr(REG_ADR_DC_FIL_ADJ,					reg_data, 1);
			reg_data[0] = 0x17, reg_wr(REG_ADR_IQ_DEC_GAIN,					reg_data, 1);
				reg_data[0] = 0x00, reg_wr(REG_ADR_IF_FREQ,							reg_data, 1);
				reg_data[0] = 0x81, reg_wr(REG_ADR_CHFIL_BW_CCA,				reg_data, 1);
			reg_data[0] = 0x00; reg_data[1] = 0x2D; reg_data[2] = 0x00;
						reg_data[3] = 0x03; reg_data[4] = 0x4B;
									reg_wr(REG_ADR_TX_RATE_H,						reg_data, 5);
				reg_data[0] = 0x0B, reg_wr(REG_ADR_RSSI_MAG_ADJ,				reg_data, 1);
		#ifdef GAUSSIAN_PROFILE
				reg_data[0] = 0x03, reg_wr(REG_ADR_BPSK_DLY_ADJ,				reg_data, 1);
		#else
				reg_data[0] = 0x0C, reg_wr(REG_ADR_BPSK_DLY_ADJ,				reg_data, 1);
		#endif
				reg_data[0] = 0x62, reg_wr(REG_ADR_RSSI_ADJ2,						reg_data, 1);
				reg_data[0] = 0x95, reg_data[1] = 0x46, reg_data[2] = 0x95;
						reg_data[3] = 0x46, reg_data[4] = 0x95; reg_data[5] = 0x46;
						reg_data[6] = 0x2B, reg_data[7] = 0x4D, reg_data[8] = 0x7D;
																reg_wr(REG_ADR_GAIN_HHTH,						reg_data, 9);
			reg_data[0] = 0x05; reg_data[1] = 0x45; reg_data[2] = 0x00;
						reg_data[3] = 0x00; reg_data[4] = 0x00; reg_data[5] = 0x22;
								reg_wr(REG_ADR_DSSS_CTRL,						reg_data, 5);
			reg_data[0] = 0x2D, reg_wr(REG_ADR_SS_DOWN_SIZE,				reg_data, 1);
						reg_data[0] = 0x06; reg_data[1] = 0x06;
									reg_wr(REG_ADR_SS_AFC_RANGE_SYNC,		reg_data, 2);
						reg_data[0] = 0x00; reg_data[1] = 0xE0; reg_data[2] = 0x00; reg_data[3] = 0xE0;
																reg_wr(REG_ADR_DSSS_RATE_SYNC_H,		reg_data, 4);
			reg_data[0] = 0x01; reg_data[1] = 0x0C; reg_data[2] = 0x01;
						reg_data[3] = 0x1C; reg_data[4] = 0x00; reg_data[5] = 0xD2; 
								reg_wr(REG_ADR_SS_SYNC_BIT8_GATE_H, reg_data, 6);
						reg_data[0] = 0x01; reg_data[1] = 0x2C;
																reg_wr(REG_ADR_SS_SYNC_BIT4_GATE_H, reg_data, 2);
			reg_data[0] = 0x14, reg_wr(REG_ADR_SS_SYNC_LOST_GATE,		reg_data, 1);
			reg_data[0] = 0x2A, reg_data[1] = 0x9C, reg_data[2] = 0x44, reg_data[3] = 0x25;
																reg_wr(REG_ADR_AGC_AVE_OFST_SYNC,		reg_data, 4);
			reg_data[0] = 0x01; reg_data[1] = 0xF4;
								reg_wr(REG_ADR_BIT8_SPDET_TH_H,			reg_data, 2);
			reg_data[0] = 0x34, reg_data[1] = 0x14, reg_data[2] = 0x32, reg_data[3] = 0x25;
																reg_wr(REG_ADR_DSSS_SET6,						reg_data, 4);

						for (i = 0; i < sizeof(dsss_80kcps_profile); i++) {
								reg_data[0] = dsss_80kcps_profile[i];
								reg_wr(REG_ADR_BPSK_STEP_CTRL+i,		 reg_data, 1);
						}

		#ifdef GAUSSIAN_PROFILE
						// ------------------- Gaussian Filter -----------------------
						// 位相切替タイミング調整
						reg_data[0] = 0x19;  reg_wr(REG_ADR_BPSK_DLY_ADJ,						reg_data, 1);
						// BT=0,5
						reg_data[0] = 0x24; reg_data[1] = 0xD6; reg_data[2] = 0x19; reg_data[3] = 0x29;
						reg_data[4] = 0x3A; reg_data[5] = 0x48; reg_data[6] = 0x4C; 
																reg_wr(REG_ADR_FSK_DEV0_H_GFIL0,				reg_data, 7);

						// BPSK_STEP_CTRL=disable
						reg_data[0] = 0x00;  reg_wr(REG_ADR_BPSK_STEP_CTRL,					reg_data, 1);
						// 各種ドライバ設定
						reg_data[0] = 0x33; reg_data[1] = 0x00; reg_data[2] = 0x00; reg_data[3] = 0x1F;
						reg_data[4] = 0x00; reg_data[5] = 0x00; reg_data[6] = 0x03; 
																reg_wr(REG_ADR_BPSK_PADRV_CTRL,					reg_data, 7);
		#endif
						reg_data[0] = 0x38; reg_data[1] = 0xE3; //	Fdev=500kHz 
																reg_wr(REG_ADR_GFSK_DEV_H,				 reg_data, 2);
						reg_data[0] = 0x00; reg_data[1] = 0x00; reg_data[2] = 0x08; reg_data[3] = 0x00; reg_data[4] = 0x04; //	;Dev_time 1us
																reg_wr(REG_ADR_BPSK_PLL_CTRL,					reg_data, 5);
#endif // BPSK_80KCPS
		/* 200kbps */
				} else if (dsss_param.page == PHY_DATARATE_200K) {

#ifdef LAZURITE_IDE
				Serial.println("--------- RF MODE: DSSS 200kcps --------");
#else
			if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s RF MODE: DSSS 200kcps \n",__FILE__,__func__);
#endif
					/* channel setting */
						// first channel: ((ch - 24) * 100khz channel space) + 300khz offset
						base_channel = ((ch - 24) * 2) + 3;

						/* frequency setting */
						phy_set_zero_channel_req(PHY_FREQ_920_7);

						/* channel space setting */
						reg_data[0] = channel_space[PHY_CHSPACE_100K][0];
						reg_data[1] = channel_space[PHY_CHSPACE_100K][1];
																reg_wr(REG_ADR_CH_SPACE_H,					reg_data, 2);

			reg_data[0] = 0xCC;	reg_wr(REG_ADR_DRATE_SET,				reg_data, 1);
			reg_data[0] = 0x02, reg_wr(REG_ADR_SYNC_CONDITION1, reg_data, 1);
			reg_data[0] = 0x01, reg_wr(REG_ADR_SYNC_CONDITION3, reg_data, 1);
			reg_data[0] = 0x15, reg_wr(REG_ADR_DC_FIL_ADJ,			reg_data, 1);
			reg_data[0] = 0x00, reg_wr(REG_ADR_IF_FREQ,					reg_data, 1);
			reg_data[0] = 0x81, reg_wr(REG_ADR_CHFIL_BW_CCA,		reg_data, 1);

			reg_data[0] = 0x00; reg_data[1] = 0x04;
									reg_wr(REG_ADR_RX_RATE1_H,					reg_data, 2);
				reg_data[0] = 0x0B, reg_wr(REG_ADR_RSSI_MAG_ADJ,				reg_data, 1);
				reg_data[0] = 0x08, reg_wr(REG_ADR_BPSK_DLY_ADJ,				reg_data, 1);
				reg_data[0] = 0xC6, reg_wr(REG_ADR_LNA_RESERVE,					reg_data, 1);
				reg_data[0] = 0xE7, reg_wr(REG_ADR_PAREG_OLR2,					reg_data, 1);
				reg_data[0] = 0x52, reg_wr(REG_ADR_RSSI_ADJ2,						reg_data, 1);
				reg_data[0] = 0x8B, reg_data[1] = 0x3C, reg_data[2] = 0x8B, reg_data[3] = 0x3C, reg_data[4] = 0x8B;
						reg_data[5] = 0x3C, reg_data[6] = 0x2B, reg_data[7] = 0x4D, reg_data[8] = 0x7D;
																reg_wr(REG_ADR_GAIN_HHTH,						reg_data, 9);

					//;------------------------------------------------------------------------------
					//; SF = 64
					//;------------------------------------------------------------------------------
						if (dsss_param.sf_bit == PHY_DSSS_SF_64) {
								reg_data[0] = dsss_param.ctrl_reg | 0x05; reg_data[1] = 0x45; reg_data[2] = 0x00;
																		reg_wr(REG_ADR_DSSS_CTRL,						reg_data, 3);
								reg_data[0] = 0x00; reg_data[1] = 0x00; reg_data[2] = 0x22;
																		reg_wr(REG_ADR_FEC_INIT_STATE,			reg_data, 3);
								reg_data[0] = 0x05; reg_data[1] = 0x05;
																		reg_wr(REG_ADR_SS_AFC_RANGE_SYNC,		reg_data, 2);
								reg_data[0] = 0x00; reg_data[1] = 0x59; reg_data[2] = 0x00; reg_data[3] = 0x59;
																		reg_wr(REG_ADR_DSSS_RATE_SYNC_H,		reg_data, 4);
//							reg_data[0] = 0x01; reg_data[1] = 0x0C; reg_data[2] = 0x01;			// Telec certicication
								reg_data[0] = 0x01; reg_data[1] = 0xF4; reg_data[2] = 0x01;			// PER
								reg_data[3] = 0x1C; reg_data[4] = 0x00; reg_data[5] = 0xD2;
																		reg_wr(REG_ADR_SS_SYNC_BIT8_GATE_H, reg_data, 6);
								reg_data[0] = 0x01; reg_data[1] = 0x2C;
																		reg_wr(REG_ADR_SS_SYNC_BIT4_GATE_H, reg_data, 3);
								reg_data[0] = 0x14, reg_wr(REG_ADR_SS_SYNC_LOST_GATE,		reg_data, 1);
								reg_data[0] = 0x2A; reg_data[1] = 0x9C; reg_data[2] = 0x44; reg_data[3] = 0x25;
																		reg_wr(REG_ADR_AGC_AVE_OFST_SYNC,		 reg_data, 4);
								reg_data[0] = 0x01; reg_data[1] = 0xF4;
																		reg_wr(REG_ADR_BIT8_SPDET_TH_H,			reg_data, 2);
								reg_data[0] = 0x34, reg_data[1] = 0x14;
																		reg_wr(REG_ADR_DSSS_SET6,						reg_data, 2);
								reg_data[0] = 0x32, reg_data[1] = 0x25;
																		reg_wr(REG_ADR_DSSS_SET8,						reg_data, 2);
						}
					//;------------------------------------------------------------------------------
					//; SF = 32
					//;------------------------------------------------------------------------------
						else if (dsss_param.sf_bit == PHY_DSSS_SF_32) {
								reg_data[0] = dsss_param.ctrl_reg | 0x05; reg_data[1] = 0x45; reg_data[2] = 0x00;
																		reg_wr(REG_ADR_DSSS_CTRL,						reg_data, 3);
								reg_data[0] = 0x00; reg_data[1] = 0x00; reg_data[2] = 0x11;
																		reg_wr(REG_ADR_FEC_INIT_STATE,			reg_data, 3);
					reg_data[0] = 0x01; reg_data[1] = 0x31; reg_data[2] = 0x2D; reg_data[3] = 0x1F;
										reg_wr(REG_ADR_SHR_GOLD_SEED3,			reg_data, 3);
										reg_wr(REG_ADR_PSDU_GOLD_SEED3,			reg_data, 3);
								reg_data[0] = 0x05; reg_data[1] = 0x05;
																		reg_wr(REG_ADR_SS_AFC_RANGE_SYNC,		reg_data, 2);
								reg_data[0] = 0x00; reg_data[1] = 0x59; reg_data[2] = 0x00; reg_data[3] = 0x59;
																		reg_wr(REG_ADR_DSSS_RATE_SYNC_H,		reg_data, 4);
								reg_data[0] = 0x00; reg_data[1] = 0xAA; reg_data[2] = 0x00; reg_data[3] = 0xB0;
								reg_data[4] = 0x00; reg_data[5] = 0xA0; 
																		reg_wr(REG_ADR_SS_SYNC_BIT8_GATE_H, reg_data, 6);
								reg_data[0] = 0x01; reg_data[1] = 0x18;
																		reg_wr(REG_ADR_SS_SYNC_BIT4_GATE_H, reg_data, 3);
								reg_data[0] = 0x14, reg_wr(REG_ADR_SS_SYNC_LOST_GATE,		reg_data, 1);
								reg_data[0] = 0x2A; reg_data[1] = 0x9C; reg_data[2] = 0x44; reg_data[3] = 0x25;
																		reg_wr(REG_ADR_AGC_AVE_OFST_SYNC,		 reg_data, 4);
								reg_data[0] = 0x00; reg_data[1] = 0xDC;
																		reg_wr(REG_ADR_BIT8_SPDET_TH_H,			reg_data, 2);
								reg_data[0] = 0x34, reg_data[1] = 0x14;
																		reg_wr(REG_ADR_DSSS_SET6,						reg_data, 2);
								reg_data[0] = 0x32, reg_data[1] = 0x25;
																		reg_wr(REG_ADR_DSSS_SET8,						reg_data, 2);
						}
						//;------------------------------------------------------------------------------
						//; SF = 16
						//;------------------------------------------------------------------------------
						else if (dsss_param.sf_bit == PHY_DSSS_SF_16) {
								reg_data[0] = dsss_param.ctrl_reg | 0x05; reg_data[1] = 0x45; reg_data[2] = 0x00;
																		reg_wr(REG_ADR_DSSS_CTRL,						reg_data, 3);
								reg_data[0] = 0x00; reg_data[1] = 0x00; reg_data[2] = 0x00;
																		reg_wr(REG_ADR_FEC_INIT_STATE,			reg_data, 3);
					reg_data[0] = 0x01; reg_data[1] = 0x31; reg_data[2] = 0x2D; reg_data[3] = 0x3A;
										reg_wr(REG_ADR_SHR_GOLD_SEED3,			reg_data, 3);
										reg_wr(REG_ADR_PSDU_GOLD_SEED3,			reg_data, 3);
								reg_data[0] = 0x05; reg_data[1] = 0x05;
																		reg_wr(REG_ADR_SS_AFC_RANGE_SYNC,		reg_data, 2);
								reg_data[0] = 0x00; reg_data[1] = 0x59; reg_data[2] = 0x00; reg_data[3] = 0x59;
																		reg_wr(REG_ADR_DSSS_RATE_SYNC_H,		reg_data, 4);
								reg_data[0] = 0x00; reg_data[1] = 0x78; reg_data[2] = 0x00; reg_data[3] = 0x78;
								reg_data[4] = 0x00; reg_data[5] = 0x70; 
																		reg_wr(REG_ADR_SS_SYNC_BIT8_GATE_H, reg_data, 6);
								reg_data[0] = 0x00; reg_data[1] = 0xA0;
																		reg_wr(REG_ADR_SS_SYNC_BIT4_GATE_H, reg_data, 3);
								reg_data[0] = 0x14, reg_wr(REG_ADR_SS_SYNC_LOST_GATE,		reg_data, 1);
								reg_data[0] = 0x2A; reg_data[1] = 0x9C; reg_data[2] = 0x44; reg_data[3] = 0x25;
																		reg_wr(REG_ADR_AGC_AVE_OFST_SYNC,		 reg_data, 4);
								reg_data[0] = 0x00; reg_data[1] = 0xAF;
																		reg_wr(REG_ADR_BIT8_SPDET_TH_H,			reg_data, 2);
								reg_data[0] = 0x35, reg_data[1] = 0x45;
																		reg_wr(REG_ADR_DSSS_SET6,						reg_data, 2);
								reg_data[0] = 0x32, reg_data[1] = 0x25;
																		reg_wr(REG_ADR_DSSS_SET8,						reg_data, 2);
						}
						//;------------------------------------------------------------------------------
						//; sf = 8
						//;------------------------------------------------------------------------------
						else if (dsss_param.sf_bit == PHY_DSSS_SF_8) {
								reg_data[0] = dsss_param.ctrl_reg | 0x05; reg_data[1] = 0x45; reg_data[2] = 0x00;
																		reg_wr(REG_ADR_DSSS_CTRL,						reg_data, 3);
								reg_data[0] = 0x00; reg_data[1] = 0x00; reg_data[2] = 0x33;
																		reg_wr(REG_ADR_FEC_INIT_STATE,			reg_data, 3);
					reg_data[0] = 0x01; reg_data[1] = 0x31; reg_data[2] = 0x30; reg_data[3] = 0xCA;
										reg_wr(REG_ADR_SHR_GOLD_SEED3,			reg_data, 3);
										reg_wr(REG_ADR_PSDU_GOLD_SEED3,			reg_data, 3);
								reg_data[0] = 0x05; reg_data[1] = 0x05;
																		reg_wr(REG_ADR_SS_AFC_RANGE_SYNC,		reg_data, 2);
								reg_data[0] = 0x00; reg_data[1] = 0x59; reg_data[2] = 0x00; reg_data[3] = 0x59;
																		reg_wr(REG_ADR_DSSS_RATE_SYNC_H,		reg_data, 4);
								reg_data[0] = 0x00; reg_data[1] = 0x65; reg_data[2] = 0x00; reg_data[3] = 0x65;
								reg_data[4] = 0x00; reg_data[5] = 0x60; 
																		reg_wr(REG_ADR_SS_SYNC_BIT8_GATE_H, reg_data, 6);
								reg_data[0] = 0x00; reg_data[1] = 0x80;
																		reg_wr(REG_ADR_SS_SYNC_BIT4_GATE_H, reg_data, 3);
								reg_data[0] = 0x14, reg_wr(REG_ADR_SS_SYNC_LOST_GATE,		reg_data, 1);
								reg_data[0] = 0x06; reg_wr(REG_ADR_DSSS_SET3,						reg_data, 2);
								reg_data[0] = 0x2A; reg_data[1] = 0x9C; reg_data[2] = 0x44; reg_data[3] = 0x25;
																		reg_wr(REG_ADR_AGC_AVE_OFST_SYNC,		 reg_data, 4);
								reg_data[0] = 0x00; reg_data[1] = 0xAF;
																		reg_wr(REG_ADR_BIT8_SPDET_TH_H,			reg_data, 2);
								reg_data[0] = 0x67, reg_data[1] = 0x67;
																		reg_wr(REG_ADR_DSSS_SET6,						reg_data, 2);
								reg_data[0] = 0x32, reg_data[1] = 0x25;
																		reg_wr(REG_ADR_DSSS_SET8,						reg_data, 2);
						}

						for (i = 0; i < sizeof(dsss_200kbps_profile); i++) {
								reg_data[0] = dsss_200kbps_profile[i];
								reg_wr(REG_ADR_BPSK_STEP_CTRL+i,		 reg_data, 1);
						}
		}

				
		/* CRC */
		reg_data[0] = 0x00; reg_data[1] = 0x00; reg_data[2] = 0x08; reg_data[3] = 0x10;
							reg_wr(REG_ADR_CRC_POLY3,						reg_data, 4);
				reg_data[0] = 0x08, reg_wr(REG_ADR_SYNC_WORD_LEN,				reg_data, 1);
				reg_data[0] = 0x00; reg_data[1] = 0x00; reg_data[2] = 0x00; reg_data[3] = 0x38;
														reg_wr(REG_ADR_SYNCWORD1_SET0,			reg_data, 4);
				reg_data[0] = 0x03; reg_data[1] = 0x10 | (dsss_param.ctrl_reg == PHY_DSSS_SIZE_FREE ? 0x0C:0x00);
														reg_wr(REG_ADR_PKT_CTRL1,						reg_data, 2);

				if(dsss_param.ctrl_reg == PHY_DSSS_SIZE_FREE){
						reg_data[0] = 0x00; reg_data[1] = dsss_param.size;
														reg_wr(REG_ADR_TX_PKT_LEN_H,				reg_data, 2);
														reg_wr(REG_ADR_RX_PKT_LEN_H,				reg_data, 2);
				}
				reg_data[0] = 0x00; reg_data[1] = 0x00; reg_data[2] = 0x00;
														reg_wr(REG_ADR_C_CHECK_CTRL,				reg_data, 3);
		/**************************************
				FSK
		 **************************************/
	} else if (dsss_param.modulation == PHY_MODULATION_FSK) {

				// 0x67/68 PA_REG_ADJ_H/L 13dBm
				reg_data[0] = 0x00; reg_data[1] = 0xFF;
														reg_wr(REG_ADR_PA_REG_ADJ_H,			 reg_data, 2);

		reg_data[0] = 0x00, reg_wr(REG_ADR_MOD_CTRL,						reg_data, 1);
		reg_data[0] = 0x00, reg_wr(REG_ADR_DSSS_CTRL,						reg_data, 1);
		reg_data[0] = 0x00, reg_wr(REG_ADR_FEC_ENC_CTRL,				reg_data, 1);
		reg_data[0] = 0x00, reg_wr(REG_ADR_FEC_DEC_CTRL,				reg_data, 1);
				reg_data[0] = 0x00, reg_wr(REG_ADR_BPSK_STEP_CTRL,			reg_data, 1);
				reg_data[0] = 0x00; reg_data[1] = 0x010; reg_data[2] = 0x01;
														reg_wr(REG_ADR_RAMP_CTRL1,					reg_data, 3);
				reg_data[0] = 0x19; reg_data[1] = 0x09; reg_data[2] = 0x05;
				reg_data[3] = 0xB0; reg_data[4] = 0x04;
														reg_wr(REG_ADR_VCO_CAL_MIN_I,				reg_data, 5);

		/* data rate setting */
		if (dsss_param.page == PHY_DATARATE_50K) {
#ifdef LAZURITE_IDE
				Serial.println("--------- RF MODE: FSK 50kbps --------");
#else
			if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s RF MODE: FSK 50kbps \n",__FILE__,__func__);
#endif
					reg_data[0] = 0x10, reg_wr(REG_ADR_CCA_LEVEL,						 reg_data, 1);

						/* frequency setting */
						phy_set_zero_channel_req(PHY_FREQ_920_6);

			/* 50kbps */
			reg_data[0] = 0xAA, reg_wr(REG_ADR_DRATE_SET,						reg_data, 1);
			reg_data[0] = 0x02, reg_wr(REG_ADR_CHFIL_BW,						reg_data, 1);
				reg_data[0] = 0x12, reg_wr(REG_ADR_DC_FIL_ADJ,					reg_data, 1);
			reg_data[0] = 0x15; reg_data[1] = 0x33;
								reg_wr(REG_ADR_IQ_DEC_GAIN,					reg_data, 2);
			reg_data[0] = 0x01, reg_wr(REG_ADR_CHFIL_BW_CCA,				reg_data, 1);
			reg_data[0] = 0x00, reg_wr(REG_ADR_DC_FIL_ADJ2,					reg_data, 1);
			reg_data[0] = 0x18, reg_wr(REG_ADR_DEC_GAIN_CCA,				reg_data, 1);
			reg_data[0] = 0x0E, reg_wr(REG_ADR_RSSI_MAG_ADJ,				reg_data, 1);
			reg_data[0] = 0x86, reg_wr(REG_ADR_AFC_GC_CTRL,					reg_data, 1);
						// FSK_CTRL & GFSK_DEV_H/L
			reg_data[0] = 0x00; reg_data[1] = 0x02; reg_data[2] = 0xD8;
								reg_wr(REG_ADR_FSK_CTRL,						reg_data, 3);
						// 0x32-38 FSK_DEV0_H/GFIL0-FSK_DEV3_H/GFIL6
						reg_data[0] = 0x24, reg_data[1] = 0xD6, reg_data[2] = 0x19, reg_data[3] = 0x29;
						reg_data[4] = 0x3A, reg_data[5] = 0x48, reg_data[6] = 0x4C;
																reg_wr(REG_ADR_FSK_DEV0_H_GFIL0,		reg_data, 7);
						// 0x57-5F DEMOD_SET1-9
			reg_data[0] = 0x04; reg_data[1] = 0x01; reg_data[2] = 0x10;
			reg_data[3] = 0x00; reg_data[4] = 0x00; reg_data[5] = 0x15;
			reg_data[6] = 0x16; reg_data[7] = 0x03; reg_data[8] = 0xCD;
								reg_wr(REG_ADR_DEMOD_SET1,					reg_data, 9);
					reg_data[0] = 0x5B, reg_wr(REG_ADR_RSSI_ADJ2,						reg_data, 1);
					//reg_data[0] = 0x62, reg_wr(REG_ADR_RSSI_ADJ2,						reg_data, 1);
					// 0x76		 AGC/RSSI_OFFSET
			reg_data[0] = 0x8C; reg_data[1] = 0x3C; reg_data[2] = 0x8C;
			reg_data[3] = 0x3C; reg_data[4] = 0x8C; reg_data[5] = 0x3C;
			reg_data[6] = 0x2F; reg_data[7] = 0x55; reg_data[8] = 0x85;
								reg_wr(REG_ADR_GAIN_HHTH,						reg_data, 9);
			reg_data[0] = 0x64, reg_wr(REG_ADR_DEMSET25,						reg_data, 1);
			reg_data[0] = 0x33, reg_wr(REG_ADR_DIF_SET0,						reg_data, 1);
				}else
				if (dsss_param.page == PHY_DATARATE_100K) {
#ifdef LAZURITE_IDE
				Serial.println("--------- RF MODE: FSK 100kbps --------");
#else
			if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s RF MODE: FSK 100kbps \n",__FILE__,__func__);
#endif

#ifndef ABROAD
            if (ch == 32) {
		        status = -1;
                goto error;
            }
#endif
				 // Telec: 0x10
					reg_data[0] = 0x30, reg_wr(REG_ADR_CCA_LEVEL,						reg_data, 1);

						reg_data[0] = 0x00, reg_wr(REG_ADR_PLL_DIV_SET,					reg_data, 1);

						/* frequency setting */
						phy_set_zero_channel_req(PHY_FREQ_920_7);

			/* 100kbps */
			reg_data[0] = 0xBB, reg_wr(REG_ADR_DRATE_SET,						reg_data, 1);
			reg_data[0] = 0x01, reg_wr(REG_ADR_CHFIL_BW,						reg_data, 1);
				reg_data[0] = 0x12, reg_wr(REG_ADR_DC_FIL_ADJ,					reg_data, 1);
			reg_data[0] = 0x17, reg_wr(REG_ADR_IQ_DEC_GAIN,					reg_data, 1);
				reg_data[0] = 0x00, reg_wr(REG_ADR_IF_FREQ,							reg_data, 1);
			reg_data[0] = 0x81, reg_wr(REG_ADR_CHFIL_BW_CCA,				reg_data, 1);
				reg_data[0] = 0x00, reg_wr(REG_ADR_DC_FIL_ADJ2,					reg_data, 1);
			reg_data[0] = 0x18, reg_wr(REG_ADR_DEC_GAIN_CCA,				reg_data, 1);
			reg_data[0] = 0x0D, reg_wr(REG_ADR_RSSI_MAG_ADJ,				reg_data, 1);
			reg_data[0] = 0x86, reg_wr(REG_ADR_AFC_GC_CTRL,					reg_data, 1);
			reg_data[0] = 0x00; reg_data[1] = 0x05; reg_data[2] = 0xB0;
								reg_wr(REG_ADR_FSK_CTRL,						reg_data, 3);
						reg_data[0] = 0x24; reg_data[1] = 0xD6; reg_data[2] = 0x19; reg_data[3] = 0x29;
																reg_wr(REG_ADR_FSK_DEV0_H_GFIL0,		reg_data, 4);
						reg_data[0] = 0x3A; reg_data[1] = 0x48; reg_data[2] = 0x4C;
																reg_wr(REG_ADR_FSK_DEV2_H_GFIL4,		reg_data, 3);
			reg_data[0] = 0x04; reg_data[1] = 0x01; reg_data[2] = 0x10;
			reg_data[3] = 0x00; reg_data[4] = 0x00; reg_data[5] = 0x15;
			reg_data[6] = 0x0B; reg_data[7] = 0x02; reg_data[8] = 0xCC;
								reg_wr(REG_ADR_DEMOD_SET1,					reg_data, 9);

				reg_data[0] = 0x5B, reg_wr(REG_ADR_RSSI_ADJ2,						reg_data, 1);
						reg_data[0] = 0x8C; reg_data[1] = 0x32; reg_data[2] = 0x8C;
						reg_data[3] = 0x32; reg_data[4] = 0x8C; reg_data[5] = 0x32;
						reg_data[6] = 0x2A; reg_data[7] = 0x52; reg_data[8] = 0x7F;
								reg_wr(REG_ADR_GAIN_HHTH,						reg_data, 9);
			reg_data[0] = 0x33, reg_wr(REG_ADR_DIF_SET0,						reg_data, 1);

#ifdef FCC
			reg_data[0] = 0x18, reg_wr(REG_ADR_CHFIL_BW,		reg_data, 1);		// WREG, 0x54, 0x81        # CHFIL_BW(400kHz)
			reg_data[0] = 0x15, reg_wr(REG_ADR_DC_FIL_ADJ,	reg_data, 1);		// WREG, 0x59, 0x15        # DC_FIL_ADJ
			reg_data[0] = 0x18, reg_wr(REG_ADR_IQ_DEC_GAIN,	reg_data, 1);		// WREG, 0x60, 0x18        # DEC_GAIN
			reg_data[0] = 0x00, reg_wr(REG_ADR_IF_FREQ,			reg_data, 1);		// WREG, 0x61, 0x00        # IF_FREQ(225kHz)
			reg_data[0] = 0x81, reg_wr(REG_ADR_CHFIL_BW_CCA,reg_data, 1);		// WREG, 0x6A, 0x81        # CHFIL_BW_CCA(400kHz)
			reg_data[0] = 0x1B, reg_wr(REG_ADR_DEC_GAIN_CCA,reg_data, 1);		// WREG, 0x6D, 0x18        # DEC_GAIN_CCA
			// BWREG, 0x30, 0x02, 0x13, 0x57    # CH_SPACE_H/L(170kHz) 6dB Bandwidth = 520kHz
			// BWREG, 0x30, 0x02, 0x12, 0xC5    # CH_SPACE_H/L(165kHz) 6dB Bandwidth = 510kHz
			// BWREG, 0x30, 0x02, 0x12, 0x51    # CH_SPACE_H/L(161kHz) 6dB Bandwidth = 500kHz
			reg_data[0] = 0x12, reg_data[1] = 0xc5;
			reg_wr(REG_ADR_GFSK_DEV_H,reg_data, 2);
			reg_data[0] = 0x00, reg_wr(REG_ADR_DEMOD_SET2,reg_data, 1);		// WREG, 0x58, 0x00        # DEM_SET2(DEM_GAIN)
			reg_data[0] = 0x1b, reg_wr(REG_ADR_DEMOD_SET6,reg_data, 1);		// WREG, 0x5C, 0x1B        # DEM_SET6(RXDEV_RANGE)
#endif
		}
				reg_data[0] = 0x01, reg_wr(REG_ADR_DATA_SET2,						reg_data, 1);
				reg_data[0] = 0x16; reg_data[1] = 0x5D;
														reg_wr(REG_ADR_PKT_CTRL1,						reg_data, 2);
				reg_data[0] = 0x00; reg_data[1] = 0x10;
														reg_wr(REG_ADR_TXPR_LEN_H,					reg_data, 2);
				reg_data[0] = 0x77; reg_wr(REG_ADR_RSSI_STABLE_TIME,		reg_data, 1);
				reg_data[0] = 0x10, reg_wr(REG_ADR_SYNC_WORD_LEN,				reg_data, 1);
				reg_data[0] = 0x00; reg_data[1] = 0x00; reg_data[2] = 0x90; reg_data[3] = 0x4E;
														reg_wr(REG_ADR_SYNCWORD1_SET0,			reg_data, 4);
				reg_data[0] = 0x00; reg_data[1] = 0x00; reg_data[2] = 0x6F; reg_data[3] = 0x4E;
														reg_wr(REG_ADR_SYNCWORD2_SET0,			reg_data, 4);
				reg_data[0] = 0x00; reg_data[1] = 0x00; reg_data[2] = 0x08; reg_data[3] = 0x10;
														reg_wr(REG_ADR_CRC_POLY3,						reg_data, 4);
				reg_data[0] = 0x00; reg_data[1] = 0xF0; reg_data[2] = 0x10;
														reg_wr(REG_ADR_WHT_INIT_H,					reg_data, 3);
	}

		/* channel setting */
		reg_data[0] = base_channel, reg_wr(REG_ADR_CH_SET,							reg_data, 1);

		/* own apparatus address acquisition */
		HAL_I2C_read(0x26, reg_data, 2), address = H2LS(*reg_data);

		vco_cal();

		status = 0;
error:
		return status;
}


PHY_PARAM *phy_init(void)
{
		uint8_t reg_data;
		uint32_t wait_t;
		int status = -1;

		hwif.timer.handler = NULL;
#ifdef PHY_HWIF_NOTHAVE_TIMER_DI
		hwif.timer.active = Disable;
		hwif.timer.call_count = 0;
#endif	/* #ifdef PHY_HWIF_NOTHAVE_TIMER_DI */
		status = HAL_init();
		if(status == 0){
		//	HAL_SPI_setup();
		//	HAL_GPIO_setup();
				HAL_TIMER_setup();
		//	HAL_I2C_setup();
				phy_timer_tick(&wait_t);
				regbank(0xff);
				reg_data=0x00; reg_wr(REG_ADR_SPI_EXT_PA_CTRL, &reg_data, 1);
//			reg_data=0xC3; reg_wr(REG_ADR_CLK_SET2,				 &reg_data, 1);		// TCXO:0xC3, XTAL:0x93
				do {
						HAL_delayMicroseconds(100);
			} while (phy_int_detection(HW_EVENT_CLK_DONE) == false);

				reg_data = 0x00; reg_wr(REG_ADR_INT_SOURCE_GRP1, &reg_data, 1);
		}

	memset(reg.rdata,0,sizeof(reg.rdata));
	memset(reg.wdata,0,sizeof(reg.wdata));
	memset(reg.rfifo,0,sizeof(reg.rfifo));
	memset(reg.wfifo,0,sizeof(reg.wfifo));
	phy.in.size = BUFFER_SIZE;
	phy.in.data = reg.rfifo+1;
	phy.in.len = 0;
	phy.out.size = BUFFER_SIZE;
	phy.out.len = 0;
	phy.out.data = reg.wfifo+1;

		reg_rd(REG_ADR_RF_STATUS, &reg_data, 1);

#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG)printk(KERN_INFO"%s,%s,rfifo:%lx,wfifo:%lx\n",__FILE__,__func__,
														(unsigned long)reg.rfifo+1,(unsigned long)reg.wfifo+1);
#endif
	return &phy;
}


/*
void phy_promiscuous(void)
{
//	phy_inten(HW_EVENT_RX_DONE | HW_EVENT_CRC_ERROR);
		phy_inten(HW_EVENT_RX_DONE);
		phy_set_trx_state(PHY_ST_RXON);
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG)printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}
*/


void phy_rxStart(void)
{
		uint8_t reg_data[3];

		phy_inten(HW_EVENT_FIFO_FULL|HW_EVENT_RX_DONE);
		phy_rst();

		// address filter
		/*
		if (dsss_param.modulation == PHY_MODULATION_FSK){
			reg_data[0] = 0x80;
			reg_data[1] = 0x00;
			reg_data[2] = 0x0F;
			reg_wr(REG_ADR_C_CHECK_CTRL, reg_data, 3);
		}
		*/
		
		fifo_param.fifo_temp_len = 0;
		fifo_param.fifo_temp_buf = 0;

		reg_data[0] = 0x80 | PHY_FIFO_FULL_TRG;
		reg_data[1] = 0x80 | (PHY_FIFO_FULL_TRG - 1);
		reg_wr(REG_ADR_RXFIFO_THRH,reg_data,2);
		phy_set_trx_state(PHY_ST_RXON);
//		reg_rd(REG_ADR_INT_SOURCE_GRP1, reg_data, 3);
//		reg_rd(REG_ADR_INT_EN_GRP1, reg_data, 3);
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}


/******************************************************************************/
/*! @brief Writing in data to FIFO
 * Delay 300usec is intended to prevent FIFO access during TX_ON transition.
 * It may become the PLL unlocking when FIFO accesses it.
 ******************************************************************************/
bool phy_txStart(BUFFER *buff,uint8_t mode)
{
		uint8_t reg_data[2];
		uint16_t length;
		uint8_t *payload = buff->data;
		uint8_t ret=0;

		if(mode == FIFO_NORMAL) return ret;

		// ----- make fcf
		if (dsss_param.modulation == PHY_MODULATION_DSSS) {
				length = dsss_param.size - PHY_CRC_LEN;
		}else if (dsss_param.modulation == PHY_MODULATION_SIGFOX) {
				length = buff->len;
				reg_data[0] = 0x00;							// PHR
				reg_data[1] = length + PHY_CRC_LEN;				// length : crc size + payload length
				reg_wr(REG_ADR_TX_PKT_LEN_H, reg_data, 2);
		}else{ // PHY_MODULATION_FSK
				length = buff->len;
				reg_data[0] = 0x18;							// PHR
				reg_data[1] = length + PHY_CRC_LEN;				// length : crc size + payload length
				reg_wr(REG_ADR_TX_PKT_LEN_H, reg_data, 2);
		}

		// ----- RF STATUS CTRL & INT STATUS
		reg_rd(REG_ADR_RF_STATUS_CTRL, reg_data, 1);
		reg_data[0] &= ~PHY_REG_SET_TX_DONE_OFF;
		if(mode == FIFO_AUTO_TX) {
				if (length > PHY_FIFO_DATA_TRG){
						reg_data[0] |= 0x30;		// FAST_TX
						phy_inten(HW_EVENT_FIFO_EMPTY);
				}else{
						reg_data[0] |= 0x10;		// auto tx on
						phy_inten(HW_EVENT_TX_DONE);
				}
		}else {
				reg_data[0] &= ~0x10;		// auto tx off
		}
		reg_wr(REG_ADR_RF_STATUS_CTRL, reg_data, 1);

		// ----- make payload
		if (length > PHY_FIFO_DATA_TRG){
				reg_data[0] = 0x80 | (PHY_FIFO_EMPTY_TRG + 3);
				reg_data[1] = 0x80 | PHY_FIFO_EMPTY_TRG;
				reg_wr(REG_ADR_TXFIFO_THRH, reg_data, 2);
				fifo_wr(REG_ADR_WR_TX_FIFO, buff->data, payload, PHY_FIFO_DATA_TRG);
				fifo_param.fifo_temp_len = length - PHY_FIFO_DATA_TRG;
				fifo_param.fifo_temp_buf = payload + PHY_FIFO_DATA_TRG;
				ret = 1;
		}else{
				fifo_wr(REG_ADR_WR_TX_FIFO, buff->data, payload, length);
				ret = 0;
		}

#ifdef LAZURITE_IDE
		#ifdef SERIAL_DEBUG
		Serial.print("USER LEN:");
		Serial.println_long((long)dsss_param.size - PHY_ADDR_TYPE6_LEN - PHY_CRC_LEN ,DEC);
		Serial.print("BUFF LEN:");
		Serial.println_long((long)buff->len,DEC);
		Serial.print("PSDU LEN(for writing to fifo):");
		Serial.println_long((long)length,DEC);
		Serial.print("DSSS SIZE:");
		Serial.println_long((long)dsss_param.size,DEC);
		Serial.print("RETRUN VALUE:");
		Serial.println_long((long)ret,DEC);

		reg_rd(REG_ADR_RF_STATUS, reg_data, 1);
		Serial.print("RF_STATUS:");
		Serial.println_long((long)reg_data[0],HEX);

		reg_rd(REG_ADR_INT_SOURCE_GRP3, reg_data, 1);
	    Serial.print("INT_G3:");
		Serial.println_long((long)reg_data[0],HEX);
        
		reg_rd(REG_ADR_RF_STATUS_CTRL, reg_data, 1);
		Serial.print("RF_CTRL:");
		Serial.println_long((long)reg_data[0],HEX);
		Serial.print("LEN:");
		Serial.println_long((long)buff->len,DEC);
		Serial.print("MODE:");
		Serial.println_long((long)mode,DEC);
		Serial.print("RET VAL:");
		Serial.println_long((long)ret,DEC);
        #endif
#else
		if(module_test & MODE_PHY_DEBUG) {
				printk(KERN_INFO"%s,%s,%lx,%d,SequnceNumber:%d, mode:%d\n",
				__FILE__,__func__,(unsigned long)payload,length,payload[2],mode);
		 // PAYLOADDUMP(payload,length);
		}
#endif

		return ret;
}

bool phy_txfifo(BUFFER *buff){

		uint8_t reg_data[2];
		uint8_t ret;

        // ssdebug
        /*
		reg_rd(REG_ADR_INT_SOURCE_GRP3, reg_data, 1);
        if (reg_data[0] & 0x10) {
		    Serial.print("INT_G3-2:");
		    Serial.println_long((long)reg_data[0],HEX);
        }
        */

		if (fifo_param.fifo_temp_len > PHY_FIFO_DATA_TRG){
				fifo_wr(REG_ADR_WR_TX_FIFO, buff->data, fifo_param.fifo_temp_buf, PHY_FIFO_DATA_TRG);
				fifo_param.fifo_temp_len -= PHY_FIFO_DATA_TRG;
				fifo_param.fifo_temp_buf += PHY_FIFO_DATA_TRG;
				phy_inten(HW_EVENT_FIFO_EMPTY);
				ret = 1;
		}else{
				fifo_wr(REG_ADR_WR_TX_FIFO, buff->data, fifo_param.fifo_temp_buf, fifo_param.fifo_temp_len);
				reg_data[0] = 0;
				reg_data[1] = 0;
				reg_wr(REG_ADR_TXFIFO_THRH, reg_data, 2);
				fifo_param.fifo_temp_len = 0;
				fifo_param.fifo_temp_buf = 0;
				phy_inten(HW_EVENT_TX_DONE);
				ret = 0;
		}

		phy_intclr(HW_EVENT_FIFO_EMPTY);
#ifdef LAZURITE_IDE
		#ifdef SERIAL_DEBUG
		reg_rd(REG_ADR_INT_SOURCE_GRP3, reg_data, 1);
        if (reg_data[0] & 0x10) {
		    Serial.print("INT_G3-3:");
		    Serial.println_long((long)reg_data[0],HEX);
        }
		Serial.print("FIFO_DONE:");
		Serial.print_long((long)fifo_param.fifo_temp_len,DEC);
		Serial.print(",");
		Serial.println_long((long)fifo_param.fifo_temp_buf,DEC);
		Serial.print("RET VAL:");
		Serial.println_long((long)ret,DEC);
		#endif
#endif
		return ret;
}


int phy_ccaCtrl(CCA_STATE state) {

		uint8_t reg_cca_cntl;
		uint8_t reg_idl_wait;
		uint8_t reg_data;
		int status = STATUS_OK;

		phy_set_trx_state(PHY_ST_FORCE_TRXOFF);

		if (state == CCA_FAILURE || state == CCA_IDLE){
				reg_data = 0x00;
				reg_wr(REG_ADR_CCA_SYNC_OFF, &reg_data, 1);
				reg_data = store_cca_sync_off;
				reg_wr(REG_ADR_DEMSET38, &reg_data, 1);
				reg_cca_cntl = 0x00;
				reg_idl_wait = 0x00;
				reg_wr(REG_ADR_IDLE_WAIT_L, &reg_idl_wait, 1);
				reg_wr(REG_ADR_CCA_CNTRL, &reg_cca_cntl, 1);

				reg_wr(REG_ADR_CH_SET, &base_channel, 1);
				dsss_param.cca_cnt = 0;

				if(state == CCA_FAILURE){
						reg_data = 0x22; // modem reset
						reg_wr(REG_ADR_RST_SET, &reg_data, 1);
				}
		}else{
				if (state == CCA_FAST) {
						reg_cca_cntl = 0x10;
						reg_idl_wait = 0x00;

					if ((dsss_param.modulation == PHY_MODULATION_DSSS) && (dsss_param.page == PHY_DATARATE_200K)) {
								if (!dsss_param.cca_cnt){
										reg_data = 0x00; reg_wr(REG_ADR_INT_SOURCE_GRP1, &reg_data, 1);
										reg_data = 0x01; reg_wr(REG_ADR_CCA_SYNC_OFF, &reg_data, 1);
										reg_rd(REG_ADR_DEMSET38, &store_cca_sync_off, 1);
										reg_data = 0x07; reg_wr(REG_ADR_DEMSET38, &reg_data, 1);
										reg_data = 0x22; reg_wr(REG_ADR_RST_SET, &reg_data, 1);

										dsss_param.cca_cnt = PHY_DSSS_MULTI_CCA - 1;
										reg_rd(REG_ADR_CH_SET, &reg_data, 1);
										reg_data -= PHY_DSSS_MULTI_CCA;
										reg_wr(REG_ADR_CH_SET, &reg_data, 1);
#if defined(LAZURITE_IDE) && defined(CCA_DEBUG)
										Serial.print("BASE CH:");
									Serial.println_long((long)base_channel,HEX);
										Serial.print("CCA CH:");
									Serial.println_long((long)reg_data,HEX);
#endif
								}else{
										reg_rd(REG_ADR_CH_SET, &reg_data, 1);
										dsss_param.cca_cnt--;

										if (PHY_DSSS_MULTI_CCA == 2) {
												reg_data += (PHY_DSSS_MULTI_CCA*2);
										}else
										if (PHY_DSSS_MULTI_CCA == 3) {
												reg_data += PHY_DSSS_MULTI_CCA;
										}

										reg_wr(REG_ADR_CH_SET, &reg_data, 1);
#if defined(LAZURITE_IDE) && defined(CCA_DEBUG)
										Serial.print("CCA CH:");
									Serial.println_long((long)reg_data,HEX);
#endif
								}
						}else{
								reg_data = 0x00; reg_wr(REG_ADR_INT_SOURCE_GRP1, &reg_data, 1);
								reg_data = 0x01; reg_wr(REG_ADR_CCA_SYNC_OFF, &reg_data, 1);
								reg_rd(REG_ADR_DEMSET38, &store_cca_sync_off, 1);
								reg_data = 0x07; reg_wr(REG_ADR_DEMSET38, &reg_data, 1);
								reg_data = 0x22; reg_wr(REG_ADR_RST_SET, &reg_data, 1);
						}
				} else
				if (state == IDLE_DETECT) {
						reg_cca_cntl = 0x50;
						reg_idl_wait = 0x64;
				} else
				if (state == CCA_RETRY) {
						phy_backoffTimer();
						reg_cca_cntl = 0x10;
						reg_idl_wait = 0x64;
				}

		 // if (state != CCA_FAST) phy_inten(HW_EVENT_CCA_DONE);
				phy_inten(HW_EVENT_CCA_DONE);

				reg_wr(REG_ADR_IDLE_WAIT_L, &reg_idl_wait, 1);
				reg_wr(REG_ADR_CCA_CNTRL, &reg_cca_cntl, 1);
				reg_data = PHY_ST_RXON;
				reg_wr(REG_ADR_RF_STATUS, &reg_data, 1);
		}
		return status;
}


CCA_STATE phy_ccadone(uint8_t be,uint8_t count, uint8_t retry)
{
		int state;
		uint8_t reg_data;

		phy_cca_be = be;

		// Notice: A following must not change.
	reg_rd(REG_ADR_CCA_CNTRL, &reg_data, 1);
		phy_intclr(HW_EVENT_CCA_DONE | HW_EVENT_RF_STATUS);

		if(reg_data&0x03){
				if ((dsss_param.modulation == PHY_MODULATION_DSSS) && (dsss_param.page == PHY_DATARATE_200K)) {
					 state = CCA_FAILURE;
				}else{
#if 1		// when it force retrying CCA, is zero.
						if(!count){
							 state = IDLE_DETECT;
						}else
#endif
						if(count < retry){
							 state = CCA_RETRY;
						}else{
							 state = CCA_FAILURE;
						}
				}
		}else{
				if (dsss_param.cca_cnt){
						state = CCA_FAST;
				}else{
						state = CCA_IDLE;
				}
		}
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG)printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
		return state;
}


void phy_txdone(void)
{
		phy_intclr(HW_EVENT_TX_DONE | HW_EVENT_TX_FIFO_DONE | HW_EVENT_RF_STATUS);
}


#if defined(LAZURITE_IDE) && defined(SERIAL_DEBUG)
uint16_t per_err_cnt = 0;
uint16_t per_ok_cnt = 0;
#endif

int phy_rxdone(BUFFER *buff)
{
		int status=STATUS_OK;
		uint8_t reg_data[2];
		uint8_t err_status;
		uint8_t rx_done;
		uint8_t int_status;
		uint8_t fifo_last;

		phy_mesg();

		// Notice: A following must not change.
		reg_rd(REG_ADR_INT_SOURCE_GRP2, &int_status, 1);
		reg_rd(REG_ADR_RD_FIFO_LAST, &fifo_last, 1);

		err_status = int_status&0x9a; // sync error | fifo errr | length error | crc err0r
		rx_done = int_status&0x01;

		if(err_status){
			status=-EBADE;
			goto error;
		}

		// Set length
		if (!fifo_param.fifo_temp_len) {
				if (dsss_param.modulation == PHY_MODULATION_DSSS && dsss_param.ctrl_reg != PHY_DSSS_SIZE_FREE){
						buff->len = dsss_param.size;
				}else{
						reg_rd(REG_ADR_RX_PKT_LEN_H, reg_data, 2);
						buff->len = (((unsigned int)reg_data[0] << 8) | reg_data[1]) & 0x07ff; 
				}

				fifo_param.fifo_temp_len = buff->len;
				fifo_param.fifo_temp_buf = buff->data;

				// first is 2 byte only.
				if (fifo_param.fifo_temp_len > PHY_FIFO_DATA_TRG){
						reg_data[0] = 0x80 | PHY_FIFO_DATA_TRG;
						reg_data[1] = 0x80 | (PHY_FIFO_DATA_TRG - 1);
						reg_wr(REG_ADR_RXFIFO_THRH, reg_data, 2);
						phy_inten(HW_EVENT_FIFO_FULL);
				}else{
						reg_data[0] = 0;
						reg_data[1] = 0;
						reg_wr(REG_ADR_RXFIFO_THRH, reg_data, 2);
						phy_inten(HW_EVENT_RX_DONE);
				}
				phy_intclr(HW_EVENT_FIFO_FULL | HW_EVENT_FIFO_EMPTY);
				status=1;
				goto nextState;
		}else{
		// fifo read
			if(rx_done){
					fifo_rd(REG_ADR_RD_RX_FIFO, buff->data, fifo_param.fifo_temp_buf, fifo_param.fifo_temp_len);
			}else{
					if (fifo_param.fifo_temp_len > PHY_FIFO_DATA_TRG){
							fifo_rd(REG_ADR_RD_RX_FIFO, buff->data, fifo_param.fifo_temp_buf, PHY_FIFO_DATA_READ); 
							fifo_param.fifo_temp_len -= PHY_FIFO_DATA_READ;
							fifo_param.fifo_temp_buf += PHY_FIFO_DATA_READ;
					}

					if (fifo_param.fifo_temp_len > PHY_FIFO_DATA_TRG){
							reg_data[0] = 0x80 | PHY_FIFO_DATA_TRG;
							reg_data[1] = 0x80 | (PHY_FIFO_DATA_TRG - 1);
							reg_wr(REG_ADR_RXFIFO_THRH, reg_data, 2);
							phy_inten(HW_EVENT_FIFO_FULL);
					}else{
							reg_data[0] = 0;
							reg_data[1] = 0;
							reg_wr(REG_ADR_RXFIFO_THRH, reg_data, 2);
							phy_inten(HW_EVENT_RX_DONE);
					}
					phy_intclr(HW_EVENT_FIFO_FULL | HW_EVENT_FIFO_EMPTY);
					status=1;
					goto nextState;
			}
		}

		phy_set_trx_state(PHY_ST_FORCE_TRXOFF);
		buff->len -= 2; // crc data
		buff->len += 1; // add ed result
		reg_rd(REG_ADR_ED_RSLT,reg_data,1); buff->data[buff->len] = reg_data[0];

error:
		phy_rst();
		phy_intclr(~(HW_EVENT_ALL_MASK));

nextState:
#ifdef LAZURITE_IDE
		#ifdef SERIAL_DEBUG
		Serial.print("INT GRP2:");
		Serial.print_long((long)int_grp2,HEX);

		if (crc_err) {
				per_err_cnt++;
				Serial.print(" CRC ERR:");
				Serial.println_long((long)per_err_cnt,DEC);
		}else{
				per_ok_cnt++;
				Serial.print(" CRC OK:");
				Serial.print_long((long)per_ok_cnt,DEC);
		}

		Serial.print(" RX_LEN:");
		Serial.print_long((long)buff->len,DEC);
		Serial.print(" DATA:");
		{
				uint8_t cnt;
		for(cnt=0;cnt<buff->len;cnt++)
		{
			Serial.print_long(buff->data[cnt],HEX);
			Serial.print(" ");
		}
		Serial.println("");
		}
		#endif
#else
	if(module_test & MODE_PHY_DEBUG){
		printk(KERN_INFO"%s,%s,%lx,total length:%d,fifo_last:%d,status:0x%x,temp len:%d,seq:%d\n",__FILE__,__func__,
				(unsigned long)buff->data,buff->len,fifo_last,status,fifo_param.fifo_temp_len,buff->data[4]);
		// PAYLOADDUMP(buff->data,buff->len);
	}
#endif
	return status;
}


void phy_stop(void)
{
	uint8_t reg_data = 0x06;
	reg_wr(REG_ADR_SLEEP_WU_SET, &reg_data, 1);

		phy_set_trx_state(PHY_ST_FORCE_TRXOFF);
		phy_intclr(~(HW_EVENT_ALL_MASK));
		phy_inten(HW_EVENT_ALL_MASK);
		phy_rst();
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}


void phy_clrAddrFilt(void)
{
		uint8_t reg_data[3];

		if (dsss_param.modulation == PHY_MODULATION_FSK){
				reg_data[0] = 0x00;
				reg_data[1] = 0x00;
				reg_data[2] = 0x00;
				reg_wr(REG_ADR_C_CHECK_CTRL, reg_data, 3);
		}
}


void phy_addrFilt(uint16_t panid, uint8_t *ieee_addr, uint16_t uc_addr, uint16_t bc_addr)
{
		uint8_t reg_data[4];

/*
#if 0 // unicast recive
		// address filter
		if (dsss_param.modulation == PHY_MODULATION_FSK){
			reg_data[0] = 0x80;
			reg_data[1] = 0x00;
			reg_data[2] = 0x0F;
		}else {
			reg_data[0] = 0x00;
			reg_data[1] = 0x00;
			reg_data[2] = 0x00;
		}
		reg_wr(REG_ADR_C_CHECK_CTRL, reg_data, 3);

		reg_data[0] = panid>>0&0xff;
		reg_data[1] = panid>>8&0xff;
		reg_data[2] = uc_addr>>0&0xff;
		reg_data[3] = uc_addr>>8&0xff;
		reg_wr(REG_ADR_A_FIELD_CODE1, reg_data, 4);
#else // broadcast recive
		reg_data[0] = 0x80;
		reg_data[1] = 0x00;
		reg_data[2] = 0x0F;
		reg_wr(REG_ADR_C_CHECK_CTRL, reg_data, 3);

		reg_data[0] = 0xff;
		reg_data[1] = 0xff;
		reg_data[2] = 0xff;
		reg_data[3] = 0xff;
		reg_wr(REG_ADR_A_FIELD_CODE1, reg_data, 4);
#endif
*/
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG){

			printk(KERN_INFO"%s,%s\n",__FILE__,__func__);

				reg_rd(REG_ADR_A_CHECK_CTRL, reg_data, 1);
				printk(KERN_INFO"ADDFIL_CNTRL: %s,%s,%x\n",__FILE__,__func__,reg_data[0]);

				reg_rd(REG_ADR_A_FIELD_CODE1, reg_data, 4);
				printk(KERN_INFO"ADDFIL1: %s,%s,%x\n",__FILE__,__func__,reg_data[0]);
				printk(KERN_INFO"ADDFIL2: %s,%s,%x\n",__FILE__,__func__,reg_data[1]);
				printk(KERN_INFO"ADDFIL3: %s,%s,%x\n",__FILE__,__func__,reg_data[2]);
				printk(KERN_INFO"ADDFIL4: %s,%s,%x\n",__FILE__,__func__,reg_data[3]);
				printk(KERN_INFO"MODULATION: %s,%s,%x\n",__FILE__,__func__,dsss_param.modulation);
		}
#endif
}


void phy_ed(uint8_t *level, uint8_t rfMode)
{
		uint8_t i,temp_ed=0;
		uint8_t ch_val;
		uint8_t reg_data;

		if(!rfMode)phy_set_trx_state(PHY_ST_RXON);

		if ((dsss_param.modulation == PHY_MODULATION_DSSS) && (dsss_param.page == PHY_DATARATE_200K)) {
				reg_rd(REG_ADR_CH_SET, &ch_val, 1);
				ch_val -= PHY_DSSS_MULTI_CCA;
				*level = 0;
				temp_ed = 0;

				reg_data = 0x30;
				reg_wr(REG_ADR_CCA_CNTRL, &reg_data, 1);

				for(i=0; i < PHY_DSSS_MULTI_CCA; i++){
						reg_wr(REG_ADR_CH_SET, &ch_val, 1);
						HAL_delayMicroseconds(100);
						reg_rd(REG_ADR_ED_RSLT, &temp_ed, 1);
					 if(*level < temp_ed) *level = temp_ed;
#if defined(LAZURITE_IDE) && defined(CCA_DEBUG)
						Serial.print("CCA CH:");
						Serial.print_long((long)ch_val,DEC);
						Serial.print("VALUE: 0x");
						Serial.println_long((long)temp_ed,HEX);
#endif
						ch_val += PHY_DSSS_MULTI_CCA;
				}
				reg_data = 0x80;
				reg_wr(REG_ADR_CCA_CNTRL, &reg_data, 1);
				reg_wr(REG_ADR_CH_SET, &base_channel, 1);
				reg_data = 0x00;
				reg_wr(REG_ADR_CCA_CNTRL, &reg_data, 1);
		}else{
				reg_rd(REG_ADR_ED_RSLT, level, 1);
		}

		if(!rfMode)phy_set_trx_state(PHY_ST_FORCE_TRXOFF);
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s,ED_value:%x\n",__FILE__,__func__,*level);
#endif
}


void phy_sleep(void)
{
/*
		uint8_t reg_data;
		phy_set_trx_state(PHY_ST_FORCE_TRXOFF);
	reg_rd(REG_ADR_SLEEP_WU_SET, &reg_data, 1);
	reg_data |=  0x01;
	reg_wr(REG_ADR_SLEEP_WU_SET, &reg_data, 1);
		reg_data = 0x00;
	reg_wr(REG_ADR_2DIV_CNTRL, &reg_data, 1);
*/
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}


void phy_cleanup(void)
{
	uint8_t reg_data;

	phy_set_trx_state(PHY_ST_FORCE_TRXOFF);
	phy_rst();
		reg_data = 0x00;
		reg_wr(REG_ADR_INT_SOURCE_GRP2, &reg_data, 1);
		reg_wr(REG_ADR_INT_SOURCE_GRP3, &reg_data, 1);
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}


void phy_monitor(void){
#ifndef LAZURITE_IDE
		uint8_t rdata[4];
		reg_rd(0, 0x24, rdata, 4);
	printk(KERN_INFO"INT SOURCE:: %x,%x,%x,%x\n", rdata[0],rdata[1],rdata[2],rdata[3]);
		reg_rd(0, 0x2A, rdata, 4);
	printk(KERN_INFO"INT ENABLE:: %x,%x,%x,%x\n", rdata[0],rdata[1],rdata[2],rdata[3]);
		reg_rd(0, 0x6c, rdata, 1);
	printk(KERN_INFO"RF STATUS:: %x\n", rdata[0]);
		reg_rd(0, 0x15, rdata, 1);
		printk(KERN_INFO"RF CCA CNTL:: %x\n", rdata[0]);
#endif
}


// following function is for debug. and test.bin use it.

void phy_regread(uint8_t bank, uint8_t addr, uint8_t *data, uint8_t size) {
		reg_rd(bank, addr, data, size);
}


void phy_regwrite(uint8_t bank, uint8_t addr, uint8_t *data, uint8_t size) {
		reg_wr(bank, addr, data, size);
}

#ifdef LAZURITE_IDE
void phy_regdump(void)
{
		uint8_t dump_cnt,dat_dump,reg_data[4];


		Serial.println("-----------------/ bank0 /---------------");
		for(dump_cnt=0; dump_cnt <= 0x7F; dump_cnt++) {
				reg_rd(0, dump_cnt, reg_data, 1); dat_dump = reg_data[0];
				if (dump_cnt == 0) Serial.print(""); 
				else if (dump_cnt%16 == 0) Serial.println("");
			else Serial.print(" ");
				if(dat_dump < 16) Serial.print("0");
			Serial.print_long((long)dat_dump,HEX);
	}
	Serial.println("");

		Serial.println("-----------------/ bank1 /---------------");
		for(dump_cnt=0; dump_cnt <= 0x7F; dump_cnt++) {
				reg_rd(1, dump_cnt, reg_data, 1); dat_dump = reg_data[0];
				if (dump_cnt == 0) Serial.print(""); 
				else if (dump_cnt%16 == 0) Serial.println("");
			else Serial.print(" ");
				if(dat_dump < 16) Serial.print("0");
			Serial.print_long((long)dat_dump,HEX);
		}
	Serial.println("");

		Serial.println("-----------------/ bank2 /---------------");
		for(dump_cnt=0; dump_cnt <= 0x7F; dump_cnt++) {
				reg_rd(2, dump_cnt, reg_data, 1); dat_dump = reg_data[0];
				if (dump_cnt == 0) Serial.print(""); 
				else if (dump_cnt%16 == 0) Serial.println("");
			else Serial.print(" ");
				if(dat_dump < 16) Serial.print("0");
			Serial.print_long((long)dat_dump,HEX);
		}
	Serial.println("");

		Serial.println("-----------------/ bank3 /---------------");
		for(dump_cnt=0; dump_cnt <= 0x7F; dump_cnt++) {
				reg_rd(3, dump_cnt, reg_data, 1); dat_dump = reg_data[0];
				if (dump_cnt == 0) Serial.print(""); 
				else if (dump_cnt%16 == 0) Serial.println("");
			else Serial.print(" ");
				if(dat_dump < 16) Serial.print("0");
			Serial.print_long((long)dat_dump,HEX);
		}
	Serial.println("");

		Serial.println("-----------------/ bank6 /---------------");
		for(dump_cnt=0; dump_cnt <= 0x7F; dump_cnt++) {
				reg_rd(6, dump_cnt, reg_data, 1); dat_dump = reg_data[0];
				if (dump_cnt == 0) Serial.print(""); 
				else if (dump_cnt%16 == 0) Serial.println("");
			else Serial.print(" ");
				if(dat_dump < 16) Serial.print("0");
			Serial.print_long((long)dat_dump,HEX);
		}
	Serial.println("");

		Serial.println("-----------------/ bank7 /---------------");
		for(dump_cnt=0; dump_cnt <= 0x7F; dump_cnt++) {
				reg_rd(7, dump_cnt, reg_data, 1); dat_dump = reg_data[0];
				if (dump_cnt == 0) Serial.print(""); 
				else if (dump_cnt%16 == 0) Serial.println("");
			else Serial.print(" ");
				if(dat_dump < 16) Serial.print("0");
			Serial.print_long((long)dat_dump,HEX);
		}
	Serial.println("");

		Serial.println("-----------------/ bank10 /---------------");
		for(dump_cnt=0; dump_cnt <= 0x7F; dump_cnt++) {
				reg_rd(10, dump_cnt, reg_data, 1); dat_dump = reg_data[0];
				if (dump_cnt == 0) Serial.print(""); 
				else if (dump_cnt%16 == 0) Serial.println("");
			else Serial.print(" ");
				if(dat_dump < 16) Serial.print("0");
			Serial.print_long((long)dat_dump,HEX);
		}
	Serial.println("");
}
#endif
