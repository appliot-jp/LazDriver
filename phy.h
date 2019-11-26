/* phy.h - 
 *
 * Copyright (c) 2015  LAPIS Semiconductor Co.,Ltd.
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
 * <http://www.gnu.org/licenses/>.
 */


 #ifndef _PHY_H_
 #define _PHY_H_


#if defined LAZURITE_IDE
	#include <common.h>
#elif defined ARDUINO
#include "arduino.h"
#else
	#include <linux/string.h>
	#include <linux/sched.h>
	#include <linux/wait.h>
#endif

#include "common_subghz.h"

typedef struct {
	uint8_t id;
	uint16_t buf_size;
	BUFFER in;
	BUFFER out;
} PHY_PARAM;

typedef enum {
	CCA_IDLE,                   /* CCA pass */
	CCA_FAST,                   /* CCA minmum */
	IDLE_DETECT,                /* CCA Idle detection */
	CCA_RETRY,                  /* CCA with BACKOFF */
	CCA_FAILURE                /* CCA failure */
} CCA_STATE;

#ifdef MK74040
typedef enum {
	FIFO_NORMAL,                /* Normal access */
	FIFO_DONE,                  /* INT FIFO DONE */
	FIFO_AUTO_TX                /* AUTO TX */
} FIFO_ACCESS;


#define PHY_MODULATION_FSK		( 0x00 )
#define PHY_MODULATION_DSSS		( 0x10 )
#define PHY_MODULATION_SIGFOX	( 0x20 )

#define PHY_CHSPACE_12_5K		( 0x00 )
#define PHY_CHSPACE_25K			( 0x01 )
#define PHY_CHSPACE_100K		( 0x02 )
#define PHY_CHSPACE_150K		( 0x03 )
#define PHY_CHSPACE_200K		( 0x04 )
#define PHY_CHSPACE_400K		( 0x05 )
#define PHY_CHSPACE_5K		    ( 0x06 )

#define PHY_PA_MODE_NORMAL      ( 0x00 )
#define PHY_PA_MODE_EXTERNAL    ( 0x01 )


#define PHY_DATARATE_50K		( 0x01 )
#define PHY_DATARATE_100K		( 0x02 )
#define PHY_DATARATE_80K		( 0x04 )
#define PHY_DATARATE_200K		( 0x08 )
#endif
/*
 -------------------------------------------------------------
                    Public interrupt section
 -------------------------------------------------------------
 */
extern int phy_sint_handler(void (*func)(void));
extern int phy_sint_ei(void);
extern int phy_sint_di(void);
extern int phy_timer_handler(void (*func)(void));
extern int phy_timer_ei(void);
extern int phy_timer_di(void);
extern int phy_timer_start(uint16_t msec);
extern int phy_timer_stop(void);
extern int phy_timer_tick(uint32_t *msec);
/*
 -------------------------------------------------------------
                    Public function section
 -------------------------------------------------------------
 */
extern void phy_wait_phy_event(void);
extern int phy_wait_mac_event(void);
extern void phy_wakeup_phy_event(void);
extern void phy_wakeup_mac_event(void);

extern PHY_PARAM *phy_init(void);
extern int phy_setup(uint8_t page,uint8_t ch,uint8_t txPower,uint8_t antsw);

// extern void phy_promiscuous(void);
extern void phy_rxStart(void);
#ifdef MK74040
//extern int phy_setup(uint8_t page,uint8_t ch);
extern void phy_config(uint8_t mod, uint8_t sf, uint16_t size);
extern bool phy_txfifo(BUFFER *buff);
extern void phy_regdump(void);
extern bool phy_txStart(BUFFER *buff,uint8_t mode);
extern void phy_ccaCtrl(CCA_STATE state);
#else
extern void phy_txStart(BUFFER *buff,uint8_t mode);
extern int phy_ccaCtrl(CCA_STATE state);
#endif
extern CCA_STATE phy_ccadone(uint8_t be,uint8_t count, uint8_t retry);
extern void phy_txdone(void);
extern int phy_rxdone(BUFFER *buff);
extern void phy_stop(void);
extern void phy_clrAddrFilt(void);
extern void phy_addrFilt(uint16_t panid, uint8_t *ieee_addr, uint16_t uc_addr, uint16_t bc_addr);
extern void phy_ed(uint8_t *level, uint8_t rfMode);
extern void phy_sleep(void);
extern void phy_cleanup(void);
extern void phy_monitor(void);
// following function is for debug. and test.bin use it.
extern void phy_regread(uint8_t bank, uint8_t addr, uint8_t *data, uint8_t size);
extern void phy_regwrite(uint8_t bank, uint8_t addr, uint8_t *data, uint8_t size);
#endif

