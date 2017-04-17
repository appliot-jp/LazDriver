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


 #ifdef LAZURITE_IDE
 	#include <common.h>
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
extern void phy_wait_mac_event(void);
extern void phy_wakeup_phy_event(void);
extern void phy_wakeup_mac_event(void);

extern PHY_PARAM *phy_init(void);
extern int phy_setup(uint8_t page,uint8_t ch);

// extern void phy_promiscuous(void);
extern void phy_rxStart(void);
extern void phy_txStart(BUFFER *buff,uint8_t mode);
extern void phy_ccaCtrl(CCA_STATE state);
extern CCA_STATE phy_ccadone(uint8_t be,uint8_t count, uint8_t retry);
extern void phy_txdone(void);
extern int phy_rxdone(BUFFER *buff);
extern void phy_stop(void);
extern void phy_addrFilt(uint16_t panid, uint8_t *ieee_addr, uint16_t uc_addr, uint16_t bc_addr);
extern void phy_ed(uint8_t *level, uint8_t rfMode);
extern void phy_sleep(void);
extern void phy_regread(uint8_t bank, uint8_t addr, uint8_t *data, uint8_t size);
extern void phy_regwrite(uint8_t bank, uint8_t addr, uint8_t *data, uint8_t size);

#endif

