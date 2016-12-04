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
#include "string.h"
#else
#include <linux/string.h>
#include <linux/sched.h>
#include <linux/wait.h>
#endif

#define INIT_SLEEP
//#define TEST_SEND_INTERVAL

#include "macl_lazurite.h"
#include "common_lazurite.h"
#include "endian.h"

/*
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
*/
// @issue check parameter. interval may not be needed.
typedef struct {
	uint8_t ch;
	uint8_t pages;
	uint8_t cca_min_be;
	uint8_t cca_max_be;
	uint8_t cca_level;
	uint8_t cca_duration;
	uint8_t cca_retry;
	uint8_t tx_min_be;
	uint8_t tx_max_be;
	uint8_t tx_retry;
	uint32_t cca_interval;
	uint32_t tx_power;
	uint32_t tx_interval;
	enum nl802154_cca_modes cca_mode;
	enum nl802154_cca_opts cca_opt;
} RF_PARAM;

typedef struct {
	struct {
		bool enb;
		uint16_t data;
	} panid;
	uint8_t addr_mode;
	union {
		uint16_t short_addr;
		uint16_t ldd_addr;
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
#ifdef LITTLE_ENDIAN
typedef struct {
	uint8_t frame_type:3;
	uint8_t sec_enb:1;
	uint8_t pending:1;
	uint8_t ack_req:1;
	uint8_t panid_comp:1;
	uint8_t nop:1;
	uint8_t seq_comp:1;
	uint8_t ielist:1;
	uint8_t dst_addr_type:2;
	uint8_t frame_ver:2;
	uint8_t src_addr_type:2;
} s_MAC_HEADER_BIT_ALIGNMENT;
#endif

typedef union {
	uint8_t fc8[2];
	uint16_t fc16;
	s_MAC_HEADER_BIT_ALIGNMENT fc_bit;
} u_MAC_HEADER;

typedef struct {
	int16_t seq;        	// sequence number
	u_MAC_HEADER fc;		// frame control
	MACH_HEADER_ADDR dst;
	MACH_HEADER_ADDR src;
	uint8_t addr_type;      // address type
	BUFFER payload;		// source address
	BUFFER raw;		// source address
	uint8_t rssi;		// source address
} MACH_Header;

typedef struct {
	MACL_PARAM *macl;
	MACH_ADDR  myAddr;
	MACH_Header tx;
	MACH_Header rx;
	MACH_Header ack;
	bool promiscuous;
	RF_PARAM rf;
} MACH_PARAM;

extern MACH_PARAM *mach_init(void);
extern int mach_sleep(bool on);
extern int mach_set_rf_param(RF_PARAM *rf);
extern int mach_set_my_short_addr(uint16_t panid,uint16_t short_addr);
extern void mach_set_dst_short_addr(uint16_t panid,uint16_t short_addr);
extern int mach_tx(BUFFER *txbuf);
extern int mach_start(BUFFER *rxbuf);
extern int mach_stop(void);
extern int mach_parse_data(uint8_t *data, uint16_t size, MACH_Header *header);
extern int mach_ed(uint8_t *ed);
extern int mach_rx_isr(MACH_Header *rx,int status);
#endif
