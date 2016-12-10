/* mach_lazurite.c - MAC(High level) for lazurite
 *
 * Copyright (c) 2015  Lapis Semiconductor Co.,Ltd
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

#include "errno.h"
#include "endian.h"
#include "common_lazurite.h"
#include "common-lzpi.h"
#include "phy_lazurite.h"

#define BUFFER_SIZE 256
static uint8_t inbuf[256];
static uint8_t outbuf[256];
static PHY_PARAM phy;

PHY_PARAM *phy_init(void)
{

	memset(inbuf,0,sizeof(inbuf));
	memset(outbuf,0,sizeof(inbuf));
	phy.in.size = BUFFER_SIZE;
	phy.in.data = inbuf;
	phy.in.len = 0;
	phy.out.size = BUFFER_SIZE;
	phy.out.len = 0;
	phy.out.data = outbuf;

	return &phy;
}

