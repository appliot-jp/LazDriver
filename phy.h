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

#include "errno.h"
#include "common_subghz.h"
#include "hwif/hal.h"

struct phy_param {
	uint8_t id;
	uint16_t unit_backoff_period;
	BUFFER in;
	BUFFER out;
	uint16_t in_ptr;
	uint16_t out_ptr;
};

typedef enum {
	MANUAL_TX = 0,
	AUTO_TX
} TX_MODE;

typedef enum {
	FIFO_DONE = 0,
	FIFO_CONT,
	CRC_ERROR
} FIFO_STATE;

#define PHY_MODULATION_FSK		( 0x00 )
#define PHY_MODULATION_DSSS		( 0x10 )
#define PHY_MODULATION_SIGFOX	( 0x20 )

#define PHY_CHSPACE_12_5K		( 0x00 )
#define PHY_CHSPACE_25K			( 0x01 )
#define PHY_CHSPACE_100K		( 0x02 )
#define PHY_CHSPACE_150K		( 0x03 )
#define PHY_CHSPACE_200K		( 0x04 )
#define PHY_CHSPACE_400K		( 0x05 )
#define PHY_CHSPACE_5K		  ( 0x06 )

#define PHY_PA_MODE_NORMAL      ( 0x00 )
#define PHY_PA_MODE_EXTERNAL    ( 0x01 )


#define PHY_DATARATE_50K		( 0x01 )
#define PHY_DATARATE_100K		( 0x02 )
#define PHY_DATARATE_80K		( 0x04 )
#define PHY_DATARATE_200K		( 0x08 )

/*
 -------------------------------------------------------------
                    Public interrupt section
 -------------------------------------------------------------
 */
extern int phy_sint_handler(void (*func)(void));
extern int phy_timer_start(uint16_t msec,void (*func)(void));
extern int phy_timer_stop(void);
/*
 -------------------------------------------------------------
                    Public function section
 -------------------------------------------------------------
 */

extern struct phy_param *phy_init(void);
extern int phy_setup(uint8_t page,uint8_t ch,uint8_t txPower,uint8_t antsw);

extern int phy_setModulation(int8_t mod, int8_t sf);
extern int phy_getModulation(int8_t *mod, int8_t *sf);

extern int phy_txpre(TX_MODE mode);
extern int phy_ccaCtrl(uint32_t us);
extern uint8_t phy_ccadone(void);
extern int phy_txstart(void);
extern FIFO_STATE phy_txfifo(void);
extern void phy_txdone(void);

extern void phy_rxstart(void);
extern FIFO_STATE phy_rxdone(void);
extern void phy_stop(void);
extern void phy_clrAddrFilt(void);
extern void phy_addrFilt(uint16_t panid, uint8_t *ieee_addr, uint16_t uc_addr, uint16_t bc_addr);
extern void phy_set_monitor(bool on);
extern uint8_t phy_ed(void);
extern void phy_sleep(void);

// following function is for debug. and test.bin use it.
extern void phy_monitor(void);
extern void phy_regread(uint8_t bank, uint8_t addr, uint8_t *data, uint8_t size);
extern void phy_regwrite(uint8_t bank, uint8_t addr, uint8_t *data, uint8_t size);
extern void phy_regdump(void);
#endif

