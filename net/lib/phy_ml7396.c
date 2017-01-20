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

#include "hwif/random.h"
#include "hwif/hal.h"
#include "hwif/hal-lzpi.h"
#include "errno.h"
#include "endian.h"
#include "common_lazurite.h"
#include "common-lzpi.h"
#include "phy_lazurite.h"
#include "phy_ml7396.h"


/*
 --------------------------------------------------------------
                          Define section
 --------------------------------------------------------------
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

/* headware interrupt */
#define HW_EVENT_ALL_MASK     0x00000000  /* Interrupt all mask */
#define HW_EVENT_VCO_CAL_DONE 0x00000004  /* VCO CAL DONE */
#define HW_EVENT_FIFO_CLEAR   0x000000C0  /* FIFO_EMPTY */
#define HW_EVENT_FIFO_EMPTY   0x00000010  /* FIFO_EMPTY */
#define HW_EVENT_FIFO_FULL    0x00000020  /* FIFO_FULL */
#define HW_EVENT_CCA_DONE     0x00000100  /* CCA DONE */
#define HW_EVENT_RF_STATUS    0x00000400  /* RF status */
#define HW_EVENT_TX_DONE      0x00030000  /* TX complete */
#define HW_EVENT_RX_DONE      0x000C0000  /* RX complete */
#define HW_EVENT_CRC_ERROR    0x00300000  /* CRC error */
#define HW_EVENT_TX_FIFO_DONE 0x00C00000  /* FIFO complete */
#define HW_EVENT_TIMEOUT      0x80000000  /* Timer timeout */

/* software interrupt */
#define SW_EVENT_SETUP   1  /* 初期化 */
#define SW_EVENT_RXSTART 2  /* パケット受信開始 */
#define SW_EVENT_RXSTOP  3  /* パケット受信停止 */
#define SW_EVENT_TXSTART 4  /* パケット送信開始 */
#define SW_EVENT_SLEEP   5  /* 省電力状態へ移行 */
#define SW_EVENT_WAKEUP  6  /* 省電力状態から復帰 */

#define PHY_REG_SET_TX_DONE_RX   0x20
#define PHY_REG_SET_TX_DONE_OFF  0x10

#define UNIT_BAKOFF_PERIOD  300
#define DEFAUL_BAKOF        1000
/*
 ---------------------------------------------------------------
                         Struct and Enum section
 ---------------------------------------------------------------
 */

/* 各状態における割り込み許可状況 */
static const uint32_t event_enable[] = {
	0,                                                                             /* ML7396_StateReset */
	HW_EVENT_RX_DONE|HW_EVENT_FIFO_FULL|HW_EVENT_CRC_ERROR,                   /* ML7396_StateIdle */
	HW_EVENT_TX_DONE|HW_EVENT_FIFO_EMPTY,                                     /* ML7396_StateSendACK */
	HW_EVENT_TX_DONE|HW_EVENT_FIFO_EMPTY|HW_EVENT_CCA_DONE|HW_EVENT_TIMEOUT,  /* ML7396_StateSending */
	HW_EVENT_RX_DONE|HW_EVENT_FIFO_FULL|HW_EVENT_CRC_ERROR|HW_EVENT_TIMEOUT,  /* ML7396_StateWaitACK */
	0                                                                              /* ML7396_StateSleep */
};

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



typedef enum {
	CCA_FAST,                    /* CCA minmum */
	CCA_IDLE_EN,                 /* CCA Idle detection */
	CCA_RETRY,                   /* CCA with BACKOFF */
	CCA_STOP                     /* CCA stop */
} CCA_REQ;


typedef enum{
    PHY_ST_FORCE_TRXOFF=0x03,
    PHY_ST_RXON=0x06,
    PHY_ST_TXON=0x09,
    PHY_ST_TRXOFF=0x08,
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



static PHY_PARAM phy;


/*
 ------------------------------------------------------------------
                      Private function section
 ------------------------------------------------------------------
 */
/******************************************************************************/
/*! @brief Register access of the ML7396 module
   The reading and writing of the SPI bus
   wdata[]: Data sequence to write in
   size: The number of the data to read and write
   rdata[]: Sequence to store the data which I began to read in
 ******************************************************************************/
static void ml7396_hwif_spi_transfer(const uint8_t *wdata, uint8_t *rdata, uint8_t size)
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
static void regbank(uint8_t bank) {

    switch (bank) {
    case 0:  /* BANK0 */
    case 1:  /* BANK1 */
    case 2:  /* BANK2 */
    case 8:  /* BANK0 + access enable */
    case 9:  /* BANK1 + access enable */
    case 10: /* BANK2 + access enable */
        if (bank != reg.bank) {
            reg.wdata[0] = (0x00<<1)|0x01, reg.wdata[1] = bank&0x03;
            if(bank > 2) reg.wdata[1] = reg.wdata[1] | 0x80;
            ml7396_hwif_spi_transfer(reg.wdata, reg.rdata, 2);
            reg.bank = bank;
        }
        break;
    case 0xff:
        reg.lock = 0;
        reg.bank = bank;
        break;
    }
    



/*
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif


    if (bank == 0xff){
        reg.lock = 0;
        reg.bank = bank;
    }else if(bank&0x0b){
        if (bank != reg.bank) {
            reg.wdata[0] = (0x00<<1)|0x01, reg.wdata[1] = bank&0x03;
            if(bank > 2) reg.wdata[1] = reg.wdata[1] | 0x80;
            ml7396_hwif_spi_transfer(reg.wdata, reg.rdata, 2);
            reg.bank = bank;
        }
    }
*/
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
        ml7396_hwif_spi_transfer(reg.wdata, reg.rdata, size + 1);
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
        ml7396_hwif_spi_transfer(reg.rdata, reg.rdata, size + 1);
        memcpy(data, reg.rdata, size);
    }
    --reg.lock;
//	__EI();
}


static void phy_pi_mesg(void)
{
#ifndef LAZURITE_IDE
    uint8_t reg_data[6];
    if(module_test & MODE_PHY_DEBUG) {

        reg_rd(REG_ADR_INT_EN_GRP1, reg_data, 4);
        printk(KERN_INFO"DEBUG PHY INTEN1: %s,%s,%x\n",__FILE__,__func__,reg_data[0]);
        printk(KERN_INFO"DEBUG PHY INTEN2: %s,%s,%x\n",__FILE__,__func__,reg_data[1]);
        printk(KERN_INFO"DEBUG PHY INTEN3: %s,%s,%x\n",__FILE__,__func__,reg_data[2]);
        printk(KERN_INFO"DEBUG PHY INTEN4: %s,%s,%x\n",__FILE__,__func__,reg_data[3]);

        reg_rd(REG_ADR_INT_SOURCE_GRP1, reg_data, 4);
        printk(KERN_INFO"DEBUG PHY INTS1: %s,%s,%x\n",__FILE__,__func__,reg_data[0]);
        printk(KERN_INFO"DEBUG PHY INTS2: %s,%s,%x\n",__FILE__,__func__,reg_data[1]);
        printk(KERN_INFO"DEBUG PHY INTS3: %s,%s,%x\n",__FILE__,__func__,reg_data[2]);
        printk(KERN_INFO"DEBUG PHY INTS4: %s,%s,%x\n",__FILE__,__func__,reg_data[3]);

        reg_rd(REG_ADR_RF_STATUS, reg_data, 1);
        printk(KERN_INFO"DEBUG PHY: %s,%s,%x\n",__FILE__,__func__,reg_data[0]);
    }
#endif
}


/******************************************************************************/
/*! @brief Enable interrupt / Diseable interrupt
 * @detail Original function was REG_INTEN
 * @issue
 ******************************************************************************/
static void phy_inten(uint32_t inten)
{
    uint8_t reg_data[4];
    reg_data[0] = (uint8_t)((inten) >>  0) | 0xc0;
    reg_data[1] = (uint8_t)((inten) >>  8);
    reg_data[2] = (uint8_t)((inten) >> 16);
    reg_data[3] = (uint8_t)((inten) >> 24);
    reg_wr(REG_ADR_INT_EN_GRP1, reg_data, 4);
}


/******************************************************************************/
/*! @brief Clear interrupt 
 * @detail Original function was REG_INTCLR
 * @issue
 ******************************************************************************/
static void phy_intclr(uint32_t intclr)
{
    uint8_t reg_data[4];
    phy_pi_mesg();
    reg_data[0] = ~(uint8_t)((intclr) >>  0);
    reg_data[1] = ~(uint8_t)((intclr) >>  8);
    reg_data[2] = ~(uint8_t)((intclr) >> 16);
    reg_data[3] = ~(uint8_t)((intclr) >> 24);
    reg_wr(REG_ADR_INT_SOURCE_GRP1, reg_data, 4);
}


static void phy_set_trx_state(PHY_TRX_STATE state) {
    uint8_t reg_data = state;
    reg_wr(REG_ADR_RF_STATUS, &reg_data, 1);
    HAL_delayMicroseconds(200);
}


static void vco_cal(void) {

    uint8_t reg_data[4];

#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
    reg_rd(REG_ADR_PACKET_MODE_SET, reg_data,1);
    reg_data[0] |=  0x1a;
    reg_wr(REG_ADR_PACKET_MODE_SET, reg_data,1);
    reg_rd(REG_ADR_FEC_CRC_SET, reg_data,1);
    reg_data[0] |=  0x0b, reg_data[0] &= ~0x04;
    reg_wr(REG_ADR_FEC_CRC_SET, reg_data,1);
    reg_data[0]=0x00;
    reg_wr(REG_ADR_TX_ALARM_LH,reg_data,1);
    reg_wr(REG_ADR_TX_ALARM_HL,reg_data,1); 
    reg_wr(REG_ADR_RX_ALARM_LH,reg_data,1);
    reg_wr(REG_ADR_RX_ALARM_HL,reg_data,1);
    reg_data[0]=0x01;
    reg_wr(REG_ADR_VCO_CAL_START, reg_data,1);
    phy_inten(HW_EVENT_ALL_MASK);
	do {
        HAL_delayMicroseconds(100);
        reg_rd(REG_ADR_INT_SOURCE_GRP1, reg_data, 1);
	} while (!(reg_data[0] & 0x04));
    phy_intclr(HW_EVENT_VCO_CAL_DONE);
}


// static void backoffTimer(EM_Data *em_data){
static void phy_backoffTimer(void){

	uint16_t cca_wait;

	cca_wait = (rand()&0x07) * UNIT_BAKOFF_PERIOD;
	if (!cca_wait) cca_wait = DEFAUL_BAKOF;
	HAL_delayMicroseconds(cca_wait);
}


static void phy_cca_ctrl(CCA_REQ state) {

    uint8_t reg_cca_cntl;
    uint8_t reg_idl_wait;
    uint8_t reg_data;

    phy_set_trx_state(PHY_ST_TRXOFF);

    if (state == CCA_STOP){
        reg_data = 0x64;
        reg_wr(REG_ADR_DEMSET3, &reg_data, 1);
        reg_data = 0x27;
        reg_wr(REG_ADR_DEMSET14, &reg_data, 1);
        reg_cca_cntl = 0x00;
        reg_idl_wait = 0x00;
        reg_wr(REG_ADR_IDLE_WAIT_L, &reg_idl_wait, 1);
        reg_wr(REG_ADR_CCA_CNTRL, &reg_cca_cntl, 1);
    }else{
        reg_data = 0x00;
        reg_wr(REG_ADR_DEMSET3, &reg_data, 1);
        reg_wr(REG_ADR_DEMSET14,&reg_data, 1);

        if (state == CCA_FAST) {
            reg_cca_cntl = 0x10;
            reg_idl_wait = 0x00;
        } else
        if (state == CCA_IDLE_EN) {
            reg_cca_cntl = 0x18;
            reg_idl_wait = 0x64;
        } else
        if (state == CCA_RETRY) {
            phy_backoffTimer();
            reg_cca_cntl = 0x10;
            reg_idl_wait = 0x64;
        }
        reg_wr(REG_ADR_IDLE_WAIT_L, &reg_idl_wait, 1);
        reg_wr(REG_ADR_CCA_CNTRL, &reg_cca_cntl, 1);
        phy_set_trx_state(PHY_ST_RXON);
    }
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
			reg_rd(REG_ADR_CCA_CNTRL, &em_data.cca_rslt, 1);
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
 -------------------------------------------------------------
                    Public interrupt section
 -------------------------------------------------------------
 */
/******************************************************************************/
/*! @brief Interrupt handler registration of the ML7396 module
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
 * @detail Interrupt permission delay cancellation of the ML7396 module
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
 * @detail The delay that interrupt of the ML7396 module is prohibited in it.
 *         I delay whether it is admitted again until I am cleared.
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
int phy_timer_di(void)
{
    int status = -1;
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
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
int phy_timer_start(uint16_t msec)
{
    int status = -1;
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
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
int phy_timer_stop(void)
{
    int status = -1;
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
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
int phy_setup(uint8_t page,uint8_t ch)
{

    uint8_t txPower = 20;
    uint8_t device_id;
    uint16_t address;

    int status = -1;
    const REGSET *regset;
    uint8_t reg_data[4];

#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
    reg_data[0]=0xC0; reg_data[1]=0x00; reg_data[2]=0x00; reg_data[3]=0x00;
    reg_wr(REG_ADR_INT_SOURCE_GRP1, reg_data, 4);
    
    HAL_I2C_read(0x23, reg_data, 1), device_id = reg_data[0];
    reg_data[0] = 0x0f, reg_wr(REG_ADR_CLK_SET,             reg_data, 1);
    reg_data[0] = 0x22, reg_wr(REG_ADR_RX_PR_LEN_SFD_LEN,   reg_data, 1);
    reg_data[0] = 0x00, reg_wr(REG_ADR_SYNC_CONDITION,      reg_data, 1);
    reg_data[0] = 0x04, reg_wr(REG_ADR_2DIV_CNTRL,          reg_data, 1);
#ifdef LAZURITE_MINI
    reg_data[0] = 0x02, reg_wr(REG_ADR_2DIV_CNTRL,          reg_data, 1);
#else
    if (device_id == DEIVE_ID_LAPIS)
        reg_data[0] = 0x0A, reg_wr(REG_ADR_2DIV_CNTRL,          reg_data, 1);
#endif
    reg_data[0] = 0x04, reg_wr(REG_ADR_SYNC_MODE,           reg_data, 1);
    reg_data[0] = 0x10, reg_wr(REG_ADR_RAMP_CNTRL,          reg_data, 1);
    reg_data[0] = 0x1e, reg_wr(REG_ADR_GAIN_MtoL,           reg_data, 1);
    reg_data[0] = 0x02, reg_wr(REG_ADR_GAIN_LtoM,           reg_data, 1);
    reg_data[0] = 0x9e, reg_wr(REG_ADR_GAIN_HtoM,           reg_data, 1);
    reg_data[0] = 0x02, reg_wr(REG_ADR_GAIN_MtoH,           reg_data, 1);
    reg_data[0] = 0x15, reg_wr(REG_ADR_RSSI_ADJ_M,          reg_data, 1);
    reg_data[0] = 0x2b, reg_wr(REG_ADR_RSSI_ADJ_L,          reg_data, 1);
    reg_data[0] = 0x22, reg_wr(REG_ADR_RSSI_STABLE_TIME,    reg_data, 1);
    reg_data[0] = 0xd4, reg_wr(REG_ADR_RSSI_VAL_ADJ,        reg_data, 1);
    reg_data[0] = 0x01, reg_wr(REG_ADR_AFC_CNTRL,           reg_data, 1);
    reg_data[0] = 0xaa, reg_wr(REG_ADR_PREAMBLE_SET,        reg_data, 1);
    reg_data[0] = 0x09, reg_wr(REG_ADR_SFD1_SET1,           reg_data, 1);
    reg_data[0] = 0x72, reg_wr(REG_ADR_SFD1_SET2,           reg_data, 1);
    reg_data[0] = 0xf6, reg_wr(REG_ADR_SFD1_SET3,           reg_data, 1);
    reg_data[0] = 0x72, reg_wr(REG_ADR_SFD1_SET4,           reg_data, 1);
    reg_data[0] = 0x5e, reg_wr(REG_ADR_SFD2_SET1,           reg_data, 1);
    reg_data[0] = 0x70, reg_wr(REG_ADR_SFD2_SET2,           reg_data, 1);
    reg_data[0] = 0xc6, reg_wr(REG_ADR_SFD2_SET3,           reg_data, 1);
    reg_data[0] = 0xb4, reg_wr(REG_ADR_SFD2_SET4,           reg_data, 1);
    reg_data[0] = 0xb6, reg_wr(REG_ADR_2DIV_GAIN_CNTRL,     reg_data, 1);
    reg_data[0] = 0x84, reg_wr(1,0x39,                      reg_data, 1);  /* Hidden register */
    reg_data[0] = 0x8f, reg_wr(REG_ADR_PLL_CTRL,            reg_data, 1);
    reg_data[0] = 0x32, reg_wr(REG_ADR_RX_ON_ADJ2,          reg_data, 1);
    reg_data[0] = 0x0f, reg_wr(REG_ADR_LNA_GAIN_ADJ_M,      reg_data, 1);
    reg_data[0] = 0x01, reg_wr(REG_ADR_LNA_GAIN_ADJ_L,      reg_data, 1);
    reg_data[0] = 0xff, reg_wr(REG_ADR_MIX_GAIN_ADJ_M,      reg_data, 1);
    reg_data[0] = 0xff, reg_wr(REG_ADR_MIX_GAIN_ADJ_L,      reg_data, 1);
    reg_data[0] = 0xb4, reg_wr(REG_ADR_TX_OFF_ADJ1,         reg_data, 1);
    reg_data[0] = 0x01, reg_wr(REG_ADR_RSSI_SLOPE_ADJ,      reg_data, 1);
    reg_data[0] = 0x04, reg_wr(REG_ADR_PA_ON_ADJ,           reg_data, 1);
    reg_data[0] = 0x0a, reg_wr(REG_ADR_RX_ON_ADJ,           reg_data, 1);
    reg_data[0] = 0x00, reg_wr(REG_ADR_RXD_ADJ,             reg_data, 1);
    reg_data[0] = 0x2c, reg_wr(2,0x2d,                      reg_data, 1);  /* Hidden register */
    reg_data[0] = 0xc0, reg_wr(2,0x2e,                      reg_data, 1);  /* Hidden register */
    reg_data[0] = 0x17, reg_wr(2,0x2f,                      reg_data, 1);  /* Hidden register */
    reg_data[0] = 0x17, reg_wr(2,0x30,                      reg_data, 1);  /* Hidden register */
    HAL_I2C_read(0x2b, reg_data, 1), reg_wr(REG_ADR_PA_ADJ1, reg_data, 1);  /*  1mW rough adjustment */
    HAL_I2C_read(0x29, reg_data, 1), reg_wr(REG_ADR_PA_ADJ3, reg_data, 1);  /* 20mW rough adjustment */
    switch (txPower) {
    case  1:  /*  1mW */
        HAL_I2C_read(0x2c, reg_data, 1), reg_wr(REG_ADR_PA_REG_FINE_ADJ, reg_data, 1);
        reg_data[0] = 0x01, reg_wr(REG_ADR_PA_CNTRL,                    reg_data, 1);
        break;
    case 20:  /* 20mW */
        HAL_I2C_read(0x2a, reg_data, 1), reg_wr(REG_ADR_PA_REG_FINE_ADJ, reg_data, 1);
        reg_data[0] = 0x13, reg_wr(REG_ADR_PA_CNTRL,                    reg_data, 1);
        break;
    default:
        goto error;
    }
    reg_data[0] = 0x0f, reg_wr(REG_ADR_SW_OUT_RAMP_ADJ,     reg_data, 1);
    reg_data[0] = 0x08, reg_wr(REG_ADR_IQ_MAG_ADJ,          reg_data, 1);
    reg_data[0] = 0x20, reg_wr(REG_ADR_IQ_PHASE_ADJ,        reg_data, 1);
#ifdef LAZURITE_MINI
    reg_data[0] = 0x07, reg_wr(REG_ADR_PA_REG_ADJ1,         reg_data, 1);
    reg_data[0] = 0x07, reg_wr(REG_ADR_PA_REG_ADJ2,         reg_data, 1);
    reg_data[0] = 0x07, reg_wr(REG_ADR_PA_REG_ADJ3,         reg_data, 1);
    reg_data[0] = 0x30, reg_wr(REG_ADR_CCA_LEVEL,           reg_data, 1);
#else
    reg_data[0] = 0x06, reg_wr(REG_ADR_PA_REG_ADJ1,         reg_data, 1);
    reg_data[0] = 0x01, reg_wr(REG_ADR_PA_REG_ADJ2,         reg_data, 1);
    reg_data[0] = 0x01, reg_wr(REG_ADR_PA_REG_ADJ3,         reg_data, 1);
    reg_data[0] = 0x55, reg_wr(REG_ADR_CCA_LEVEL,           reg_data, 1);
#endif
    reg_data[0] = 0x04, reg_wr(REG_ADR_TX_PR_LEN,           reg_data, 1);  /* more than 0x04 */
    reg_data[0] = 0x1f, reg_wr(REG_ADR_RSSI_LPF_ADJ,        reg_data, 1);
    reg_data[0] = 0x44, reg_wr(REG_ADR_PLL_CP_ADJ,          reg_data, 1);
    HAL_I2C_read(0x2d, reg_data, 1), reg_wr(REG_ADR_OSC_ADJ, reg_data, 1);  /* XA */
    if (device_id == DEIVE_ID_LAPIS) {
        HAL_I2C_read(0x80, reg_data, 1), reg_wr(REG_ADR_OSC_ADJ2, reg_data, 1);  /* XA */
    //  reg_data[0] = 0x06, reg_wr(REG_ADR_OSC_ADJ2, reg_data, 1);  /* XA */
    //  reg_data[0] = 0x58, reg_wr(REG_ADR_OSC_ADJ, reg_data, 1);  /* XA */
    }
//#ifdef LAZURITE_MINI
//    HAL_I2C_read(0x81, reg_data, 1), reg_wr(REG_ADR_PA_REG_ADJ3, reg_data, 1);
//    HAL_I2C_read(0x82, reg_data, 1), reg_wr(REG_ADR_RF_CNTRL_SET, reg_data, 1);
//#endif
    /* variableness level setting */

    switch (page) {
    case  1:  /*  50kbps */
        regset = &regset_50kbps;
        break;
    case 2:  /* 100kbps */
        regset = &regset_100kbps;
        break;
    default:
        goto error;
    }
    /* rate setting */
    reg_data[0] = regset->rate, reg_wr(REG_ADR_DATA_SET, reg_data, 1);
    {/* frequency setting */
        uint32_t freq_ch0, freq_min;
        uint8_t n4, a;
        uint32_t f;

        if (ch < 24 || ch > 61)
            goto error;
        if (page == 2 && ch == 32)
            goto error;
        /* CCA IDLE WAIT time setting */
        if (ch <= 32) {
            reg_data[0] = 0x01, reg_wr(REG_ADR_IDLE_WAIT_H, reg_data, 1);
            reg_data[0] = 0x18, reg_wr(REG_ADR_IDLE_WAIT_L, reg_data, 1);
        } else
        if (ch <= 61 ) {
            reg_data[0] = 0x00, reg_wr(REG_ADR_IDLE_WAIT_H, reg_data, 1);
        // ARIB 5ms:idle_wait=on, 1.7us:idle_wait=off
            reg_data[0] = 0x64, reg_wr(REG_ADR_IDLE_WAIT_L, reg_data, 1);
        }
        freq_ch0 = regset->freq[ch - 24];
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
        reg_wr(REG_ADR_CH0_FL, reg_data, 4);  /* A special command: I set a value of bp.param[BP_PARAM_CH0_FL] */
        n4 = (INTQ(freq_min >> 2, 20) & 0x0f) << 2;  /* 4 times level of n */
        a = (INTQ(freq_min, 20) - n4) & 0x03;
        f = (freq_min - ((n4 + a) << 20)) & 0x0fffff;
        reg_data[0] = f >>  0 & 0xff, reg_data[1] = f >>  8 & 0xff, reg_data[2] = f >> 16 & 0x0f;
        reg_data[3] = n4 << 2 | a;  /* These data are not used */
        /* A special command: I set a value of bp.param[BP_PARAM_MIN_FL] */
        reg_wr(REG_ADR_VCO_CAL_MIN_FL, reg_data, 3);
        /* bandwidth 400kHz */
        reg_data[0] = 0x07, reg_wr(REG_ADR_VCO_CAL_MAX_N, reg_data, 1);
    }
    {
        uint16_t n;

        /* bandwidth setting */
        n = regset->chspc / 36;
        reg_data[0] = n >>  0 & 0xff, reg_data[1] = n >>  8 & 0xff;
        reg_wr(REG_ADR_CH_SPACE_L, reg_data, 2);
        /* IF frequency setting */
        n = regset->iffreq / 36;
        reg_data[0] = n >>  8 & 0xff, reg_data[1] = n >>  0 & 0xff;
        reg_wr(REG_ADR_IF_FREQ_H, reg_data, 2);
        reg_wr(REG_ADR_IF_FREQ_AFC_H, reg_data, 2);
        n = regset->iffreq_cca / 36;
        reg_data[0] = n >>  8 & 0xff, reg_data[1] = n >>  0 & 0xff;
        reg_wr(REG_ADR_IF_FREQ_CCA_H, reg_data, 2);
    }
    {  /* BPF setting */
        uint8_t bpf;
        uint16_t n;

        reg_rd(REG_ADR_BPF_ADJ_OFFSET, reg_data, 1), bpf = reg_data[0];
        if (bpf & 0x80)
            n = regset->ref + (uint16_t)INTQ((uint32_t)(bpf & 0x7f) * regset->coef, 14);
        else
            n = regset->ref - (uint16_t)INTQ((uint32_t)(bpf & 0x7f) * regset->coef, 14);
        reg_data[0] = n >> 8 & 0xff, reg_data[1] = n >> 0 & 0xff;
        reg_wr(REG_ADR_BPF_ADJ_H,     reg_data, 2);
        reg_wr(REG_ADR_BPF_AFC_ADJ_H, reg_data, 2);
        if (bpf & 0x80)
            n = regset->ref_cca + (uint16_t)INTQ((uint32_t)(bpf & 0x7f) * regset->coef_cca, 14);
        else
            n = regset->ref_cca - (uint16_t)INTQ((uint32_t)(bpf & 0x7f) * regset->coef_cca, 14);
        reg_data[0] = n >> 8 & 0xff, reg_data[1] = n >> 0 & 0xff;
        reg_wr(REG_ADR_BPF_CCA_ADJ_H, reg_data, 2);
    }

    reg_data[0] = 0x2c, reg_wr(REG_ADR_PRIVATE_BPF_CAP1,  reg_data, 1);
    reg_data[0] = 0xc0, reg_wr(REG_ADR_PRIVATE_BPF_CAP2,  reg_data, 1);
    reg_data[0] = 0x17, reg_wr(REG_ADR_PRIVATE_BPF_ADJ1,  reg_data, 1);
    reg_data[0] = 0x17, reg_wr(REG_ADR_PRIVATE_BPF_ADJ2,  reg_data, 1);

    /* GFSK Frequency shift setting */
    reg_data[0] = regset->fdev >> 0 & 0xff, reg_data[1] = regset->fdev >> 8 & 0xff;
    reg_data[0] = 0xb0, reg_wr(REG_ADR_F_DEV_L, reg_data, 2);
    /* Hidden register setting */
    reg_data[0] = regset->reg1, reg_wr(2,0x0e, reg_data, 1);
    /* diversity search setting */
    reg_data[0] = regset->div, reg_wr(REG_ADR_2DIV_SEARCH, reg_data, 1);

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
#ifdef ML7396_HWIF_NOTHAVE_TIMER_DI
    hwif.timer.active = Disable;
    hwif.timer.call_count = 0;
#endif  /* #ifdef ML7396_HWIF_NOTHAVE_TIMER_DI */
    status = HAL_init(0x50,8);
    if(status == 0){
    //  HAL_SPI_setup();
    //  HAL_GPIO_setup();
        HAL_TIMER_setup();
    //  HAL_I2C_setup();
        phy_timer_tick(&wait_t);
        regbank(0xff);
        do {
            HAL_delayMicroseconds(100);
            reg_rd(REG_ADR_CLK_SET, &reg_data, 1);
        } while (!(reg_data & 0x80));
        reg_data = 0x00; reg_wr(REG_ADR_INT_SOURCE_GRP1, &reg_data, 1);
    }

	memset(reg.rdata,0,sizeof(reg.rdata));
	memset(reg.wdata,0,sizeof(reg.wdata));
	phy.in.size = BUFFER_SIZE;
	phy.in.data = reg.rdata;
	phy.in.len = 0;
	phy.out.size = BUFFER_SIZE;
	phy.out.len = 0;
	phy.out.data = reg.wdata;

    reg_rd(REG_ADR_RF_STATUS, &reg_data, 1);

	return &phy;
}


void phy_rst(void)
{
    uint8_t reg_data[1];

    reg_data[0] = 0x03;
    reg_wr(REG_ADR_RF_STATUS, reg_data, 1);
    HAL_delayMicroseconds(200);
    reg_data[0] = 0x88;
    reg_wr(REG_ADR_RST_SET, reg_data, 1);
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}


void phy_trxoff(void)
{
    phy_set_trx_state(PHY_ST_TRXOFF);
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}


void phy_addr_filt(void)
{
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}


int phy_ed(void)
{
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
    return 0;
}


void phy_sleep(void)
{
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}


/*
 ------------------------------------------------------------------
                      Public state machine section
 ------------------------------------------------------------------
 */
void phy_stm_promiscuous(void)
{
    phy_set_trx_state(PHY_ST_RXON);
    phy_inten(HW_EVENT_RX_DONE | HW_EVENT_CRC_ERROR);
    HAL_wait_event();
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}


void phy_stm_receive(void)
{
    phy_inten(HW_EVENT_RX_DONE);
    HAL_wait_event();
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}


uint8_t send_seq;

void phy_stm_send(BUFFER buff)
{
    uint8_t reg_data[2];
    uint16_t length = buff.len;
//  uint8_t *payload = buff.data;
//  uint8_t payload[18-2]; // = "Hello"; // "LAPIS Lazurite RF system";
    uint8_t payload[] = "         LAPIS Lazurite RF system\r\n";
    uint8_t i=0;

    payload[i] = 0x21;
    payload[++i] = 0xA8;
    payload[++i] = ++send_seq;
    payload[++i] = 0xcd;
    payload[++i] = 0xab;
    payload[++i] = 0x70;
    payload[++i] = 0x66;
//    payload[++i] = 0xcd;
//    payload[++i] = 0xab;
    payload[++i] = 0x54;
    payload[++i] = 0xac;
//    payload[++i] = 0x55;//"H";
//    payload[++i] = 0x55;//"e";
//    payload[++i] = 0x55;//"l";
//    payload[++i] =0x55;// "l";
//    payload[++i] =0x55;// "o";
//    payload[++i] =0x0d;//  CR
//    payload[++i] =0x00;//  LF

    // make fcf
    length = sizeof(payload);
    reg_data[0] = 0x18;             // PHR
    reg_data[1] = 2 + length;       // length : crc size + payload length
    reg_wr(REG_ADR_WR_TX_FIFO, reg_data, 2); 

    // make payload
    reg_wr(REG_ADR_WR_TX_FIFO, payload, length);
    HAL_delayMicroseconds(300);

    reg_data[0] = PHY_REG_SET_TX_DONE_RX;
	reg_wr(REG_ADR_ACK_TIMER_EN, reg_data, 1);

    phy_inten(HW_EVENT_TX_FIFO_DONE);
    HAL_wait_event();

#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s,%s,%d\n",__FILE__,__func__,payload,length);
#endif

#if 0
/* 送信バッファ書き込み(先頭データ)
 */
// 2015.05.07 Eiichi Saito : Change PHR CRC length field 0x0800 -> 0x1800
#define REG_TXSTART(_buffer) \
    do { \
        uint16_t _data_size; \
        uint8_t _reg_data[2]; \
        ASSERT((_buffer)->status == ML7396_BUFFER_INIT); \
        _data_size = (_buffer)->size; \
        if (_data_size > (_buffer)->capacity) \
            (_buffer)->status = ML7396_BUFFER_ESIZE; \
        else { \
            _data_size += TXCRC_SIZE; \
            _data_size |= 0x1800; \
            u2n16_set(_data_size, _reg_data); \
            ON_ERROR(reg_wr(REG_ADR_WR_TX_FIFO, _reg_data, 2)); \
            (_buffer)->status = 0; \
        } \
    } while (0)
void REG_TXSTART(ML7396_Buffer* _buffer)
{
    uint16_t _data_size;
    uint8_t reg_data[2]; 
    ASSERT((_buffer)->status == ML7396_BUFFER_INIT); 
    _data_size = (_buffer)->size; 
    if (_data_size > (_buffer)->capacity) 
        (_buffer)->status = ML7396_BUFFER_ESIZE; 
    else { 
        _data_size += TXCRC_SIZE; 
        _data_size |= 0x1800; 
        u2n16_set(_data_size, reg_data); 
        reg_wr(REG_ADR_WR_TX_FIFO, reg_data, 2); 
        (_buffer)->status = 0; 
    }
}

/* 送信バッファ書き込み開始(継続データ)
 * delay 300usecやTX_ONへの遷移中のFIFOアクセス（PLLアンロック）を防止するため。
 *  必要に応じて自動でML7396の状態を RX_ON に変更
 *  FIFO_MARGINが32なので_size変数は224、_data_sizeはパケットレングスになる。
 *  パケットレングスが224以下であれば224以下の値に、244以上であれば224の値を
 *  FIFOライトする値にする。
 */
// 2015.06.08 Eiichi Saito : addition delay
/*
#define REG_TXCONTINUE(_buffer) \
    do { \
        uint8_t _size; \
        uint16_t _data_size; \
        ASSERT((_buffer)->status >= 0); \
        _size = 256-FIFO_MARGIN; \
        _data_size = (_buffer)->size - (_buffer)->status; \
        if (_data_size <= _size) \
            _size = _data_size; \
        if (_size > 0) { \
            ON_ERROR(reg_wr(REG_ADR_WR_TX_FIFO, (_buffer)->data + (_buffer)->status, _size)); \
            (_buffer)->status += _size; \
            HAL_delayMicroseconds(300); \
        } \
    } while (0)
*/
// 2016.4.21 Eiichi Saito: FAST_TX disable
#define REG_TXCONTINUE(_buffer) \
    do { \
        uint8_t _size; \
        ASSERT((_buffer)->status >= 0); \
        _size = (_buffer)->size - (_buffer)->status; \
        if (_size > 0) { \
            ON_ERROR(reg_wr(REG_ADR_WR_TX_FIFO, (_buffer)->data + (_buffer)->status, _size)); \
            (_buffer)->status += _size; \
            HAL_delayMicroseconds(300); \
        } \
    } while (0)
#endif
}


void phy_stm_fifodone(void)
{
    phy_cca_ctrl(CCA_FAST);
    phy_inten(HW_EVENT_CCA_DONE);
    HAL_wait_event();
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}


int phy_stm_ccadone(void)
{
    int status;
    uint8_t reg_data;

    phy_intclr(HW_EVENT_CCA_DONE | HW_EVENT_RF_STATUS);
	reg_rd(REG_ADR_CCA_CNTRL, &reg_data, 1);

    if(reg_data&0x03){
        phy_cca_ctrl(CCA_FAST);
        status = CCA_BUSY;
    }else{
        phy_cca_ctrl(CCA_STOP);
        phy_set_trx_state(PHY_ST_TXON);
        phy_inten(HW_EVENT_TX_DONE);
        status = CCA_IDLE;
    }
    HAL_wait_event();
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG)printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
   return status;
}


void phy_stm_txdone(void)
{
    phy_intclr(HW_EVENT_TX_DONE | HW_EVENT_TX_FIFO_DONE | HW_EVENT_RF_STATUS);
    phy_inten(HW_EVENT_RX_DONE | HW_EVENT_CRC_ERROR);
//  HAL_wait_event();
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG)printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}


void phy_stm_rxdone(void)
{
    phy_intclr(HW_EVENT_RX_DONE | HW_EVENT_CRC_ERROR | HW_EVENT_RF_STATUS);
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG)printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}


void phy_stm_retry(void)
{
    phy_intclr(HW_EVENT_TX_DONE | HW_EVENT_TX_FIFO_DONE | HW_EVENT_RF_STATUS);
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}

#if 0
/* コールバック関数呼び出し
 */
#define BUFFER_DONE(_buffer) \
    do { \
        if ((_buffer)->opt.common.done != NULL) \
            (_buffer)->opt.common.done(_buffer); \
    } while (0)


/** よく使うレジスタ操作
 *
 * 受信手順: (FIFOデータの最後にED値が付く設定である事)
 *   REG_RXON();
 *   連続受信時の繰り返し範囲 {
 *     FIFO_FULL 割り込み待ち
 *     REG_RXSTART(&buffer);
 *     REG_RXCONTINUE(&buffer);
 *     何度か繰り返し {
 *       FIFO_FULL 割り込み待ち
 *       REG_RXCONTINUE(&buffer);
 *     }
 *     受信完了割り込み待ち
 *     REG_RXCONTINUE(&buffer);
 *     REG_RXDONE(&buffer);
 *   (この時点で受信したデータは揃っている)
 *     CRCエラー割り込みあり {
 *       CRCエラー処理
 *     } else {
 *       ACKを返す場合 {
 *         ACKデータに対して「送信手順」を実行
 *       }
 *       正常終了処理
 *     }
 *   }
 *   REG_TRXOFF();
 *
 * 送信手順: (自動送信OFF(送信完了で自動的にTRX_OFFになる)が有効である事)
 *   REG_TRXOFF();
 *   連続送信時の繰り返し範囲 {
 *     REG_CCAEN(_type);
 *     REG_RXON();
 *     CCA検出完了割り込み待ち
 *     REG_TRXOFF();
 *     キャリアなし {
 *       REG_TXSTART(&buffer);
 *       REG_TXCONTINUE(&buffer);
 *       何度か繰り返し {
 *         FIFO_EMPTY 割り込み待ち
 *         REG_TXCONTINUE(&buffer);
 *       }
 *       送信完了割り込み待ち
 *   (この時点で送信は完了している)
 *       ACKを待つ場合 {
 *         ACKデータに対して「受信手順」を実行
 *       }
 *       正常終了処理
 *     } else {
 *       キャリアありエラー処理
 *     }
 *   }
 */

/* レジスタ1バイト書き込み
 */
#define REG_WRB(_addr, _data) \
    do { \
        uint8_t _reg_data[1]; \
        _reg_data[0] = (_data); \
        ON_ERROR(reg_wr(_addr, _reg_data, 1)); \
    } while (0)

/* レジスタ1バイト読み出し
 */
#define REG_RDB(_addr, _data) \
    do { \
        uint8_t _reg_data[1]; \
        ON_ERROR(reg_rd(_addr, _reg_data, 1));  \
        (_data) = _reg_data[0]; \
    } while (0)




/* 受信バッファ読み出し(先頭データ)
 */
#define REG_RXSTART(_buffer) \
    do { \
        uint16_t _data_size; \
        uint8_t _reg_data[2]; \
        ASSERT((_buffer)->status == ML7396_BUFFER_INIT); \
        ON_ERROR(reg_rd(REG_ADR_RD_RX_FIFO, _reg_data, 2)); \
        _data_size = n2u16(_reg_data) & 0x07ff; \
        if (_data_size < RXCRC_SIZE) { \
            (_buffer)->size = 0; \
            (_buffer)->status = ML7396_BUFFER_ESIZE; \
        } \
        else { \
            _data_size -= RXCRC_SIZE; \
            (_buffer)->size = _data_size; \
            if (_data_size > (_buffer)->capacity)  \
                (_buffer)->status = ML7396_BUFFER_ESIZE; \
            else \
                (_buffer)->status = 0; \
        } \
    } while (0)
void REG_RXSTART(ML7396_Buffer *_buffer)
{
        uint16_t _data_size;
        uint8_t _reg_data[2];
        ASSERT((_buffer)->status == ML7396_BUFFER_INIT);
        reg_rd(REG_ADR_RD_RX_FIFO, _reg_data, 2);
        _data_size = n2u16(_reg_data) & 0x07ff; 
        if (_data_size < RXCRC_SIZE) {
            (_buffer)->size = 0;
            (_buffer)->status = ML7396_BUFFER_ESIZE;
        }
        else {
            _data_size -= RXCRC_SIZE;
            (_buffer)->size = _data_size;
            if (_data_size > (_buffer)->capacity) 
                (_buffer)->status = ML7396_BUFFER_ESIZE;
            else
                (_buffer)->status = 0;
        }
}

/* 受信バッファ読み出し(継続データ)
 *  CRCとED値は読み出さずに残す
 */
#define REG_RXCONTINUE(_buffer) \
    do { \
        uint8_t _size; \
        uint16_t _data_size; \
        ASSERT((_buffer)->status >= 0); \
        _size = 256-FIFO_MARGIN; \
        _data_size = (_buffer)->size - (_buffer)->status; \
        if (_data_size <= _size) \
            _size = _data_size; \
        else \
            --_size; \
        if (_size > 0) { \
            ON_ERROR(reg_rd(REG_ADR_RD_RX_FIFO, (_buffer)->data + (_buffer)->status, _size)); \
            (_buffer)->status += _size; \
        } \
    } while (0)

/* ED値読み出し
 *  REG_RXCONTINUE() でFIFOに残ったCRCの破棄とED値を読みだすので読み出し処理の最後に実行する事
 */
#define REG_RXDONE(_buffer) \
    do { \
        uint8_t _reg_data[4]; \
        ON_ERROR(reg_rd(REG_ADR_RD_RX_FIFO, _reg_data, RXCRC_SIZE)); \
        ON_ERROR(reg_rd(REG_ADR_RD_RX_FIFO, &(_buffer)->opt.common.ed, 1)); \
    } while (0)

#endif
