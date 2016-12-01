/* mac_lazurite.h - 
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

#ifndef _MAC_LAZURITE_H_
#define _MAC_LAZURITE_H_
#include "phy_lazurite.h"

typedef struct {
	bool panid_comp;
	uint16_t pan_id;
	bool addr_mode;
	union {
		uint16_t short_addr;
		uint8_t ieee_addr[8];
	}addr;
} MACH_HEADER_ADDR;
//
typedef struct
{
	uint16_t	pan_id;					// for lazurite
	uint16_t	short_addr;				// for lazurite
	uint8_t		ieee_addr[8];			// for lazurite
	bool		pan_coord;				// common
} MACH_ADDR;


typedef struct {
    int16_t seq;        	// sequence number
    uint16_t fc;        	// framce control
    uint8_t type;      // address type
	BUFFER buf;		// source address
	uint8_t rssi;		// source address
	MACH_HEADER_ADDR dst;
	MACH_HEADER_ADDR src;
} MACH_Header;

typedef struct {
	PHY_PARAM *phy;
	MACH_ADDR  myAddr;
	MACH_Header tx;
	MACH_Header rx;
	MACH_Header ack;
	bool promiscuous;
	uint8_t tx_retry;
	uint16_t tx_interval;
} MACH_PARAM;

extern MACH_PARAM *mac_init(void);
extern int mach_sleep(bool on);
#endif
