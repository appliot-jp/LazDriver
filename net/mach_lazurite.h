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

#define INIT_SLEEP
//#define TEST_SEND_INTERVAL

#include "phy_lazurite.h"
#include "common_lazurite.h"

#define MACH_FC_TYPE			0x0007
#define MACH_FC_SEC_ENB			0x0008
#define MACH_FC_PENDING			0x0010
#define MACH_FC_ACK_REG			0x0020
#define MACH_FC_PANID_COMP		0x0040
#define MACH_FC_SEQ_COMP		0x0100
#define MACH_FC_IE_LIST			0x0200
#define MACH_FC_SRC_ADDR		0x0C00
#define MACH_FC_VER				0x3000
#define MACH_FC_DST_ADDR		0xC000

typedef struct {
	struct {
		bool isValid;
		uint16_t data;
	} panid;
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

/*! @struct s_MAC_HEADER_BIT_ALIGNMENT
  @brief  abstruct
  internal use only
  bit alightment of mac header
  */
typedef struct {
	uint8_t frame_type:3;
	uint8_t sec_enb:1;
	uint8_t pending:1;
	uint8_t ack_req:1;
	uint8_t panid_comp:1;
	uint8_t nop:1;
	uint8_t seq_comp:1;
	uint8_t ielist:1;
	uint8_t rx_addr_type:2;
	uint8_t frame_ver:2;
	uint8_t tx_addr_type:2;
} s_MAC_HEADER_BIT_ALIGNMENT;

typedef union {
	uint8_t fc8[2];
	uint16_t fc16;
	s_MAC_HEADER_BIT_ALIGNMENT fc_bit;
} u_MAC_HEADER;

typedef struct {
	int16_t seq;        	// sequence number
	u_MAC_HEADER fc;		// frame control
	uint8_t addr_type;      // address type
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
