/* phy_ml7396.c - ml7396 hardware interface for lazurite
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


#ifdef SUBGHZ_OTA
#pragma SEGCODE "OTA_SEGCODE"
#pragma SEGINIT "OTA_SEGINIT"
#pragma SEGNOINIT "OTA_SEGNOINIT"
#pragma SEGCONST "OTA_SEGCONST"
#endif
#ifdef LAZURITE_IDE
	#include <common.h>
	#include "lazurite.h"
#else
	#include <linux/stddef.h>
	#include "../hwif/random-lzpi.h"
	#include "../common-lzpi.h"
	#include "../hwif/hal-lzpi.h"
#endif
	// COMMON HEADER for LAZURITE
#include "../phy.h"
#include "phy_ml7396.h"
#include "../hwif/hal.h"
#include "../errno.h"
#include "../endian.h"
#include "../common_subghz.h"

/*
	 --------------------------------------------------------------
	 Define section
	 --------------------------------------------------------------
	 */
#define BUFFER_SIZE 1+254+2				// WR: FIFO_HDR(1)+PSDU(254)+CRC(2)
																	// RD: PSDU(254)+CRC(2)+ED(1)
const uint8_t device_id_bp3596[] =   {0x00,0x1d,0x12,0x90};
const uint8_t device_id_lazurite[] = {0x00,0x1d,0x12,0xd0};
//#define DEIVE_ID_ROHM  0x90
//#define DEIVE_ID_LAPIS 0xD0

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
#define HW_EVENT_ALL_MASK     0x00000000L  /* Interrupt all mask */
#define HW_EVENT_VCO_CAL_DONE 0x00000004L  /* VCO CAL DONE */
#define HW_EVENT_ADD_FIL_DONE 0x00000008L  /* Address Filter done */
#define HW_EVENT_FIFO_CLEAR   0x000000C0L  /* FIFO_EMPTY */
#define HW_EVENT_FIFO_EMPTY   0x00000010L  /* FIFO_EMPTY */
#define HW_EVENT_FIFO_FULL    0x00000020L  /* FIFO_FULL */
#define HW_EVENT_CCA_DONE     0x00000100L  /* CCA DONE */
#define HW_EVENT_RF_STATUS    0x00000400L  /* RF status */
#define HW_EVENT_TX_DONE      0x00030000L  /* TX complete */
#define HW_EVENT_RX_DONE      0x000C0000L  /* RX complete */
#define HW_EVENT_CRC_ERROR    0x00300000L  /* CRC error */
#define HW_EVENT_TX_FIFO_DONE 0x00C00000L  /* FIFO complete */
#define HW_EVENT_TIMEOUT      0x80000000L  /* Timer timeout */

/* software interrupt */
#define SW_EVENT_SETUP   1  /* 初期化 */
#define SW_EVENT_RXSTART 2  /* パケット受信開始 */
#define SW_EVENT_RXSTOP  3  /* パケット受信停止 */
#define SW_EVENT_TXSTART 4  /* パケット送信開始 */
#define SW_EVENT_SLEEP   5  /* 省電力状態へ移行 */
#define SW_EVENT_WAKEUP  6  /* 省電力状態から復帰 */

#define PHY_REG_SET_TX_DONE_RX   0x20
#define PHY_REG_SET_TX_DONE_OFF  0x10

#define UNIT_BACKOFF_PERIOD  320
#define DEFAUL_BAKOF        1000

#define PHY_INIT  1
#define PHY_SLEEP 2
#define PHY_SETUP 3

static struct {
	uint8_t page:3;
	uint8_t antsw:1;
	uint8_t state:3;
	uint8_t txPower;
	uint8_t ch;
} local_params;
/*
	 ---------------------------------------------------------------
	 Struct and Enum section
	 ---------------------------------------------------------------
	 */

static struct {
	uint8_t bank;           // back number
	uint8_t rdata[8];     // input buffer 
	uint8_t wdata[8];     // outpu buffer
	uint8_t rfifo[BUFFER_SIZE];     // input buffer 
	uint8_t wfifo[BUFFER_SIZE];     // outpu buffer
}reg = {
	0xff  /* bank */
};

/* register setting fixed number */

typedef struct {
	uint8_t rate;                /* rate setting */
	uint32_t freq[38];           /* frequency setting */
	uint32_t chspc;              /* bandwidth setting */
	uint32_t iffreq;             /* IF frequency setting */ 
	uint32_t iffreq_cca;         /* IF frequency setting (CCA) */
	uint16_t coef, ref;          /* BPF setting */
	uint16_t coef_cca, ref_cca;  /* BPF setting (CCA) */
	uint16_t fdev;               /* GFSK frequency shift setting */
	uint8_t reg1;                /* Concealment of register setting */
	uint8_t div;                 /* diversity search setting */
} REGSET;

typedef enum{
	PHY_ST_FORCE_TRXOFF=0x03,
	PHY_ST_RXON=0x06,
	PHY_ST_TXON=0x09,
	PHY_ST_TRXOFF=0x08
} PHY_TRX_STATE;

/* setting fixed number (I do not handle the floating point arithmetic with the CPU and entrust all a compiler) */
static const REGSET regset_50kbps = {
	0x10,                               /* rate */
	{                                   /* freq[] (bandwidth 200kHz) */
		FIXQ(920.6, 20, uint32_t),        /* Channel=24 */
		FIXQ(920.8, 20, uint32_t),        /* Channel=25 */
		FIXQ(921.0, 20, uint32_t),        /* Channel=26 */
		FIXQ(921.2, 20, uint32_t),        /* Channel=27 */
		FIXQ(921.4, 20, uint32_t),        /* Channel=28 */
		FIXQ(921.6, 20, uint32_t),        /* Channel=29 */
		FIXQ(921.8, 20, uint32_t),        /* Channel=30 */
		FIXQ(922.0, 20, uint32_t),        /* Channel=31 */
		FIXQ(922.2, 20, uint32_t),        /* Channel=32 */
		FIXQ(922.4, 20, uint32_t),        /* Channel=33 */
		FIXQ(922.6, 20, uint32_t),        /* Channel=34 */
		FIXQ(922.8, 20, uint32_t),        /* Channel=35 */
		FIXQ(923.0, 20, uint32_t),        /* Channel=36 */
		FIXQ(923.2, 20, uint32_t),        /* Channel=37 */
		FIXQ(923.4, 20, uint32_t),        /* Channel=38 */
		FIXQ(923.6, 20, uint32_t),        /* Channel=39 */
		FIXQ(923.8, 20, uint32_t),        /* Channel=40 */
		FIXQ(924.0, 20, uint32_t),        /* Channel=41 */
		FIXQ(924.2, 20, uint32_t),        /* Channel=42 */
		FIXQ(924.4, 20, uint32_t),        /* Channel=43 */
		FIXQ(924.6, 20, uint32_t),        /* Channel=44 */
		FIXQ(924.8, 20, uint32_t),        /* Channel=45 */
		FIXQ(925.0, 20, uint32_t),        /* Channel=46 */
		FIXQ(925.2, 20, uint32_t),        /* Channel=47 */
		FIXQ(925.4, 20, uint32_t),        /* Channel=48 */
		FIXQ(925.6, 20, uint32_t),        /* Channel=49 */
		FIXQ(925.8, 20, uint32_t),        /* Channel=50 */
		FIXQ(926.0, 20, uint32_t),        /* Channel=51 */
		FIXQ(926.2, 20, uint32_t),        /* Channel=52 */
		FIXQ(926.4, 20, uint32_t),        /* Channel=53 */
		FIXQ(926.6, 20, uint32_t),        /* Channel=54 */
		FIXQ(926.8, 20, uint32_t),        /* Channel=55 */
		FIXQ(927.0, 20, uint32_t),        /* Channel=56 */
		FIXQ(927.2, 20, uint32_t),        /* Channel=57 */
		FIXQ(927.4, 20, uint32_t),        /* Channel=58 */
		FIXQ(927.6, 20, uint32_t),        /* Channel=59 */
		FIXQ(927.8, 20, uint32_t),        /* Channel=60 */
		FIXQ(928.0, 20, uint32_t)         /* Channel=61 */
	},
	FIXQ(0.200, 20, uint32_t),          /* chspc = 200kHz */
	FIXQ(0.250, 20, uint32_t),          /* iffreq = 250kHz */
	FIXQ(0.250, 20, uint32_t),          /* iffreq_cca = 250kHz */
	FIXQ(1.440, 14, uint16_t), 0x034b,  /* coef = 1.440, ref */
	FIXQ(1.440, 14, uint16_t), 0x034b,  /* coef_cca = 1.440, ref_cca */
	0x02d8,                             /* fdev */
	0x24,                               /* reg1 */
	0x11                                /* div = more than 0x11 */
};
static const REGSET regset_100kbps = {
	0x11,                               /* rate */
	{                                   /* freq[] (bandwidth 400kHz) */
		FIXQ(920.7, 20, uint32_t),        /* Channel=24,25 */
		FIXQ(920.9, 20, uint32_t),        /* Channel=25,26 */
		FIXQ(921.1, 20, uint32_t),        /* Channel=26,27 */
		FIXQ(921.3, 20, uint32_t),        /* Channel=27,28 */
		FIXQ(921.5, 20, uint32_t),        /* Channel=28,29 */
		FIXQ(921.7, 20, uint32_t),        /* Channel=29,30 */
		FIXQ(921.9, 20, uint32_t),        /* Channel=30,31 */
		FIXQ(922.1, 20, uint32_t),        /* Channel=31,32 */
		FIXQ(922.3, 20, uint32_t),        /* Channel=32,33 Reserved channel */
		FIXQ(922.5, 20, uint32_t),        /* Channel=33,34 */
		FIXQ(922.7, 20, uint32_t),        /* Channel=34,35 */
		FIXQ(922.9, 20, uint32_t),        /* Channel=35,36 */
		FIXQ(923.1, 20, uint32_t),        /* Channel=36,37 */
		FIXQ(923.3, 20, uint32_t),        /* Channel=37,38 */
		FIXQ(923.5, 20, uint32_t),        /* Channel=38,39 */
		FIXQ(923.7, 20, uint32_t),        /* Channel=39,40 */
		FIXQ(923.9, 20, uint32_t),        /* Channel=40,41 */
		FIXQ(924.1, 20, uint32_t),        /* Channel=41,42 */
		FIXQ(924.3, 20, uint32_t),        /* Channel=42,43 */
		FIXQ(924.5, 20, uint32_t),        /* Channel=43,44 */
		FIXQ(924.7, 20, uint32_t),        /* Channel=44,45 */
		FIXQ(924.9, 20, uint32_t),        /* Channel=45,46 */
		FIXQ(925.1, 20, uint32_t),        /* Channel=46,47 */
		FIXQ(925.3, 20, uint32_t),        /* Channel=47,48 */
		FIXQ(925.5, 20, uint32_t),        /* Channel=48,49 */
		FIXQ(925.7, 20, uint32_t),        /* Channel=49,50 */
		FIXQ(925.9, 20, uint32_t),        /* Channel=50,51 */
		FIXQ(926.1, 20, uint32_t),        /* Channel=51,52 */
		FIXQ(926.3, 20, uint32_t),        /* Channel=52,53 */
		FIXQ(926.5, 20, uint32_t),        /* Channel=53,54 */
		FIXQ(926.7, 20, uint32_t),        /* Channel=54,55 */
		FIXQ(926.9, 20, uint32_t),        /* Channel=55,56 */
		FIXQ(927.1, 20, uint32_t),        /* Channel=56,57 */
		FIXQ(927.3, 20, uint32_t),        /* Channel=57,58 */
		FIXQ(927.5, 20, uint32_t),        /* Channel=58,59 */
		FIXQ(927.7, 20, uint32_t),        /* Channel=59,60 */
		FIXQ(927.9, 20, uint32_t),        /* Channel=60,61 */
		FIXQ(927.9, 20, uint32_t)         /* Channel=60,61 (60 and 61 is same) */
	},
	FIXQ(0.400, 20, uint32_t),          /* chspc = 400kHz */
	FIXQ(0.180, 20, uint32_t),          /* iffreq = 180kHz */
	FIXQ(0.250, 20, uint32_t),          /* iffreq_cca = 250kHz */
	FIXQ(1.000, 14, uint16_t), 0x024a,  /* coef = 1.000, ref */
	FIXQ(0.480, 14, uint16_t), 0x0119,  /* coef_cca = 1.000, ref_cca */
	0x05b0,                             /* fdev */
	0x27,                               /* reg1 */
	0x16                                /* div = more than 0x16 */
};



static struct phy_param phy;

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
static void regbank(uint8_t bank) {

	uint8_t reg_data[2];
	switch (bank) {
		case 0:  /* BANK0 */
		case 1:  /* BANK1 */
		case 2:  /* BANK2 */
		case 8:  /* BANK0 + access enable */
		case 9:  /* BANK1 + access enable */
		case 10: /* BANK2 + access enable */
			if (bank != reg.bank) {
				reg_data[0] = (uint8_t)((0x00<<1)|0x01);
				reg_data[1] = (uint8_t)(bank&0x03);
				if(bank > 2) reg_data[1] = (uint8_t)(reg_data[1] | 0x80);
				HAL_SPI_transfer(reg_data,2,reg.rdata,0);
				reg.bank = bank;
			}
			break;
		case 0xff:
			reg.bank = bank;
			break;
		default:
			break;
	}
}


/******************************************************************************/
/*! @brief write register
 * bank: bank number
 * addr: write address
 * data: write data
 * size: data size
 ******************************************************************************/

static void reg_wr(uint8_t bank, uint8_t addr,uint8_t size)
{
	regbank(bank);
	reg.wdata[0] = (uint8_t)((addr << 1) | 0x01);
	HAL_SPI_transfer(reg.wdata,size,reg.rdata,0);
}

static void fifo_wr(uint8_t bank, uint8_t addr)
{
	uint8_t *p_header = phy.out.data -1;
	uint16_t size = phy.out.len;
	static const char s1[] = "PHY BUFFER ERROR";

	regbank(bank);
	*p_header = (uint8_t)((addr << 1) | 0x01);

	if(size <= phy.out.size) {
		HAL_SPI_transfer(p_header,size+1,reg.rdata,0);
	} else {
		alert(s1);
	}

}


/******************************************************************************/
/*! @brief read register
 * bank: bank number
 * addr: read address
 * data: store readind data
 * size: data size
 ******************************************************************************/
static void reg_rd(uint8_t bank, uint8_t addr, uint8_t size)
{
	regbank(bank);
	reg.wdata[0] = (uint8_t)((addr << 1) | 0x00);
	HAL_SPI_transfer(reg.wdata,1,reg.rdata,size);
}


static void fifo_rd(uint8_t bank, uint8_t addr)
{
	regbank(bank);
	reg.wdata[0] = (uint8_t)((addr << 1) | 0x00);
	HAL_SPI_transfer(reg.wdata,1,phy.in.data,phy.in.len);
}

/******************************************************************************/
/*! @brief Enable interrupt / Diseable interrupt
 * @detail Original function was REG_INTEN
 * @issue
 ******************************************************************************/
static void phy_inten(uint32_t inten)
{
	reg.wdata[1] = (uint8_t)((uint8_t)((inten) >>  0));
	reg.wdata[2] = (uint8_t)((uint8_t)((inten) >>  8));
	reg.wdata[3] = (uint8_t)((uint8_t)((inten) >> 16));
	reg.wdata[4] = (uint8_t)((uint8_t)((inten) >> 24));
	reg_wr(REG_ADR_INT_EN_GRP1,5);
}


/******************************************************************************/
/*! @brief Clear interrupt 
 * @detail Original function was REG_INTCLR
 * @issue
 ******************************************************************************/
static void phy_intclr(uint32_t intclr)
{
	reg.wdata[1] = (uint8_t)(~(uint8_t)((intclr) >>  0));
	reg.wdata[2] = (uint8_t)(~(uint8_t)((intclr) >>  8));
	reg.wdata[3] = (uint8_t)(~(uint8_t)((intclr) >> 16));
	reg.wdata[4] = (uint8_t)(~(uint8_t)((intclr) >> 24));
	reg_wr(REG_ADR_INT_SOURCE_GRP1, 5);
}

uint32_t phy_intsrc(void)
{
	uint32_t intsrc=0;
	reg_rd(REG_ADR_INT_SOURCE_GRP1, 4);
	memcpy(&intsrc,reg.rdata,4);
	return intsrc;
}

static void phy_trx_state(PHY_TRX_STATE state) {

	reg.wdata[1] = (uint8_t)state;
	reg_wr(REG_ADR_RF_STATUS, 2);
}

static void phy_reset(void)
{
	HAL_GPIO_setValue(PHY_RESETN,LOW);
	HAL_delayMicroseconds(2000L);
	HAL_GPIO_setValue(PHY_RESETN,HIGH);
	HAL_delayMicroseconds(1000L);
}

static bool vco_cal(void) {

	uint8_t cycle = 0;
	static const char s1[] = "vco_cal error";
	reg.wdata[1]=0x01;
	reg_wr(REG_ADR_VCO_CAL_START, 2);
	do {
		cycle++;
		HAL_delayMicroseconds(100L);
		reg_rd(REG_ADR_INT_SOURCE_GRP1, 1);
		if(cycle > 100) {
			alert(s1);
			phy_monitor();
			local_params.state = PHY_INIT;
			goto error;
		}
	} while (!(reg.rdata[0] & 0x04));
	phy_intclr((uint32_t)HW_EVENT_VCO_CAL_DONE);
	return true;
error:
	return false;
}

/******************************************************************************/
/*! @brief Interrupt handler registration of the ML7396 module
 * @detail Handler of the interrupt that SINTN terminal generates at 'L' level
 ******************************************************************************/
int phy_sint_handler(void (*func)(void))
{
	HAL_GPIO_setInterrupt(func);
	return STATUS_OK;
}

/******************************************************************************/
/*! @brief time-out interrupt count start
 * @detail I produce an interrupt after progress at designation time
 * msec: Time before producing a time-out interrupt (appoint it by a msec unit)
 ******************************************************************************/
int phy_timer_start(uint16_t msec,void (*func)(void))
{
	HAL_TIMER_start(msec, func);
	return STATUS_OK;
}

/******************************************************************************/
/*! @brief time-out interrupt count start
 * @detail I produce an interrupt after progress at designation time
 * msec: Time before producing a time-out interrupt (appoint it by a msec unit)
 ******************************************************************************/
int phy_timer_stop(void)
{
	HAL_TIMER_stop();
	return STATUS_OK;
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
{
	uint8_t device_id[4];
	uint8_t eui64_extend_type;
	const REGSET *regset;
	static const char s1[] = "unsupported device1";
	static const char s2[] = "unsupported device2";
	static uint8_t reg_antsw;

	// CLK START
#ifdef LAZURITE_IDE
	HAL_spi0_sleep = 2;
#endif
	reg.wdata[1] = 0x0f, reg_wr(REG_ADR_CLK_SET,             2);
#ifdef LAZURITE_IDE
	HAL_spi0_sleep = 0;
#endif

	// Check Parameters
#ifdef JP
	switch(page) {
		case 1:			// 50kbps
			if (ch < 24 || ch > 61) {
				return -EINVAL;
			}
			regset = &regset_50kbps;
			break;
		case 2:			// 100kbps
			if ((ch < 24 || ch > 60) || (ch == 32)){
				return -EINVAL;
			}
			regset = &regset_100kbps;
			break;
		default:
			return -EINVAL;
			break;
	}
#elif TW
	switch(page) {
		case 1:			// 50kbps
			if (ch < 24 || ch > 44) {
				return -EINVAL;
			}
			regset = &regset_50kbps;
			break;
		case 2:			// 100kbps
			if (ch < 24 || ch > 43) {
				return -EINVAL;
			}
			regset = &regset_100kbps;
			break;
		default:
			return -EINVAL;
			break;
	}
#endif
	// PHY RST
	reg.wdata[1] = 0x88, reg_wr(REG_ADR_RST_SET, 2);
	phy_trx_state(PHY_ST_FORCE_TRXOFF);
	phy_inten(HW_EVENT_ALL_MASK);
	phy_intclr(~HW_EVENT_FIFO_CLEAR);

	// set calibration parameters
	if((local_params.state == PHY_INIT) || (txPower != local_params.txPower)) {
		uint8_t calibs[5];
		HAL_I2C_read(0x29, calibs, 5);
		reg.wdata[1] = calibs[0], reg_wr(REG_ADR_PA_ADJ3, 2);  /* 20mW rough adjustment */
		reg.wdata[1] = calibs[2], reg_wr(REG_ADR_PA_ADJ1, 2);  /*  1mW rough adjustment */
		reg.wdata[1] = calibs[4], reg_wr(REG_ADR_OSC_ADJ, 2);  /* XA */
		switch (txPower) {
			case  1:  /*  1mW */
				reg.wdata[1] = calibs[3], reg_wr(REG_ADR_PA_REG_FINE_ADJ, 2);
				reg.wdata[1] = 0x01, reg_wr(REG_ADR_PA_CNTRL,             2);
				break;
			case 20:  /* 20mW */
				reg.wdata[1] = calibs[1], reg_wr(REG_ADR_PA_REG_FINE_ADJ, 2);
				reg.wdata[1] = 0x13, reg_wr(REG_ADR_PA_CNTRL,             2);
				break;
			default:
				return -EINVAL;
				break;
		}
	}

	// Set RF antena Switch
	/*  <Antenna definition>
	 *                   920j  MJ2001 BP3596A
	 *  extended_tpye  : 0xFF  0x05     --
	 *  inside(defualt): 0x02  0x06    0x04
	 *  outside        : 0x02  0x02    0x04
	 */
	// Get Device ID
	if((local_params.state == PHY_INIT) || (antsw != local_params.antsw)) {
		HAL_I2C_read(0x20, device_id, 4);
		// BP3596
		if(memcmp(device_id, device_id_bp3596,4) == 0) {
			reg_antsw = 0x04;
		} else if (memcmp(device_id,device_id_lazurite,4) == 0) {
			// Lazurite 920J or MJ2001
			HAL_I2C_read(0xA0, &eui64_extend_type, 1);
			switch(eui64_extend_type) {
				case 0x04:					// Lazurite 920J
				case 0xFF:					// Lazurite 920J
					reg_antsw = 0x02;
					break;
				case 0x05:					// MJ2001
					if (antsw == 0x00) {
						reg_antsw = 0x06;
					}else{
						reg_antsw = 0x02;
					}
					break;
				default:
					alert(s1);
					return -EINVAL;
					break;
			}
			HAL_I2C_read(0x80, &reg.wdata[1],1),  reg_wr(REG_ADR_OSC_ADJ2, 2);  /* Additional parameter */
		} else {
			alert(s2);
		}
	}
	reg.wdata[1] = reg_antsw, reg_wr(REG_ADR_2DIV_CNTRL,      2);

	if(local_params.state == PHY_INIT) {
		// Operation Mode Set
		reg.wdata[1] = 0x10, reg_wr(REG_ADR_ACK_TIMER_EN,       2);		// enable TX_DONE_OFF
		reg.wdata[1] = 0x3a, reg_wr(REG_ADR_PACKET_MODE_SET,    2);		// set MANUAL_TX
		reg.wdata[1] = 0x0b, reg_wr(REG_ADR_FEC_CRC_SET,        2);   // CRC_EN, CRC_MODE=16bit, CRC_DONE

		reg.wdata[1] = 0x22, reg_wr(REG_ADR_RX_PR_LEN_SFD_LEN,  2);
		reg.wdata[1] = 0x00, reg_wr(REG_ADR_SYNC_CONDITION,     2);
		reg.wdata[1] = 0x04, reg_wr(REG_ADR_SYNC_MODE,          2);
		reg.wdata[1] = 0x10, reg_wr(REG_ADR_RAMP_CNTRL,         2);
		reg.wdata[1] = 0x1e, reg_wr(REG_ADR_GAIN_MtoL,          2);
		reg.wdata[1] = 0x02, reg_wr(REG_ADR_GAIN_LtoM,          2);
		reg.wdata[1] = 0x9e, reg_wr(REG_ADR_GAIN_HtoM,          2);
		reg.wdata[1] = 0x02, reg_wr(REG_ADR_GAIN_MtoH,          2);
		reg.wdata[1] = 0x15, reg_wr(REG_ADR_RSSI_ADJ_M,         2);
		reg.wdata[1] = 0x2b, reg_wr(REG_ADR_RSSI_ADJ_L,         2);
		reg.wdata[1] = 0x22, reg_wr(REG_ADR_RSSI_STABLE_TIME,   2);
		reg.wdata[1] = 0xd4, reg_wr(REG_ADR_RSSI_VAL_ADJ,       2);
		reg.wdata[1] = 0x01, reg_wr(REG_ADR_AFC_CNTRL,          2);
		reg.wdata[1] = 0xaa, reg_wr(REG_ADR_PREAMBLE_SET,       2);
		reg.wdata[1] = 0x09, reg_wr(REG_ADR_SFD1_SET1,          2);
		reg.wdata[1] = 0x72, reg_wr(REG_ADR_SFD1_SET2,          2);
		reg.wdata[1] = 0xf6, reg_wr(REG_ADR_SFD1_SET3,          2);
		reg.wdata[1] = 0x72, reg_wr(REG_ADR_SFD1_SET4,          2);
		reg.wdata[1] = 0x5e, reg_wr(REG_ADR_SFD2_SET1,          2);
		reg.wdata[1] = 0x70, reg_wr(REG_ADR_SFD2_SET2,          2);
		reg.wdata[1] = 0xc6, reg_wr(REG_ADR_SFD2_SET3,          2);
		reg.wdata[1] = 0xb4, reg_wr(REG_ADR_SFD2_SET4,          2);
		reg.wdata[1] = 0xb6, reg_wr(REG_ADR_2DIV_GAIN_CNTRL,    2);
		reg.wdata[1] = 0x84, reg_wr(1,0x39,                     2);  /* Hidden register */
		reg.wdata[1] = 0x8f, reg_wr(REG_ADR_PLL_CTRL,           2);
		reg.wdata[1] = 0x32, reg_wr(REG_ADR_RX_ON_ADJ2,         2);
		reg.wdata[1] = 0x0f, reg_wr(REG_ADR_LNA_GAIN_ADJ_M,     2);
		reg.wdata[1] = 0x01, reg_wr(REG_ADR_LNA_GAIN_ADJ_L,     2);
		reg.wdata[1] = 0xff, reg_wr(REG_ADR_MIX_GAIN_ADJ_M,     2);
		reg.wdata[1] = 0xff, reg_wr(REG_ADR_MIX_GAIN_ADJ_L,     2);
		reg.wdata[1] = 0xb4, reg_wr(REG_ADR_TX_OFF_ADJ1,        2);
		reg.wdata[1] = 0x01, reg_wr(REG_ADR_RSSI_SLOPE_ADJ,     2);
		reg.wdata[1] = 0x04, reg_wr(REG_ADR_PA_ON_ADJ,          2);
		reg.wdata[1] = 0x0a, reg_wr(REG_ADR_RX_ON_ADJ,          2);
		reg.wdata[1] = 0x00, reg_wr(REG_ADR_RXD_ADJ,            2);
		// Other Initialization
		reg.wdata[1] = 0x2c, reg_wr(REG_ADR_PRIVATE_BPF_CAP1,   2);  /* Hidden register */
		reg.wdata[1] = 0xc0, reg_wr(REG_ADR_PRIVATE_BPF_CAP2,   2);  /* Hidden register */
		reg.wdata[1] = 0x17, reg_wr(REG_ADR_PRIVATE_BPF_ADJ1,   2);  /* Hidden register */
		reg.wdata[1] = 0x17, reg_wr(REG_ADR_PRIVATE_BPF_ADJ2,   2);  /* Hidden register */

		// Other Initialization
		reg.wdata[1]=0x00;
		reg_wr(REG_ADR_TX_ALARM_LH,2);
		reg_wr(REG_ADR_TX_ALARM_HL,2); 
		reg_wr(REG_ADR_RX_ALARM_LH,2);
		reg_wr(REG_ADR_RX_ALARM_HL,2);

		reg.wdata[1] = 0x0f, reg_wr(REG_ADR_SW_OUT_RAMP_ADJ,     2);
		reg.wdata[1] = 0x08, reg_wr(REG_ADR_IQ_MAG_ADJ,          2);
		reg.wdata[1] = 0x20, reg_wr(REG_ADR_IQ_PHASE_ADJ,        2);
#ifdef LAZURITE_MINI
		reg.wdata[1] = 0x07, reg_wr(REG_ADR_PA_REG_ADJ1,         2);
		reg.wdata[1] = 0x07, reg_wr(REG_ADR_PA_REG_ADJ2,         2);
		reg.wdata[1] = 0x07, reg_wr(REG_ADR_PA_REG_ADJ3,         2);
		reg.wdata[1] = 0x30, reg_wr(REG_ADR_CCA_LEVEL,           2);
#else
		reg.wdata[1] = 0x06, reg_wr(REG_ADR_PA_REG_ADJ1,         2);
		reg.wdata[1] = 0x01, reg_wr(REG_ADR_PA_REG_ADJ2,         2);
		reg.wdata[1] = 0x01, reg_wr(REG_ADR_PA_REG_ADJ3,         2);
		reg.wdata[1] = 0x55, reg_wr(REG_ADR_CCA_LEVEL,           2);
#endif
		reg.wdata[1] = 0x04, reg_wr(REG_ADR_TX_PR_LEN,           2);  /* more than 0x04 */
		reg.wdata[1] = 0x1f, reg_wr(REG_ADR_RSSI_LPF_ADJ,        2);
		reg.wdata[1] = 0x44, reg_wr(REG_ADR_PLL_CP_ADJ,          2);

		reg.wdata[1] = 0x2c, reg_wr(REG_ADR_PRIVATE_BPF_CAP1,  2);
		reg.wdata[1] = 0xc0, reg_wr(REG_ADR_PRIVATE_BPF_CAP2,  2);
		reg.wdata[1] = 0x17, reg_wr(REG_ADR_PRIVATE_BPF_ADJ1,  2);
		reg.wdata[1] = 0x17, reg_wr(REG_ADR_PRIVATE_BPF_ADJ2,  2);

		reg.wdata[1] = 0x44, reg.wdata[2] = 0x44, reg.wdata[3] = 0x08, reg.wdata[4] = 0x07;
		reg_wr(REG_ADR_VCO_CAL_MIN_FL, 5);
	}
	if((local_params.state == PHY_INIT) || (ch != local_params.ch)) {
		/* frequency setting */
		uint32_t freq_ch0, freq_min;
		uint32_t n4, a;
		uint32_t f;

		freq_ch0 = regset->freq[ch - 24];
		/* which assumes a value having lower 2MHz than CH0 frequency a calibration lower limit level
		 * (does not handle the floating point arithmetic with the CPU, and entrusts all a compiler)
		 */
		freq_min = freq_ch0 - FIXQ(2.0, 20, uint32_t);
		freq_ch0 /= 36;
		freq_min /= 36;
		if (INTQ(freq_min, 20) != INTQ(freq_ch0, 20)) { /* invalid as for the setting to step over the 36MHz border */
			return -EINVAL;
		}

		n4 = (uint32_t)((INTQ(freq_ch0 >> 2, 20) & 0x0f) << 2);  /* 4 times level of n */
		a = (uint32_t)((INTQ(freq_ch0, 20) - n4) & 0x03);
		f = (freq_ch0 - ((n4 + a) << 20)) & 0x0fffff;
		reg.wdata[1] = (uint8_t)(f >>  0 & 0xff), reg.wdata[2] = (uint8_t)(f >>  8 & 0xff), reg.wdata[3] = (uint8_t)(f >> 16 & 0x0f);
		reg.wdata[4] = (uint8_t)(n4 << 2 | a);
		reg_wr(REG_ADR_CH0_FL, 5);  /* A special command: I set a value of bp.param[BP_PARAM_CH0_FL] */
	}

	if((local_params.state == PHY_INIT) || (page != local_params.page)) {
		{
			uint16_t n;
			/* rate setting */
			reg.wdata[1] = regset->rate, reg_wr(REG_ADR_DATA_SET, 2);

			/* bandwidth setting */
			n = (uint16_t)(regset->chspc / 36);
			reg.wdata[1] = (uint8_t)(n >>  0 & 0xff), reg.wdata[2] = (uint8_t)(n >>  8 & 0xff);
			reg_wr(REG_ADR_CH_SPACE_L, 3);
			/* IF frequency setting */
			n = (uint16_t)(regset->iffreq / 36);
			reg.wdata[1] = (uint8_t)(n >>  8 & 0xff), reg.wdata[2] = (uint8_t)(n >>  0 & 0xff);
			reg_wr(REG_ADR_IF_FREQ_H, 3);
			reg_wr(REG_ADR_IF_FREQ_AFC_H, 3);
			n = (uint16_t)(regset->iffreq_cca / 36);
			reg.wdata[1] = (uint8_t)(n >>  8 & 0xff), reg.wdata[2] = (uint8_t)(n >>  0 & 0xff);
			reg_wr(REG_ADR_IF_FREQ_CCA_H, 3);
		}
		{  /* BPF setting */
			uint8_t bpf;
			uint16_t n;

			reg_rd(REG_ADR_BPF_ADJ_OFFSET, 1), bpf = reg.rdata[0];
			if (bpf & 0x80) {
				n = regset->ref + (uint16_t)INTQ((uint32_t)(bpf & 0x7f) * regset->coef, 14);
			} else {
				n = regset->ref - (uint16_t)INTQ((uint32_t)(bpf & 0x7f) * regset->coef, 14);
			}
			reg.wdata[1] = (uint8_t)(n >> 8 & 0xff), reg.wdata[2] = (uint8_t)(n >> 0 & 0xff);
			reg_wr(REG_ADR_BPF_ADJ_H,     3);
			reg_wr(REG_ADR_BPF_AFC_ADJ_H, 3);
			if (bpf & 0x80)
				n = regset->ref_cca + (uint16_t)INTQ((uint32_t)(bpf & 0x7f) * regset->coef_cca, 14);
			else
				n = regset->ref_cca - (uint16_t)INTQ((uint32_t)(bpf & 0x7f) * regset->coef_cca, 14);
			reg.wdata[1] = (uint8_t)(n >> 8 & 0xff), reg.wdata[2] = (uint8_t)(n >> 0 & 0xff);
			reg_wr(REG_ADR_BPF_CCA_ADJ_H, 3);

			/* GFSK Frequency shift setting */
			reg.wdata[1] = (uint8_t)(regset->fdev >> 0 & 0xff), reg.wdata[2] = (uint8_t)(regset->fdev >> 8 & 0xff);
			reg_wr(REG_ADR_F_DEV_L, 3);
			/* Hidden register setting */
			reg.wdata[1] = regset->reg1, reg_wr(2,0x0e, 2);
		}
	}

	/* own apparatus address acquisition */

	if((local_params.state == PHY_INIT) ||
			(page != local_params.page) ||
			(ch != local_params.ch)) {
		if(vco_cal() == false) {
			return -EDEADLK;
		};
	}
	local_params.ch = ch;
	local_params.txPower = txPower;
	local_params.page = page;
	local_params.state = PHY_SETUP;

	return STATUS_OK;
}

struct phy_param *phy_init(void)
{
	struct hw_mode hwif;
	hwif.i2c_addr = 0x50;

#if defined(LAZURITE_MINI)
	hwif.i2c_addr_bits = 16;
#else
	hwif.i2c_addr_bits = 8;
#endif
	if(HAL_init(&hwif) != STATUS_OK) return NULL;

	phy_reset();

	regbank(0xff);

	phy_intclr(~HW_EVENT_ALL_MASK);
	phy_inten(HW_EVENT_ALL_MASK);

	phy.in.size = BUFFER_SIZE;
	phy.in.data = reg.rfifo;
	phy.in.len = 0;
	phy.out.size = BUFFER_SIZE-3;						// REG_ADR(1) & CRC(2)
	phy.out.len = 0;
	phy.out.data = reg.wfifo+1;							// REG_ADR(1)
	phy.unit_backoff_period = UNIT_BACKOFF_PERIOD;

	reg.wdata[1] = 0xD3,reg_wr(REG_ADR_ADC_CLK_SET,2);
	reg.wdata[1] = 0x2F,reg_wr(REG_ADR_CLK_SET,2);

	local_params.state = PHY_INIT;

	return &phy;
}


/******************************************************************************/
/*! @brief Writing in data to FIFO
 * Delay 300usec is intended to prevent FIFO access during TX_ON transition.
 * It may become the PLL unlocking when FIFO accesses it.
 ******************************************************************************/
int phy_txpre(TX_MODE mode)
{
	uint16_t length = phy.out.len+2;

	phy_intclr(~HW_EVENT_ALL_MASK);
	switch(mode) {
		case MANUAL_TX:
			reg.wdata[1] = 0x3a;
			reg_wr(REG_ADR_PACKET_MODE_SET, 2);
			break;
		case AUTO_TX:				// AUTO_TX
			reg.wdata[1] = 0x3e;
			reg_wr(REG_ADR_PACKET_MODE_SET, 2);
			phy_inten(HW_EVENT_TX_DONE);
			break;
		default:
			return -EINVAL;
	}

	// make fcf
	reg.wdata[1] = (uint8_t)(0x18+((length >> 8) & 0x07));	// PHR
	reg.wdata[2] = (uint8_t)(length & 0xff);							// length : crc size + payload length
	reg_wr(REG_ADR_WR_TX_FIFO, 3);

	// make payload
	fifo_wr(REG_ADR_WR_TX_FIFO);

	return STATUS_OK;
}

int phy_ccaCtrl(uint32_t us) {
	long d;
	// data invalid setting during CCA
	reg.wdata[1] = 0x00;
	reg_wr(REG_ADR_DEMSET3, 2);
	reg_wr(REG_ADR_DEMSET14,2);
	phy_inten((uint32_t)HW_EVENT_CCA_DONE);

	d = map((long)us,1600L,4000L,92L,242L);

	reg.wdata[1] = (uint8_t)((d>>8)&0x03);
	reg_wr(REG_ADR_IDLE_WAIT_H, 2);
	reg.wdata[1] = (uint8_t)(d&0x000000FF);
	reg_wr(REG_ADR_IDLE_WAIT_L, 2);
	reg.wdata[1] = 0x18;
	reg_wr(REG_ADR_CCA_CNTRL,   2);
	phy_trx_state(PHY_ST_RXON);
	return STATUS_OK;
}

uint8_t phy_ccadone(void) {
	uint8_t ccadone;
	union {
		uint8_t d8[4];
		uint32_t d32;
	} intsrc;
	reg_rd(REG_ADR_INT_SOURCE_GRP1, 4);
	memcpy(&intsrc,reg.rdata,4);
	reg_rd(REG_ADR_CCA_CNTRL, 1);
	ccadone = reg.rdata[0];
	if(ccadone & 0x10) {
		reg.wdata[1] = 0;
		reg_wr(REG_ADR_CCA_CNTRL, 2);
		phy_trx_state(PHY_ST_FORCE_TRXOFF);
	}
	phy_intclr(~(HW_EVENT_FIFO_CLEAR|HW_EVENT_TX_FIFO_DONE));
	phy_inten(HW_EVENT_ALL_MASK);
	reg.wdata[1] = 0x64;
	reg_wr(REG_ADR_DEMSET3, 2);
	reg.wdata[1] = 0x27;
	reg_wr(REG_ADR_DEMSET14, 2);
	return ccadone;
}

int phy_txstart(void) {

	phy_inten((uint32_t)HW_EVENT_TX_DONE);
	phy_trx_state(PHY_ST_TXON);
	return STATUS_OK;
}

FIFO_STATE phy_txfifo(void) {
	return FIFO_DONE;
}

void phy_txdone(void)
{
	int cycle = 0;
	uint32_t intsrc;
	static const char s1[] = "auto txdone error1";
	static const char s2[] = "auto txdone error2";

	reg_rd(REG_ADR_INT_SOURCE_GRP1, 4);
	memcpy(&intsrc,reg.rdata,4);
	do {
		cycle++;
		reg_rd(REG_ADR_RF_STATUS,1);
		if((reg.rdata[0] & 0x0F) != 0x08) {
			alert(s1);
			phy_trx_state(PHY_ST_FORCE_TRXOFF);
			break;
		} else if(cycle > 10000) {
			alert(s2);
			phy_trx_state(PHY_ST_FORCE_TRXOFF);
			break;
		}
	} while((reg.rdata[0] & 0xF0) != 0x80);

	phy_intclr(~HW_EVENT_FIFO_CLEAR);
}

void phy_rxstart(void)
{
	reg.wdata[1] = 0x64;
	reg_wr(REG_ADR_DEMSET3,  2);
	reg.wdata[1] = 0x27;
	reg_wr(REG_ADR_DEMSET14, 2);
	phy_intclr(~HW_EVENT_ALL_MASK);
	phy_inten(HW_EVENT_RX_DONE | HW_EVENT_ADD_FIL_DONE);
	phy_trx_state(PHY_ST_RXON);
}

FIFO_STATE phy_rxdone()
{
	FIFO_STATE status=FIFO_DONE;
	uint16_t data_size=0;
	union{
		uint8_t d8[4];
		uint32_t d32;
	} intsrc;

	phy_trx_state(PHY_ST_FORCE_TRXOFF);

	// Notice: A following must not change.
	reg_rd(REG_ADR_INT_SOURCE_GRP1, 4);
	memcpy(&intsrc.d32,reg.rdata,4);

	if(intsrc.d8[2] != 0x04) {
		status = CRC_ERROR;
		goto error;
	}
	reg_rd(REG_ADR_RD_RX_FIFO, 2);
	data_size = reg.rdata[0] & 0x07;
	data_size = (data_size << 8) + reg.rdata[1];
	if(data_size<=phy.in.size) {
		phy.in.len = data_size + 1; // add ED vale
		fifo_rd(REG_ADR_RD_RX_FIFO);
		phy.in.data[phy.in.len-3] = phy.in.data[phy.in.len-1];		// erase crc and move ed
		phy.in.len -= 2;
	} else {
		status = CRC_ERROR;
		goto error;
	}
error:
	phy_intclr(HW_EVENT_RX_DONE | HW_EVENT_CRC_ERROR | HW_EVENT_RF_STATUS | HW_EVENT_ADD_FIL_DONE);
	reg.wdata[1] = 0x88, reg_wr(REG_ADR_RST_SET, 2);		// PHY RESET
	return status;
}

void phy_stop(void) {
	phy_trx_state(PHY_ST_FORCE_TRXOFF);
	phy_intclr(~HW_EVENT_ALL_MASK);
	phy_inten(HW_EVENT_ALL_MASK);
}

void phy_clrAddrFilt(void)
{
	reg.wdata[1] = 0x00;
	reg_wr(REG_ADR_ADDFIL_CNTRL, 2);
}

void phy_addrFilt(uint16_t panid, uint8_t *ieee_addr, uint16_t uc_addr, uint16_t bc_addr)
{
	reg.wdata[1] = 0x1E;
	reg_wr(REG_ADR_ADDFIL_CNTRL, 2);

	reg.wdata[1] = (uint8_t)(panid & 0xff);
	reg.wdata[2] = (uint8_t)((panid >> 8) & 0xff);
	reg_wr(REG_ADR_PANID_L, 3);

	memcpy(&reg.wdata[1],ieee_addr,4);
	reg_wr(REG_ADR_64ADDR1, 5);
	memcpy(&reg.wdata[1],ieee_addr+4,4);
	reg_wr(REG_ADR_64ADDR5, 5);


	reg.wdata[1] = (uint8_t)(uc_addr & 0xff);
	reg.wdata[2] = (uint8_t)((uc_addr >> 8) & 0xff);
	reg_wr(REG_ADR_SHT_ADDR0_L, 3);

	reg.wdata[1] = (uint8_t)(bc_addr & 0xff);
	reg.wdata[2] = (uint8_t)((bc_addr >> 8) & 0xff);
	reg_wr(REG_ADR_SHT_ADDR1_L, 3);
}

void phy_sleep(void)
{
	if(local_params.state == PHY_SETUP) {
		phy_trx_state(PHY_ST_FORCE_TRXOFF);
		reg.wdata[1] = 0x2F, reg_wr(REG_ADR_CLK_SET, 2);
		reg.wdata[1] = 0x00, reg_wr(REG_ADR_2DIV_CNTRL, 2);
		local_params.state = PHY_SLEEP;
	}
}

int phy_setModulation(int8_t mode,int8_t sf) {
	return STATUS_OK;
}

int phy_getModulation(int8_t *mode,int8_t *sf) {
	*mode = -1;
	*sf = -1;
	return -EINVAL;
}

int phy_ed(int mode,uint8_t **data,int *size) {
	uint32_t *avr_p;
	uint8_t ch;
	int cycle;
	const uint8_t ch_num[2]={38,37};
	phy.in.len = 0;
	phy.out.len = 0;
	switch(mode) {
		case 1:
			avr_p = (uint32_t *) phy.in.data;
			memset(phy.out.data,0,1);
			memset(avr_p,0,sizeof(uint32_t));

			reg.wdata[1] = 0x00;
			reg_wr(REG_ADR_DEMSET3, 2);
			reg_wr(REG_ADR_DEMSET14,2);
			phy_inten(HW_EVENT_ALL_MASK);
			phy_trx_state(PHY_ST_RXON);

			HAL_delayMicroseconds(128);

			for(cycle = 0; cycle < 128; cycle ++) {
				HAL_delayMicroseconds(128);
				reg_rd(REG_ADR_ED_RSLT,1);
				if(phy.out.data[0]  < reg.rdata[0]) phy.out.data[0] = reg.rdata[0];
				avr_p[0] += reg.rdata[0];
			}
			avr_p[0] = avr_p[0]/128;
			phy.out.data[1] = (uint8_t)avr_p[0];
			phy.out.len = 2;

			reg.wdata[1] = 0x64;
			reg_wr(REG_ADR_DEMSET3, 2);
			reg.wdata[1] = 0x27;
			reg_wr(REG_ADR_DEMSET14, 2);
			phy_trx_state(PHY_ST_TRXOFF);
			phy_intclr(~HW_EVENT_ALL_MASK);
			break;
		case 2:
		case 3:
			avr_p = (uint32_t *) phy.in.data;
			memset(phy.out.data,0,ch_num[mode-2]);
			memset(avr_p,0,sizeof(uint32_t)*ch_num[mode-2]);

			reg.wdata[1] = 0x00;
			reg_wr(REG_ADR_DEMSET3, 2);
			reg_wr(REG_ADR_DEMSET14,2);
			phy_inten(HW_EVENT_ALL_MASK);
			phy_trx_state(PHY_ST_TRXOFF);

			for(cycle = 0; cycle < 16; cycle ++) {
				for(ch=0;ch<ch_num[mode-2];ch++) {
					if(phy_setup(mode-1,24+ch, 20,0) != STATUS_OK) {
						continue;
					}
					phy_trx_state(PHY_ST_RXON);
					HAL_delayMicroseconds(256);
					reg_rd(REG_ADR_ED_RSLT,1);
					if(phy.out.data[ch]  < reg.rdata[0]) phy.out.data[ch] = reg.rdata[0];
					avr_p[ch] += reg.rdata[0];
					phy_trx_state(PHY_ST_TRXOFF);
				}
			}
			for(ch=0;ch<ch_num[mode-2];ch++) {
				phy.out.data[ch_num[mode-2]+ch] = avr_p[ch]/16;
			}
			phy.out.len = ch_num[mode-2]*2;
			reg.wdata[1] = 0x64;
			reg_wr(REG_ADR_DEMSET3, 2);
			reg.wdata[1] = 0x27;
			reg_wr(REG_ADR_DEMSET14, 2);
			phy_intclr(~HW_EVENT_ALL_MASK);
			break;
		default:
			return -EINVAL;
			break;
	}
	*data = phy.out.data;
	*size = phy.out.len;
	return STATUS_OK;
}
// TEST CODE
#ifndef LAZURITE_IDE
extern volatile int que_irq;
extern struct thread_param m;
#endif


void phy_monitor(void){
#ifdef LAZURITE_IDE
	static const char s1[] = "PHY_MONITOR";
	static const char s2[] = "INT SOURCE:: ";
	static const char s3[] = ",";
	static const char s4[] = "INT ENABLE:: ";
	static const char s5[] = "RF STATUS:: ";
	static const char s6[] = "RF CCA CNTL:: ";
	static const char s7[] = "PACKET MODE SET:: ";
	static const char s8[] = "PD DATA REQ:: ";
	static const char s9[] = "PD DATA IND:: ";
	static const char s10[] = "AUTO ACK SET: ";
#endif
	// READ INT SOURCE
	reg_rd(REG_ADR_INT_SOURCE_GRP1, 4);
#ifndef LAZURITE_IDE
	printk(KERN_INFO"QUE :: %d %d\n",que_irq,m.trigger);
	printk(KERN_INFO"INT SOURCE:: %x,%x,%x,%x\n", reg.rdata[0],reg.rdata[1],reg.rdata[2],reg.rdata[3]);
#else
	delay(10);
	Serial.println(s1);
	Serial.print(s2);
	Serial.print_long((long)reg.rdata[0],HEX);
	Serial.print(s3);
	Serial.print_long((long)reg.rdata[1],HEX);
	Serial.print(s3);
	Serial.print_long((long)reg.rdata[2],HEX);
	Serial.print(s3);
	Serial.println_long((long)reg.rdata[3],HEX);
#endif

	// READ INT ENABLE
	reg_rd(REG_ADR_INT_EN_GRP1, 4);
#ifndef LAZURITE_IDE
	printk(KERN_INFO"INT ENABLE:: %x,%x,%x,%x\n", reg.rdata[0],reg.rdata[1],reg.rdata[2],reg.rdata[3]);
#else
	Serial.print(s4);
	Serial.print_long((long)reg.rdata[0],HEX);
	Serial.print(s3);
	Serial.print_long((long)reg.rdata[1],HEX);
	Serial.print(s3);
	Serial.print_long((long)reg.rdata[2],HEX);
	Serial.print(s3);
	Serial.println_long((long)reg.rdata[3],HEX);
#endif

	// READ RF STATE
	reg_rd(REG_ADR_RF_STATUS, 1);
#ifndef LAZURITE_IDE
	printk(KERN_INFO"RF STATUS:: %x\n", reg.rdata[0]);
#else
	Serial.print(s5);
	Serial.println_long((long)reg.rdata[0],HEX);
#endif
	reg_rd(REG_ADR_CCA_CNTRL, 1);
#ifndef LAZURITE_IDE
	printk(KERN_INFO"RF CCA CNTL:: %x\n", reg.rdata[0]);
#else
	Serial.print(s6);
	Serial.println_long((long)reg.rdata[0],HEX);
#endif
	reg_rd(REG_ADR_PACKET_MODE_SET, 1);
#ifndef LAZURITE_IDE
	printk(KERN_INFO"PACKET MODE SET:: %x\n", reg.rdata[0]);
#else
	Serial.print(s7);
	Serial.println_long((long)reg.rdata[0],HEX);
#endif
	reg_rd(REG_ADR_PD_DATA_REQ, 1);
#ifndef LAZURITE_IDE
	printk(KERN_INFO"PD DATA REQ:: %x\n", reg.rdata[0]);
#else
	Serial.print(s8);
	Serial.println_long((long)reg.rdata[0],HEX);
#endif
	reg_rd(REG_ADR_PD_DATA_IND, 1);
#ifndef LAZURITE_IDE
	printk(KERN_INFO"PD DATA IND:: %x\n", reg.rdata[0]);
#else
	Serial.print(s9);
	Serial.println_long((long)reg.rdata[0],HEX);
#endif
	reg_rd(REG_ADR_AUTO_ACK_SET, 1);
#ifndef LAZURITE_IDE
	printk(KERN_INFO"AUTO ACK SET: %x\n", reg.rdata[0]);
#else
	Serial.print(s10);
	Serial.println_long((long)reg.rdata[0],HEX);
	__asm("brk");
#endif
}

// following function is for debug. and test.bin use it.

int phy_regread(uint8_t bank, uint8_t addr, uint8_t *data, uint8_t size) {
	int status = -ENOMEM;
	if(size<=sizeof(reg.rdata)) {
		reg_rd(bank,addr,size);
		memcpy(data,reg.rdata,size);
		status = STATUS_OK;
	}
	return status;
}


int phy_regwrite(uint8_t bank, uint8_t addr, uint8_t *data, uint8_t size) {
	int status = -ENOMEM;
	if(size<=sizeof(reg.wdata)-1) {
		memcpy(reg.wdata+1,data,size);
		reg_wr(bank, addr, (uint8_t)(size+1));
		status = STATUS_OK;
	}
	return status;
}

void phy_regdump(void) {
	uint8_t bank,dump_cnt;
#ifdef LAZURITE_IDE
	uint8_t i;
	static const char s1[] = "-----------------/ bank";
	static const char s2[] = " /---------------";
	static const char s3[] = " ";
	static const char s4[] = "0";
	static const char s5[] = "";
#endif

	for(bank = 8; bank<=10; bank++) {
#ifdef LAZURITE_IDE
		Serial.print(s1);
		Serial.print_long((long)(bank-8),DEC);
		Serial.println(s2);
#else
		printk(KERN_INFO"-----------------/ bank%d /---------------",bank-8);
#endif
		for(dump_cnt=0; dump_cnt <= 0x7F; dump_cnt+=8) {
			reg_rd(bank, dump_cnt, 8);
#ifdef LAZURITE_IDE
			for(i=0;i<8;i++) {
				Serial.print(s3);
				if(reg.rdata[i] < 16) {
					Serial.print(s4);
				}
				Serial.print_long((long)reg.rdata[i],HEX);
			}
			Serial.println(s5);
#else
			printk(KERN_INFO"%02X %02X %02X %02X %02X %02X %02X %02X\n",
					reg.rdata[0],
					reg.rdata[1],
					reg.rdata[2],
					reg.rdata[3],
					reg.rdata[4],
					reg.rdata[5],
					reg.rdata[6],
					reg.rdata[7]);
#endif
		}
	}
}

