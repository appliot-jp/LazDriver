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


#ifdef LAZURITE_IDE
#include <stddef.h>
#include <stdint.h>
#include "hwif/core/ml7396_hwif.h"
#include "hwif/core/ml7396_reg.h"
#else
#include <linux/stddef.h>
#endif

#include "hwif/hal.h"
#include "hwif/hal-lzpi.h"
#include "errno.h"
#include "endian.h"
#include "common_lazurite.h"
#include "common-lzpi.h"
#include "phy_lazurite.h"
#include "phy_ml7396.h"


/*
 ******************************************************
                    Define section
 ******************************************************
 */
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

/*
 ******************************************************
                    Struct section
 ******************************************************
 */
static struct {
    volatile uint8_t lock;  // exclusion lock counter  
    uint8_t bank;           // back number
    uint8_t rdata[256];     // input buffer 
    uint8_t wdata[256];     // outpu buffer
}reg = {
    0,    /* lock */
    0xff  /* bank */
};

static volatile struct {
    struct {                      /* Timer-related parameter */
        void (*handler)(void);    /* Interrupt handler of the timer */
#ifdef ML7396_HWIF_NOTHAVE_TIMER_DI
        enum {
            Disable=0,
            Enable
        } active;
        uint8_t call_count;       /* The handler summons number of times that interrupts it, and is prohibiting it */
#endif  /* #ifdef ML7396_HWIF_NOTHAVE_TIMER_DI */
    } timer;
} hwif = {
    {
        NULL  /* timer.handler */
#ifdef ML7396_HWIF_NOTHAVE_TIMER_DI
      , Disable,  /* timer.acvive */
        0         /* timer.call_count */
#endif  /* #ifdef ML7396_HWIF_NOTHAVE_TIMER_DI */
    }
};

#ifdef ML7396_HWIF_NOTHAVE_TIMER_DI
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
#endif  /* #ifdef ML7396_HWIF_NOTHAVE_TIMER_DI */


/*
Register setting argument
*/
typedef struct {
    uint8_t channel;
    uint8_t rate;
    uint8_t txPower;
    uint8_t device_id;
    uint16_t address;
} Setup;


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



static PHY_PARAM phy;


/*
 ******************************************************
               Private function section
 ******************************************************
 */
/******************************************************************************/
/*! @brief Register access of the ML7396 module
   The reading and writing of the SPI bus
   wdata[]: Data sequence to write in
   size: The number of the data to read and write
   rdata[]: Sequence to store the data which I began to read in
 ******************************************************************************/
static void ml7396_hwif_spi_transfer(const uint8_t *wdata, uint8_t *rdata, uint8_t size) {

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
static void regbank(uint8_t bank) {
    if (bank&0x0b){
        if (bank != reg.bank) {
            reg.wdata[0] = (0x00<<1)|0x01, reg.wdata[1] = bank&0x03;
            if(bank > 2) reg.wdata[1] = reg.wdata[1] | 0x80;
            ml7396_hwif_spi_transfer(reg.wdata, reg.rdata, 2);
            reg.bank = bank;
        }
    }else{
        reg.lock = 0;
        reg.bank = bank;
    }
}

/******************************************************************************/
/*! @brief write register
 * bank: bank number
 * addr: write address
 * data: write data
 * size: data size
 ******************************************************************************/
static void ml7396_regwrite(uint8_t bank, uint8_t addr, const uint8_t *data, uint8_t size)
{
//	__DI();
    if (reg.lock++) {
        --reg.lock;
    }else{
        regbank(bank);
        reg.wdata[0] = (addr << 1) | 0x01;
        memcpy(reg.wdata + 1, data, size);
        ml7396_hwif_spi_transfer(reg.wdata, reg.rdata, size + 1);
    }
//	__EI();
}

/******************************************************************************/
/*! @brief read register
 * bank: bank number
 * addr: read address
 * data: store readind data
 * size: data size
 ******************************************************************************/
static void ml7396_regread(uint8_t bank, uint8_t addr, uint8_t *data, uint8_t size) {
//	__DI();
    if (reg.lock++) {
        --reg.lock;
    }else{
    regbank(bank);
    reg.rdata[0] = (addr << 1) | 0x00;
    memset(reg.rdata + 1, 0xff, size);
    ml7396_hwif_spi_transfer(reg.rdata, reg.rdata, size + 1);
    memcpy(data, reg.rdata, size);
    }
//	__EI();
}

#if 0
/******************************************************************************/
/*! @brief Sint event handler
 * @detail 
 ******************************************************************************/
static void sint_handler(void) {
	uint32_t hw_event, hw_done;
	ml7396_hwif_timer_di();
	// REG_INTSRC(hw_event);
	printk(KERN_INFO"%s %s %d %08x\n",__FILE__,__func__,__LINE__,hw_event);
	hw_done = 0;
//	em_data.store_hw_event = 0;
#ifdef LAZURITE_IDE 
	if((em_data.state == ML7396_StateSending) &&
			hw_event&(HW_EVENT_CCA_DONE|
				HW_EVENT_FIFO_EMPTY|HW_EVENT_TX_DONE)) {

		em_data.store_hw_event = hw_event;
		if(hw_event & HW_EVENT_CCA_DONE){
			ml7396_regread(REG_ADR_CCA_CNTRL, &em_data.cca_rslt, 1);
			em_data.cca_rslt &= 0x03;
		}
		hw_event &= ~HW_EVENT_TX_FIFO_DONE;
		REG_INTCLR(hw_event);
	}else
#endif
	{
		//em_main(&em_data, NULL, 0, hw_event, &hw_done);
		//REG_INTCLR(hw_done);
	}
	ml7396_hwif_timer_ei();
}

/******************************************************************************/
/*! @brief Sint event handler
 * @detail 
 ******************************************************************************/
static void timer_handler(void) {
	uint32_t hw_event, hw_done;
	ml7396_hwif_sint_di();
	hw_event = ETIMEDOUT, hw_done = 0;
	// em_main(&em_data, NULL, 0, hw_event, &hw_done);
	ml7396_hwif_sint_ei();
}
#endif



/*
 ******************************************************
               Public function section
 ******************************************************
 */
/******************************************************************************/
/*! @brief Hardware interface function
    Neighboring device initialization of the L7396 module
    Preparations for SPI bus data communication
    Preparations for SINTN interrupt control
    Clear and start of the elapsed time timer
    Preparations for time-out interrupt control
    Hardware reset with the RESET termin
   @return  more than 0=STATUS_OK, less than 0= error num
 ******************************************************************************/
int ml7396_hwif_init(void) {
    int status = -1;
    uint32_t wait_t;

    hwif.timer.handler = NULL;
#ifdef ML7396_HWIF_NOTHAVE_TIMER_DI
    hwif.timer.active = Disable;
    hwif.timer.call_count = 0;
#endif  /* #ifdef ML7396_HWIF_NOTHAVE_TIMER_DI */
    status = HAL_init(0x50,8);
	if(status != 0) return status;
//  HAL_SPI_setup();
//  HAL_GPIO_setup();
    HAL_TIMER_setup();
//  HAL_I2C_setup();
    ml7396_hwif_timer_tick(&wait_t);
    status = 0;
    return status;
}

/******************************************************************************/
/*! @brief Interrupt handler registration of the ML7396 module
 * @detail Handler of the interrupt that SINTN terminal generates at 'L' level
 ******************************************************************************/
int ml7396_hwif_sint_handler(void (*func)(void)) {
    int status = -1;

    HAL_GPIO_setInterrupt(func);
    status = 0;
    return status;
}

/******************************************************************************/
/*! @brief Enable interrupt
 * @detail Interrupt permission delay cancellation of the ML7396 module
 ******************************************************************************/
int ml7396_hwif_sint_ei(void) {
    int status = -1;

    HAL_GPIO_enableInterrupt();
    status = 0;
    return status;
}

/******************************************************************************/
/*! @brief Disable interrupt
 * @detail The delay that interrupt of the ML7396 module is prohibited in it.
 *         I delay whether it is admitted again until I am cleared.
 ******************************************************************************/
int ml7396_hwif_sint_di(void) {
    int status = -1;

    HAL_GPIO_disableInterrupt();
    status = 0;
    return status;
}

/******************************************************************************/
/*! @brief Time-out interrupt handler registration
 * @detail func: Interrupt handler function
 ******************************************************************************/
int ml7396_hwif_timer_handler(void (*func)(void)) {
    int status = -1;

    hwif.timer.handler = func;
    status = 0;
    return status;
}

/******************************************************************************/
/*! @brief Enable time-out interrupt
 * @detail func: The delay that time-out interrupt is prohibited in it.
           I delay whether it is admitted again until I am cleared.
 ******************************************************************************/
int ml7396_hwif_timer_ei(void) {
    int status = -1;

#ifdef ML7396_HWIF_NOTHAVE_TIMER_DI
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
#else  /* #ifdef ML7396_HWIF_NOTHAVE_TIMER_DI */
    HAL_TIMER_enableInterrupt();
#endif  /* #ifdef ML7396_HWIF_NOTHAVE_TIMER_DI */
    status = 0;
    return status;
}

/******************************************************************************/
/*! @brief Disable time-out interrupt
 * @detail The delay that time-out interrupt is prohibited in it.
 I delay whether it is admitted again until I am cleared.
 ******************************************************************************/
int ml7396_hwif_timer_di(void) {
    int status = -1;

#ifdef ML7396_HWIF_NOTHAVE_TIMER_DI
    switch (hwif.timer.active) {
    case Disable:
        break;
    case Enable:
        hwif.timer.active = Disable;
        break;
    }
#else  /** #ifdef ML7396_HWIF_NOTHAVE_TIMER_DI */
    HAL_TIMER_disableInterrupt();
#endif  /* #ifdef ML7396_HWIF_NOTHAVE_TIMER_DI */
    status = 0;
    return status;
}

/******************************************************************************/
/*! @brief time-out interrupt count start
 * @detail I produce an interrupt after progress at designation time
 * msec: Time before producing a time-out interrupt (appoint it by a msec unit)
 ******************************************************************************/
int ml7396_hwif_timer_start(uint16_t msec) {
    int status = -1;

#ifdef ML7396_HWIF_NOTHAVE_TIMER_DI
    HAL_TIMER_start(msec, timer_handler);
#else  /* #ifdef ML7396_HWIF_NOTHAVE_TIMER_DI */
    HAL_TIMER_start(msec, hwif.timer.handler);
#endif  /* #ifdef ML7396_HWIF_NOTHAVE_TIMER_DI */
    status = 0;
    return status;
}

/******************************************************************************/
/*! @brief time-out interrupt count start
 * @detail I produce an interrupt after progress at designation time
 * msec: Time before producing a time-out interrupt (appoint it by a msec unit)
 ******************************************************************************/
int ml7396_hwif_timer_stop(void) {
    int status = -1;

    HAL_TIMER_stop();
    status = 0;
    return status;
}

/******************************************************************************/
/*! @brief Timer tick
 * @detail The acquisition of the elapsed time timer.
           I acquire an elapsed time from neighboring device initialization.
           msec: The elapsed time when acquired it (msec unit).
 ******************************************************************************/
int ml7396_hwif_timer_tick(uint32_t *msec) {
    int status = -1;

    HAL_TIMER_getTick(msec);
    status = 0;
    return status;
}



/******************************************************************************/
/*! @brief Register setting of ML7396
 * @detail 
       Channel setting
       Bandwidth setting
       Communication rate setting
       Transmission output setting
       Setting peculiar to other devices
       awaiting first clock stability and the last calibration practice are unnecessary
 ******************************************************************************/
int ml7396_hwif_regset(void *data) {
    int status = -1;
    Setup *setup = (Setup *)data;
    const REGSET *regset;
    uint8_t reg_data[4];

    HAL_I2C_read(0x23, reg_data, 1), setup->device_id = reg_data[0];
    reg_data[0] = 0x0f, ml7396_regwrite(REG_ADR_CLK_SET,             reg_data, 1);
    reg_data[0] = 0x22, ml7396_regwrite(REG_ADR_RX_PR_LEN_SFD_LEN,   reg_data, 1);
    reg_data[0] = 0x00, ml7396_regwrite(REG_ADR_SYNC_CONDITION,      reg_data, 1);
#ifdef LAZURITE_MINI
    reg_data[0] = 0x02, ml7396_regwrite(REG_ADR_2DIV_CNTRL,          reg_data, 1);
#else
    if (setup->device_id == DEIVE_ID_LAPIS)
        reg_data[0] = 0x0A, ml7396_regwrite(REG_ADR_2DIV_CNTRL,          reg_data, 1);
    else
        reg_data[0] = 0x04, ml7396_regwrite(REG_ADR_2DIV_CNTRL,          reg_data, 1);
#endif
    reg_data[0] = 0x04, ml7396_regwrite(REG_ADR_SYNC_MODE,           reg_data, 1);
    reg_data[0] = 0x10, ml7396_regwrite(REG_ADR_RAMP_CNTRL,          reg_data, 1);
    reg_data[0] = 0x1e, ml7396_regwrite(REG_ADR_GAIN_MtoL,           reg_data, 1);
    reg_data[0] = 0x02, ml7396_regwrite(REG_ADR_GAIN_LtoM,           reg_data, 1);
    reg_data[0] = 0x9e, ml7396_regwrite(REG_ADR_GAIN_HtoM,           reg_data, 1);
    reg_data[0] = 0x02, ml7396_regwrite(REG_ADR_GAIN_MtoH,           reg_data, 1);
    reg_data[0] = 0x15, ml7396_regwrite(REG_ADR_RSSI_ADJ_M,          reg_data, 1);
    reg_data[0] = 0x2b, ml7396_regwrite(REG_ADR_RSSI_ADJ_L,          reg_data, 1);
    reg_data[0] = 0x22, ml7396_regwrite(REG_ADR_RSSI_STABLE_TIME,    reg_data, 1);
    reg_data[0] = 0xd4, ml7396_regwrite(REG_ADR_RSSI_VAL_ADJ,        reg_data, 1);
    reg_data[0] = 0x01, ml7396_regwrite(REG_ADR_AFC_CNTRL,           reg_data, 1);
    reg_data[0] = 0xaa, ml7396_regwrite(REG_ADR_PREAMBLE_SET,        reg_data, 1);
    reg_data[0] = 0x09, ml7396_regwrite(REG_ADR_SFD1_SET1,           reg_data, 1);
    reg_data[0] = 0x72, ml7396_regwrite(REG_ADR_SFD1_SET2,           reg_data, 1);
    reg_data[0] = 0xf6, ml7396_regwrite(REG_ADR_SFD1_SET3,           reg_data, 1);
    reg_data[0] = 0x72, ml7396_regwrite(REG_ADR_SFD1_SET4,           reg_data, 1);
    reg_data[0] = 0x5e, ml7396_regwrite(REG_ADR_SFD2_SET1,           reg_data, 1);
    reg_data[0] = 0x70, ml7396_regwrite(REG_ADR_SFD2_SET2,           reg_data, 1);
    reg_data[0] = 0xc6, ml7396_regwrite(REG_ADR_SFD2_SET3,           reg_data, 1);
    reg_data[0] = 0xb4, ml7396_regwrite(REG_ADR_SFD2_SET4,           reg_data, 1);
    reg_data[0] = 0xb6, ml7396_regwrite(REG_ADR_2DIV_GAIN_CNTRL,     reg_data, 1);
    reg_data[0] = 0x84, ml7396_regwrite(1,0x39,                      reg_data, 1);  /* Hidden register */
    reg_data[0] = 0x8f, ml7396_regwrite(REG_ADR_PLL_CTRL,            reg_data, 1);
    reg_data[0] = 0x32, ml7396_regwrite(REG_ADR_RX_ON_ADJ2,          reg_data, 1);
    reg_data[0] = 0x0f, ml7396_regwrite(REG_ADR_LNA_GAIN_ADJ_M,      reg_data, 1);
    reg_data[0] = 0x01, ml7396_regwrite(REG_ADR_LNA_GAIN_ADJ_L,      reg_data, 1);
    reg_data[0] = 0xff, ml7396_regwrite(REG_ADR_MIX_GAIN_ADJ_M,      reg_data, 1);
    reg_data[0] = 0xff, ml7396_regwrite(REG_ADR_MIX_GAIN_ADJ_L,      reg_data, 1);
    reg_data[0] = 0xb4, ml7396_regwrite(REG_ADR_TX_OFF_ADJ1,         reg_data, 1);
    reg_data[0] = 0x01, ml7396_regwrite(REG_ADR_RSSI_SLOPE_ADJ,      reg_data, 1);
    reg_data[0] = 0x04, ml7396_regwrite(REG_ADR_PA_ON_ADJ,           reg_data, 1);
    reg_data[0] = 0x0a, ml7396_regwrite(REG_ADR_RX_ON_ADJ,           reg_data, 1);
    reg_data[0] = 0x00, ml7396_regwrite(REG_ADR_RXD_ADJ,             reg_data, 1);
    reg_data[0] = 0x2c, ml7396_regwrite(2,0x2d,                      reg_data, 1);  /* Hidden register */
    reg_data[0] = 0xc0, ml7396_regwrite(2,0x2e,                      reg_data, 1);  /* Hidden register */
    reg_data[0] = 0x17, ml7396_regwrite(2,0x2f,                      reg_data, 1);  /* Hidden register */
    reg_data[0] = 0x17, ml7396_regwrite(2,0x30,                      reg_data, 1);  /* Hidden register */
    HAL_I2C_read(0x2b, reg_data, 1), ml7396_regwrite(REG_ADR_PA_ADJ1, reg_data, 1);  /*  1mW rough adjustment */
    HAL_I2C_read(0x29, reg_data, 1), ml7396_regwrite(REG_ADR_PA_ADJ3, reg_data, 1);  /* 20mW rough adjustment */
    switch (setup->txPower) {
    case  1:  /*  1mW */
        HAL_I2C_read(0x2c, reg_data, 1), ml7396_regwrite(REG_ADR_PA_REG_FINE_ADJ, reg_data, 1);
        reg_data[0] = 0x01, ml7396_regwrite(REG_ADR_PA_CNTRL,                    reg_data, 1);
        break;
    case 20:  /* 20mW */
        HAL_I2C_read(0x2a, reg_data, 1), ml7396_regwrite(REG_ADR_PA_REG_FINE_ADJ, reg_data, 1);
        reg_data[0] = 0x13, ml7396_regwrite(REG_ADR_PA_CNTRL,                    reg_data, 1);
        break;
    default:
        goto error;
    }
    reg_data[0] = 0x0f, ml7396_regwrite(REG_ADR_SW_OUT_RAMP_ADJ,     reg_data, 1);
    reg_data[0] = 0x08, ml7396_regwrite(REG_ADR_IQ_MAG_ADJ,          reg_data, 1);
    reg_data[0] = 0x20, ml7396_regwrite(REG_ADR_IQ_PHASE_ADJ,        reg_data, 1);
#ifdef LAZURITE_MINI
    reg_data[0] = 0x07, ml7396_regwrite(REG_ADR_PA_REG_ADJ1,         reg_data, 1);
    reg_data[0] = 0x07, ml7396_regwrite(REG_ADR_PA_REG_ADJ2,         reg_data, 1);
    reg_data[0] = 0x07, ml7396_regwrite(REG_ADR_PA_REG_ADJ3,         reg_data, 1);
    reg_data[0] = 0x30, ml7396_regwrite(REG_ADR_CCA_LEVEL,           reg_data, 1);
#else
    reg_data[0] = 0x06, ml7396_regwrite(REG_ADR_PA_REG_ADJ1,         reg_data, 1);
    reg_data[0] = 0x01, ml7396_regwrite(REG_ADR_PA_REG_ADJ2,         reg_data, 1);
    reg_data[0] = 0x01, ml7396_regwrite(REG_ADR_PA_REG_ADJ3,         reg_data, 1);
    reg_data[0] = 0x55, ml7396_regwrite(REG_ADR_CCA_LEVEL,           reg_data, 1);
#endif
    reg_data[0] = 0x04, ml7396_regwrite(REG_ADR_TX_PR_LEN,           reg_data, 1);  /* more than 0x04 */
    reg_data[0] = 0x1f, ml7396_regwrite(REG_ADR_RSSI_LPF_ADJ,        reg_data, 1);
    reg_data[0] = 0x44, ml7396_regwrite(REG_ADR_PLL_CP_ADJ,          reg_data, 1);
    HAL_I2C_read(0x2d, reg_data, 1), ml7396_regwrite(REG_ADR_OSC_ADJ, reg_data, 1);  /* XA */
    if (setup->device_id == DEIVE_ID_LAPIS) {
        HAL_I2C_read(0x80, reg_data, 1), ml7396_regwrite(REG_ADR_OSC_ADJ2, reg_data, 1);  /* XA */
    //  reg_data[0] = 0x06, ml7396_regwrite(REG_ADR_OSC_ADJ2, reg_data, 1);  /* XA */
    //  reg_data[0] = 0x58, ml7396_regwrite(REG_ADR_OSC_ADJ, reg_data, 1);  /* XA */
    }
//#ifdef LAZURITE_MINI
//    HAL_I2C_read(0x81, reg_data, 1), ml7396_regwrite(REG_ADR_PA_REG_ADJ3, reg_data, 1);
//    HAL_I2C_read(0x82, reg_data, 1), ml7396_regwrite(REG_ADR_RF_CNTRL_SET, reg_data, 1);
//#endif
    /* variableness level setting */
    switch (setup->rate) {
    case  50:  /*  50kbps */
        regset = &regset_50kbps;
        break;
    case 100:  /* 100kbps */
        regset = &regset_100kbps;
        break;
    default:
        goto error;
    }
    /* rate setting */
    reg_data[0] = regset->rate, ml7396_regwrite(REG_ADR_DATA_SET, reg_data, 1);
    {/* frequency setting */
        uint32_t freq_ch0, freq_min;
        uint8_t n4, a;
        uint32_t f;

        if (setup->channel < 24 || setup->channel > 61)
            goto error;
        if (setup->rate == 100 && setup->channel == 32)
            goto error;
        /* CCA IDLE WAIT time setting */
        if (setup->channel <= 32) {
            reg_data[0] = 0x01, ml7396_regwrite(REG_ADR_IDLE_WAIT_H, reg_data, 1);
            reg_data[0] = 0x18, ml7396_regwrite(REG_ADR_IDLE_WAIT_L, reg_data, 1);
        } else
        if (setup->channel <= 61 ) {
            reg_data[0] = 0x00, ml7396_regwrite(REG_ADR_IDLE_WAIT_H, reg_data, 1);
        // ARIB 5ms:idle_wait=on, 1.7us:idle_wait=off
            reg_data[0] = 0x64, ml7396_regwrite(REG_ADR_IDLE_WAIT_L, reg_data, 1);
        }
        freq_ch0 = regset->freq[setup->channel - 24];
        /* which assumes a value having lower 2MHz than CH0 frequency a calibration lower limit level
         * (does not handle the floating point arithmetic with the CPU, and entrusts all a compiler)
         */
        freq_min = freq_ch0 - FIXQ(2.0, 20, uint32_t);
        freq_ch0 /= 36;
        freq_min /= 36;
        if (INTQ(freq_min, 20) != INTQ(freq_ch0, 20))  /* invalid as for the setting to step over the 36MHz border */
            goto error;
        n4 = (INTQ(freq_ch0 >> 2, 20) & 0x0f) << 2;  /* 4 times level of n */
        a = (INTQ(freq_ch0, 20) - n4) & 0x03;
        f = (freq_ch0 - ((n4 + a) << 20)) & 0x0fffff;
        reg_data[0] = f >>  0 & 0xff, reg_data[1] = f >>  8 & 0xff, reg_data[2] = f >> 16 & 0x0f;
        reg_data[3] = n4 << 2 | a;
        ml7396_regwrite(REG_ADR_CH0_FL, reg_data, 4);  /* A special command: I set a value of bp.param[BP_PARAM_CH0_FL] */
        n4 = (INTQ(freq_min >> 2, 20) & 0x0f) << 2;  /* 4 times level of n */
        a = (INTQ(freq_min, 20) - n4) & 0x03;
        f = (freq_min - ((n4 + a) << 20)) & 0x0fffff;
        reg_data[0] = f >>  0 & 0xff, reg_data[1] = f >>  8 & 0xff, reg_data[2] = f >> 16 & 0x0f;
        reg_data[3] = n4 << 2 | a;  /* These data are not used */
        /* A special command: I set a value of bp.param[BP_PARAM_MIN_FL] */
        ml7396_regwrite(REG_ADR_VCO_CAL_MIN_FL, reg_data, 3);
        /* bandwidth 400kHz */
        reg_data[0] = 0x07, ml7396_regwrite(REG_ADR_VCO_CAL_MAX_N, reg_data, 1);
    }
    {
        uint16_t n;

        /* bandwidth setting */
        n = regset->chspc / 36;
        reg_data[0] = n >>  0 & 0xff, reg_data[1] = n >>  8 & 0xff;
        ml7396_regwrite(REG_ADR_CH_SPACE_L, reg_data, 2);
        /* IF frequency setting */
        n = regset->iffreq / 36;
        reg_data[0] = n >>  8 & 0xff, reg_data[1] = n >>  0 & 0xff;
        ml7396_regwrite(REG_ADR_IF_FREQ_H, reg_data, 2);
        ml7396_regwrite(REG_ADR_IF_FREQ_AFC_H, reg_data, 2);
        n = regset->iffreq_cca / 36;
        reg_data[0] = n >>  8 & 0xff, reg_data[1] = n >>  0 & 0xff;
        ml7396_regwrite(REG_ADR_IF_FREQ_CCA_H, reg_data, 2);
    }
    {  /* BPF setting */
        uint8_t bpf;
        uint16_t n;

        ml7396_regread(REG_ADR_BPF_ADJ_OFFSET, reg_data, 1), bpf = reg_data[0];
        if (bpf & 0x80)
            n = regset->ref + (uint16_t)INTQ((uint32_t)(bpf & 0x7f) * regset->coef, 14);
        else
            n = regset->ref - (uint16_t)INTQ((uint32_t)(bpf & 0x7f) * regset->coef, 14);
        reg_data[0] = n >> 8 & 0xff, reg_data[1] = n >> 0 & 0xff;
        ml7396_regwrite(REG_ADR_BPF_ADJ_H,     reg_data, 2);
        ml7396_regwrite(REG_ADR_BPF_AFC_ADJ_H, reg_data, 2);
        if (bpf & 0x80)
            n = regset->ref_cca + (uint16_t)INTQ((uint32_t)(bpf & 0x7f) * regset->coef_cca, 14);
        else
            n = regset->ref_cca - (uint16_t)INTQ((uint32_t)(bpf & 0x7f) * regset->coef_cca, 14);
        reg_data[0] = n >> 8 & 0xff, reg_data[1] = n >> 0 & 0xff;
        ml7396_regwrite(REG_ADR_BPF_CCA_ADJ_H, reg_data, 2);
    }

    reg_data[0] = 0x2c, ml7396_regwrite(REG_ADR_PRIVATE_BPF_CAP1,  reg_data, 1);
    reg_data[0] = 0xc0, ml7396_regwrite(REG_ADR_PRIVATE_BPF_CAP2,  reg_data, 1);
    reg_data[0] = 0x17, ml7396_regwrite(REG_ADR_PRIVATE_BPF_ADJ1,  reg_data, 1);
    reg_data[0] = 0x17, ml7396_regwrite(REG_ADR_PRIVATE_BPF_ADJ2,  reg_data, 1);

    /* GFSK Frequency shift setting */
    reg_data[0] = regset->fdev >> 0 & 0xff, reg_data[1] = regset->fdev >> 8 & 0xff;
    reg_data[0] = 0xb0, ml7396_regwrite(REG_ADR_F_DEV_L, reg_data, 2);
    /* Hidden register setting */
    reg_data[0] = regset->reg1, ml7396_regwrite(2,0x0e, reg_data, 1);
    /* diversity search setting */
    reg_data[0] = regset->div, ml7396_regwrite(REG_ADR_2DIV_SEARCH, reg_data, 1);

    /* own apparatus address acquisition */
    HAL_I2C_read(0x26, reg_data, 2), setup->address = H2LS(*reg_data);

    status = 0;
error:
    return status;
}


PHY_PARAM *phy_init(void)
{
	memset(reg.rdata,0,sizeof(reg.rdata));
	memset(reg.wdata,0,sizeof(reg.wdata));
	phy.in.size = BUFFER_SIZE;
	phy.in.data = reg.rdata;
	phy.in.len = 0;
	phy.out.size = BUFFER_SIZE;
	phy.out.len = 0;
	phy.out.data = reg.wdata;

	return &phy;
}

int phy_set_trx(uint8_t state)
{
    return 0;
}
int phy_get_trx(void)
{
    return 0;
}
int phy_set_cca(void)
{
    return 0;
}
int phy_get_ed(void)
{
    return 0;
}

