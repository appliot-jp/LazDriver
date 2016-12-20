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


#define PHY_ST_FORCE_TRXOFF      0x03
#define PHY_ST_RXON              0x06
#define PHY_ST_TXON              0x09
#define PHY_ST_TRXOFF            0x08


extern int phy_sint_handler(void (*func)(void));
extern int phy_sint_ei(void);
extern int phy_sint_di(void);
extern int phy_timer_handler(void (*func)(void));
extern int phy_timer_ei(void);
extern int phy_timer_di(void);
extern int phy_timer_start(uint16_t msec);
extern int phy_timer_stop(void);
extern int phy_timer_tick(uint32_t *msec);
extern int phy_regset(void *data);
extern PHY_PARAM *phy_init(void);
extern void phy_set_trx(uint8_t state);
extern int phy_get_trx(void);
extern int phy_set_cca(void);
extern int phy_get_ed(void);
extern void phy_intsrc(uint32_t intsrc);
extern void phy_inten(uint32_t inten);
extern void phy_intclr(uint32_t intclr);



#endif
