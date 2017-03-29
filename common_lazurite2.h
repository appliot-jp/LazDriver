/* common_lazurite.h - 
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

#ifndef _COMMON_LAZURITE_H_
#define _COMMON_LAZURITE_H_

#ifdef LAZURITE_IDE
#include "lazurite.h"
//#include "hwif/hal.h"
//#include "string.h"
//#include "driver_irq.h"
#else
#include <linux/string.h>
//#include <linux/sched.h>
//#include <linux/wait.h>
#endif

/*! @brief buffer definision for subghz common 
 @struct BUFFER
	@uint8_t *data	starting pointer of data buffer
	@uint16_t len	length of data
	@int16_t size	buffer size
 */
typedef struct {
	uint8_t *data;
	uint16_t len;
	int size;			// size <= 0 : size unknown
} BUFFER;

#define DBM_TO_MBM(gain)	(gain*100)
#define MBM_TO_DBM(gain)	(gain/100)

#define BIT(n)				(0x01<<n)

#endif
