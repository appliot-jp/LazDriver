/* phy_lazurite.h - 
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
#include "lazurite.h"
#include "hal.h"
#include "string.h"
#include "lp_manage.h"
#include "driver_irq.h"
#else
#include <linux/string.h>
#include <linux/sched.h>
#include <linux/wait.h>
#endif
#include "common_lazurite.h"

#define INIT_SLEEP
//#define TEST_SEND_INTERVAL


typedef struct {
	uint8_t id;
	uint16_t buf_size;
	BUFFER in;
	BUFFER out;
} PHY_PARAM;


typedef enum {
	CCA_IDLE=0,
	CCA_BUSY,
	CCA_TIMEOUT
}CCA_RESULT;


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
extern int phy_setup(uint8_t page,uint8_t ch);
extern PHY_PARAM *phy_init(void);
extern void phy_rst(void);
extern void phy_trxoff(void);
extern void phy_addr_filt(void);
extern int phy_ed(void);
extern void phy_sleep(void);
/*
 ------------------------------------------------------------------
                      Public state machine section
 ------------------------------------------------------------------
 */
extern void phy_stm_promiscuous(void);
extern void phy_stm_receive(void);
extern void phy_stm_send(BUFFER buff);
extern void phy_stm_fifodone(void);
extern int phy_stm_ccadone(void);
extern void phy_stm_txdone(void);
extern void phy_stm_rxdone(void);
extern void phy_stm_retry(void);



#endif
