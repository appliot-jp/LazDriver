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
//	#include <stddef.h>
//	#include <stdint.h>
#else
	#include <linux/stddef.h>
	#include "../common-lzpi.h"
#endif

#include "../phy.h"
#include "phy_ml7396.h"
#include "../hwif/random.h"
#include "../hwif/hal.h"
#include "../errno.h"
#include "../endian.h"
#include "../common_subghz.h"

#ifndef LAZURITE_IDE
#undef ML7396_HWIF_NOTHAVE_TIMER_DI
#endif


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
// 2017.10.3
#define HW_EVENT_ADD_FIL_DONE 0x00000008  /* Address Filter done */
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
    uint8_t rdata[8];     // input buffer 
    uint8_t wdata[8];     // outpu buffer
    uint8_t rfifo[260];     // input buffer 
    uint8_t wfifo[260];     // outpu buffer
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


static uint8_t phy_cca_be;

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


static void fifo_wr(uint8_t bank, uint8_t addr, uint8_t *data, uint8_t size)
{
//	__DI();
    uint8_t *p_header;

    p_header = data - 1;
    if (reg.lock++) {
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"REG LOCK ERR%s,%s,%d\n",__FILE__,__func__,reg.lock);
#endif
    }else{
        regbank(bank);
        *p_header = (addr << 1) | 0x01;
        ml7396_hwif_spi_transfer(p_header, reg.rdata, size + 1);
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


static void fifo_rd(uint8_t bank, uint8_t addr, uint8_t *data, uint8_t size)
{
//	__DI();
    uint8_t *p_header;

    p_header = data - 1;
    if (reg.lock++) {
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"REG LOCK ERR%s,%s,%d\n",__FILE__,__func__,reg.lock);
#endif
    }else{
        regbank(bank);
        *p_header = (addr << 1) | 0x00;
        ml7396_hwif_spi_transfer(p_header, data, size + 1);
    }
    --reg.lock;
//	__EI();
}

/*
static void phy_mesg(void)
{
    uint8_t reg_data[4];
#ifndef LAZURITE_IDE
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
#else
    reg_rd(REG_ADR_INT_EN_GRP1, reg_data, 4);
    reg_rd(REG_ADR_INT_SOURCE_GRP1, reg_data, 4);
    reg_rd(REG_ADR_RF_STATUS, reg_data, 1);
#endif
}
*/

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
    // phy_mesg(); 
    reg_data[0] = ~(uint8_t)((intclr) >>  0);
    reg_data[1] = ~(uint8_t)((intclr) >>  8);
    reg_data[2] = ~(uint8_t)((intclr) >> 16);
    reg_data[3] = ~(uint8_t)((intclr) >> 24);
    reg_wr(REG_ADR_INT_SOURCE_GRP1, reg_data, 4);
}


static void phy_set_trx_state(PHY_TRX_STATE state) {
    uint8_t set_data,get_data,i;
    
    set_data = state;
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

    uint8_t reg_data[4];

    reg_rd(REG_ADR_PACKET_MODE_SET, reg_data,1);
//  reg_data[0] |=  0x1a;
    reg_data[0] |=  0x3a;
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
	do {
        HAL_delayMicroseconds(100);
        reg_rd(REG_ADR_INT_SOURCE_GRP1, reg_data, 1);
	} while (!(reg_data[0] & 0x04));
    phy_intclr(HW_EVENT_VCO_CAL_DONE);
}


static void phy_backoffTimer(void){

	uint16_t cca_wait;

	cca_wait = (rand()&phy_cca_be) * UNIT_BAKOFF_PERIOD;
	if (!cca_wait) cca_wait = DEFAUL_BAKOF;
	HAL_delayMicroseconds(cca_wait);
}


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
//       HAL_TIMER_enableInterrupt();
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
//    HAL_TIMER_disableInterrupt();
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


void phy_wait_mac_event(void)
{
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
    HAL_wait_event(HAL_MAC_EVENT);
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

    phy_rst();

    phy_inten(HW_EVENT_ALL_MASK);
    phy_intclr(~(HW_EVENT_ALL_MASK | HW_EVENT_FIFO_CLEAR));

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
//  phy_inten(HW_EVENT_RX_DONE | HW_EVENT_CRC_ERROR);
    phy_inten(HW_EVENT_RX_DONE);
    phy_set_trx_state(PHY_ST_RXON);
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG)printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}
*/


void phy_rxStart(void)
{
    phy_intclr(~(HW_EVENT_ALL_MASK | HW_EVENT_FIFO_CLEAR));
//  phy_inten(HW_EVENT_RX_DONE | HW_EVENT_CRC_ERROR);
// 2017.10.3
//  phy_inten(HW_EVENT_RX_DONE);
    phy_inten(HW_EVENT_RX_DONE | HW_EVENT_ADD_FIL_DONE);
    phy_rst();
    phy_set_trx_state(PHY_ST_RXON);
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG)printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}


/******************************************************************************/
/*! @brief Writing in data to FIFO
 * Delay 300usec is intended to prevent FIFO access during TX_ON transition.
 * It may become the PLL unlocking when FIFO accesses it.
 ******************************************************************************/
void phy_txStart(BUFFER *buff,uint8_t mode)
{
    uint8_t reg_data[2];
    uint16_t length = buff->len;
    uint8_t *payload = buff->data;

//  if (mode != 2) {
//        phy_set_trx_state(PHY_ST_FORCE_TRXOFF);
//        phy_rst();
//  }

    reg_data[0] = PHY_REG_SET_TX_DONE_OFF;
    reg_wr(REG_ADR_ACK_TIMER_EN, reg_data, 1);


    if(mode == 1) {
        phy_inten(HW_EVENT_TX_FIFO_DONE);
    }else
    if(mode == 2) {
        reg_rd(REG_ADR_PACKET_MODE_SET, reg_data, 1);
        reg_data[0] |= 0x04;    // auto tx on
        reg_wr(REG_ADR_PACKET_MODE_SET, reg_data, 1);

        phy_inten(HW_EVENT_TX_DONE);
    }else
    {
        reg_rd(REG_ADR_PACKET_MODE_SET, reg_data, 1);
        reg_data[0] &= ~0x04;    // auto tx off
        reg_wr(REG_ADR_PACKET_MODE_SET, reg_data, 1);
    }

    // make fcf
    reg_data[0] = 0x18;             // PHR
    reg_data[1] = 2 + length;       // length : crc size + payload length
    reg_wr(REG_ADR_WR_TX_FIFO, reg_data, 2);

    // make payload
    fifo_wr(REG_ADR_WR_TX_FIFO, payload, length);
    if(mode == 2) phy_set_trx_state(PHY_ST_TXON);
#ifndef LAZURITE_IDE
    if(module_test & MODE_PHY_DEBUG){
        printk(KERN_INFO"%s,%s,%lx,%d,SequnceNumber:%d,Mode:%d\n",__FILE__,__func__,(unsigned long)payload,length,payload[2],mode);
     // PAYLOADDUMP(payload,length);
    }
#endif
}


void phy_ccaCtrl(CCA_STATE state) {

    uint8_t reg_cca_cntl;
    uint8_t reg_idl_wait;
    uint8_t reg_data;

     if (state == CCA_FAILURE) {
     // phy_set_trx_state(PHY_ST_FORCE_TRXOFF);
        reg_data = PHY_ST_TRXOFF;
        reg_wr(REG_ADR_RF_STATUS, &reg_data, 1);
     }

    if (state == CCA_FAILURE || state == CCA_IDLE){
        reg_data = 0x64;
        reg_wr(REG_ADR_DEMSET3, &reg_data, 1);
        reg_data = 0x27;
        reg_wr(REG_ADR_DEMSET14, &reg_data, 1);
        reg_cca_cntl = 0x00;
        reg_idl_wait = 0x00;
        reg_wr(REG_ADR_IDLE_WAIT_L, &reg_idl_wait, 1);
        reg_wr(REG_ADR_CCA_CNTRL, &reg_cca_cntl, 1);

        if(state == CCA_IDLE){
            phy_inten(HW_EVENT_TX_DONE);
            phy_set_trx_state(PHY_ST_TXON);
        }
    }else{
        if (state == CCA_FAST) {
            reg_data = 0x00;
            reg_wr(REG_ADR_DEMSET3, &reg_data, 1);
            reg_wr(REG_ADR_DEMSET14,&reg_data, 1);

            reg_cca_cntl = 0x10;
            reg_idl_wait = 0x00;
        } else
        if (state == IDLE_DETECT) {
            reg_cca_cntl = 0x18;
            reg_idl_wait = 250;
        } else
        if (state == CCA_RETRY) {
            phy_backoffTimer();
            reg_cca_cntl = 0x10;
            reg_idl_wait = 250;
        }
        phy_inten(HW_EVENT_CCA_DONE);
        reg_wr(REG_ADR_IDLE_WAIT_L, &reg_idl_wait, 1);
        reg_wr(REG_ADR_CCA_CNTRL, &reg_cca_cntl, 1);
//      phy_set_trx_state(PHY_ST_RXON);
        reg_data = 0x06;
        reg_wr(REG_ADR_RF_STATUS, &reg_data, 1);
    }
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
#if 1   // when it force retrying CCA, is zero.
        if(!count){
           state = IDLE_DETECT;
        }else
#endif
        if(count < retry){
           state = CCA_RETRY;
        }else{
           state = CCA_FAILURE;
        }
    }else{
        state = CCA_IDLE;
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


int phy_rxdone(BUFFER *buff)
{
    int status=STATUS_OK;
    uint16_t data_size=0;
    uint8_t reg_data[2];
    uint8_t rx_done;
	union {
		uint32_t d32;
		uint8_t d8[4];
	} intsrc;

// 2017.10.3
//  phy_set_trx_state(PHY_ST_FORCE_TRXOFF);
    reg_data[0] = 0x03;
    reg_wr(REG_ADR_RF_STATUS, reg_data, 1);

    // Notice: A following must not change.
    reg_rd(REG_ADR_INT_SOURCE_GRP1, reg_data, 1);
	intsrc.d8[0] = reg_data[0];
    reg_rd(REG_ADR_INT_SOURCE_GRP2, reg_data, 1);
	intsrc.d8[1] = reg_data[0];
    reg_rd(REG_ADR_INT_SOURCE_GRP4, reg_data, 1);
	intsrc.d8[3] = reg_data[0];
    reg_rd(REG_ADR_INT_SOURCE_GRP3, reg_data, 1);
	intsrc.d8[2] = reg_data[0];

	/*
    crc_err = reg_data[0]&0x30;
    rx_done = (reg_data[0]&0x0C) << 2;
	*/
    // 2017.10.3
//	rx_done = ((reg_data[0]&0x3C)==0x04) ? true : false;
	if(intsrc.d8[2] == 0x08){
	    rx_done = false;
	}else{
	    if(intsrc.d8[2] == 0x04) {
            rx_done = true;
        }else{
            rx_done = false;
        }
	}

    if (!rx_done) {
    //if (crc_err & rx_done){
		//printk(KERN_INFO"%s %s %d %08lx\n",__FILE__,__func__,__LINE__,intsrc.d32);
        phy_rst();
        status=-EBADE;
    }else{
        // front packet which is not my address is throw.
#if 0        
        if(rx_done&0x20){
            reg_rd(REG_ADR_RD_RX_FIFO, reg_data, 2);
            data_size = (((unsigned int)reg_data[0] << 8) | reg_data[1]) & 0x07ff; 
            buff->len = data_size + 1; // add ED vale
            fifo_rd(REG_ADR_RD_RX_FIFO, buff->data, buff->len);
        }
#endif
        reg_rd(REG_ADR_RD_RX_FIFO, reg_data, 2);
        data_size = (((unsigned int)reg_data[0] << 8) | reg_data[1]) & 0x07ff; 
        buff->len = data_size + 1; // add ED vale
        fifo_rd(REG_ADR_RD_RX_FIFO, buff->data, buff->len);
        // delete crc data
        buff->data[buff->len-3] = buff->data[buff->len-1];
        buff->len -= 2;
        phy_rst();
    }

    // 2017.10.3
//  phy_intclr(HW_EVENT_RX_DONE | HW_EVENT_CRC_ERROR | HW_EVENT_RF_STATUS);
    phy_intclr(HW_EVENT_RX_DONE | HW_EVENT_CRC_ERROR | HW_EVENT_RF_STATUS | HW_EVENT_ADD_FIL_DONE);
//  phy_intclr(~(HW_EVENT_ALL_MASK | HW_EVENT_FIFO_CLEAR));

#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG){
        printk(KERN_INFO"%s,%s,%lx,%d,%d,status=%d,seq=%d\n",__FILE__,__func__,(unsigned long)buff->data,buff->len,data_size,status,buff->data[4]);
     // PAYLOADDUMP(buff->data,buff->len);
    }
#endif
    return status;
}


void phy_stop(void)
{
    phy_set_trx_state(PHY_ST_FORCE_TRXOFF);
    phy_intclr(~(HW_EVENT_ALL_MASK | HW_EVENT_FIFO_CLEAR));
    phy_inten(HW_EVENT_ALL_MASK);
    phy_rst();
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
}


void phy_clrAddrFilt(void)
{
    uint8_t reg_data;
	reg_data = 0x00;
	reg_wr(REG_ADR_ADDFIL_CNTRL, &reg_data, 1);
}


void phy_addrFilt(uint16_t panid, uint8_t *ieee_addr, uint16_t uc_addr, uint16_t bc_addr)
{
    uint8_t reg_data[8];

	reg_data[0] = 0x1E;
	reg_wr(REG_ADR_ADDFIL_CNTRL, reg_data, 1);

	reg_data[0] = panid>>0&0xff;
	reg_data[1] = panid>>8&0xff;
	reg_wr(REG_ADR_PANID_L, reg_data, 2);

    /*
	reg_data[0] = ieee_addr[0];
	reg_data[1] = ieee_addr[1];
	reg_data[2] = ieee_addr[2];
	reg_data[3] = ieee_addr[3];
	reg_data[4] = ieee_addr[4];
	reg_data[5] = ieee_addr[5];
	reg_data[6] = ieee_addr[6];
	reg_data[7] = ieee_addr[7];
	reg_wr(REG_ADR_64ADDR1, reg_data, 8);
    */
	reg_wr(REG_ADR_64ADDR1, ieee_addr, 8);

	reg_data[0] = uc_addr>>0&0xff;
	reg_data[1] = uc_addr>>8&0xff;
	reg_wr(REG_ADR_SHT_ADDR0_L, reg_data, 2);

	reg_data[0] = bc_addr>>0&0xff;
	reg_data[1] = bc_addr>>8&0xff;
	reg_wr(REG_ADR_SHT_ADDR1_L, reg_data, 2);

#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG){

	    printk(KERN_INFO"%s,%s\n",__FILE__,__func__);

        reg_rd(REG_ADR_ADDFIL_CNTRL, reg_data, 1);
        printk(KERN_INFO"ADDFIL_CNTRL: %s,%s,%x\n",__FILE__,__func__,reg_data[0]);

        reg_rd(REG_ADR_PANID_L, reg_data, 2);
        printk(KERN_INFO"PANID_L_L: %s,%s,%x\n",__FILE__,__func__,reg_data[0]);
        printk(KERN_INFO"PANID_L_H: %s,%s,%x\n",__FILE__,__func__,reg_data[1]);

        reg_rd(REG_ADR_SHT_ADDR0_L, reg_data, 2);
        printk(KERN_INFO"ADDR0_L: %s,%s,%x\n",__FILE__,__func__,reg_data[0]);
        printk(KERN_INFO"ADDR0_H: %s,%s,%x\n",__FILE__,__func__,reg_data[1]);

        reg_rd(REG_ADR_SHT_ADDR1_L, reg_data, 2);
        printk(KERN_INFO"ADDR1_L: %s,%s,%x\n",__FILE__,__func__,reg_data[0]);
        printk(KERN_INFO"ADDR1_H: %s,%s,%x\n",__FILE__,__func__,reg_data[1]);
    }
#endif
}


void phy_ed(uint8_t *level, uint8_t rfMode)
{
    if(!rfMode)phy_set_trx_state(PHY_ST_RXON);
    reg_rd(REG_ADR_ED_RSLT, level, 1);
    if(!rfMode)phy_set_trx_state(PHY_ST_FORCE_TRXOFF);
#ifndef LAZURITE_IDE
	if(module_test & MODE_PHY_DEBUG) printk(KERN_INFO"%s,%s,ED_value:%x\n",__FILE__,__func__,*level);
#endif
}


void phy_sleep(void)
{
    uint8_t reg_data;

    phy_set_trx_state(PHY_ST_FORCE_TRXOFF);
	reg_rd(REG_ADR_CLK_SET, &reg_data, 1);
	reg_data |=  0x20;
	reg_wr(REG_ADR_CLK_SET, &reg_data, 1);
    reg_data = 0x00;
	reg_wr(REG_ADR_2DIV_CNTRL, &reg_data, 1);
#ifndef LAZURITE_IDE
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
