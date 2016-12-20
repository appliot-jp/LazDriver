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

#define BUFFER_SIZE 256
static struct {
    volatile uint8_t lock;  // exclusion lock counter  
    uint8_t bank;           // back number
    uint8_t rdata[256];     // input buffer 
    uint8_t wdata[256];     // outpu buffer
}reg = {
    0,    /* lock */
    0xff  /* bank */
};


static PHY_PARAM phy;

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
