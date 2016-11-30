
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
	struct {
		uint8_t enb;
		uint16_t data;
	} panid;
	struct {
		uint8_t mode;
		uint16_t addr16;
		uint8_t addr64[8];
	}addr;
} MAC_ADDR;

typedef struct {
	uint8_t *data;
	uint16_t len;
	int size;			// size < 0 : size unknown
} BUFFER;

typedef struct {
    int16_t seq;        	// sequence number
    uint16_t fc;        	// framce control
    uint8_t type;      // address type
	BUFFER buf;		// source address
	uint8_t rssi;		// source address
} MAC_Header;

typedef struct {
	PHY_PARAM *phy;
	MAC_ADDR  myAddr;
	MAC_Header tx;
	MAC_Header rx;
	MAC_Header ack;
	uint8_t tx_retry;
	uint16_t tx_interval;
} MAC_PARAM;

extern MAC_PARAM *mac_init(void);
extern int mac_sleep(bool on);
#endif
