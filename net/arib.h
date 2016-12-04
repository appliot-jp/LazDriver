/* arib_lazurite.h - 
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

#ifndef _ARIB_LAZURITE_H_
#define _ARIB_LAZURITE_H_

#ifdef LAZURITE_IDE
#include "lazurite.h"
#include "string.h"
#else
#include <linux/string.h>
#include <linux/sched.h>
#include <linux/wait.h>
#endif


extern void arib_init(void);
extern void arib_tx_end(uint8_t pages, uint16_t size);
extern bool arib_tx_check(uint8_t pages, uint16_t size);
#endif
