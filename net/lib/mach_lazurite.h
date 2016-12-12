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

// @issue check parameter. interval may not be needed.

struct mac_addr {
	struct {
		bool enb;
		uint16_t data;
	} panid;
	uint8_t addr_type;
	union {
		uint16_t short_addr;
		uint16_t ldd_addr;
		uint8_t ieee_addr[8];
	}addr;
};
//

#define IEEE802154_FC_TYPE_BEACON	0
#define IEEE802154_FC_TYPE_DATA		1
#define IEEE802154_FC_TYPE_ACK		2
#define IEEE802154_FC_TYPE_CMD		3
#define IEEE802154_FC_VER_2003		0
#define IEEE802154_FC_VER_2006		1
#define IEEE802154_FC_VER_4E		2
#define IEEE802154_FC_ADDR_NONE		0
#define IEEE802154_FC_ADDR_LDD		1
#define IEEE802154_FC_ADDR_SHORT	2
#define IEEE802154_FC_ADDR_IEEE		3

/*! @struct mac_fc_alignment
  @brief  abstruct
  internal use only
  bit alightment of mac header
  */
#ifdef LITTLE_ENDIAN
struct mac_fc_alignment{
	uint8_t frame_type:3;
	uint8_t sec_enb:1;
	uint8_t pending:1;
	uint8_t ack_req:1;
	uint8_t panid_comp:1;
	uint8_t nop:1;
	uint8_t seq_comp:1;
	uint8_t ielist:1;
	uint8_t src_addr_type:2;
	uint8_t frame_ver:2;
	uint8_t dst_addr_type:2;
};
#endif

union mac_frame_control {
	uint8_t fc8[2];
	uint16_t fc16;
	struct mac_fc_alignment fc_bit;
};

struct mac_header{
	int16_t seq;        	// sequence number
	union mac_frame_control fc;		// frame control
	struct mac_addr dst;
	struct mac_addr src;
	uint8_t addr_type;      // address type
	BUFFER payload;		// source address
	BUFFER raw;		// source address
	BUFFER input;		// source address
	uint8_t rssi;		// source address
};

struct rf_param {
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
};

struct mach_param {
	MACL_PARAM *macl;
	struct {
		uint16_t	pan_id;					// for lazurite
		uint8_t		ldd_addr;				// for lazurite
		uint16_t	short_addr;				// for lazurite
		uint8_t		ieee_addr[8];			// for lazurite
		bool		pan_coord;				// common
	} my_addr;
	struct mac_header tx;
	struct mac_header rx;
	struct mac_header ack;
	bool promiscuous;
	struct rf_param *rf;
};

extern struct mach_param *mach_init(void);
extern int mach_sleep(bool on);
extern int mach_setup(struct rf_param *rf);
extern int mach_set_my_short_addr(uint16_t panid,uint16_t short_addr);
extern int mach_set_dst_ieee_addr(uint8_t *addr);
extern int mach_set_dst_short_addr(uint16_t panid,uint16_t short_addr);
extern int mach_set_src_addr(uint8_t addr_mode);
extern int mach_tx(struct mac_fc_alignment,uint8_t addr_type,BUFFER *txbuf);
extern int mach_start(BUFFER *rxbuf);
extern int mach_stop(void);
extern int mach_parse_data(struct mac_header *header);
extern int mach_ed(uint8_t *ed);
extern int mach_rx_irq(BUFFER* rx);
#endif
