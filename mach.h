/* mac.h - 
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

#ifndef _MACH_H_
#define _MACH_H_

#if defined LAZURITE_IDE
	#include <common.h>
#elif	defined ARDUINO
	#include <arduino.h>
#else
	#include <linux/string.h>
	#include <linux/sched.h>
	#include <linux/wait.h>
#endif

#include "macl.h"
#include "endian.h"

struct fc_addr {
	struct {
		bool enb;
		uint16_t data;
	} panid;
	uint8_t addr_type;
	union {
		uint8_t lddn_addr;
		uint16_t short_addr;
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
	@brief	abstruct
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
	uint8_t dst_addr_type:2;
	uint8_t frame_ver:2;
	uint8_t src_addr_type:2;
};
#endif

union mac_frame_control {
	uint8_t fc8[2];
	uint16_t fc16;
	struct mac_fc_alignment fc_bit;
};

struct mac_header{
	union mac_frame_control fc;		// frame control
	struct fc_addr dst;
	struct fc_addr src;
	uint8_t seq;					// sequence number
	uint8_t addr_type;			// address type
	uint8_t rssi;		// source address
	BUFFER payload;		// source address
	BUFFER raw;		// source address
	BUFFER input;		// source address
	int payload_offset;
};

struct rf_param {
	uint8_t ch;
	uint8_t pages;
	uint8_t cca_min_be;
	uint8_t cca_max_be;
	uint8_t cca_retry;
	uint8_t tx_min_be;
	uint8_t tx_max_be;
	uint8_t tx_retry;
	uint8_t ant_sw;
	int8_t modulation;
	int8_t dsssSF;
	int8_t dsssSize;
	uint16_t ack_timeout;
	int32_t cca_level;		//mbm
	int32_t tx_power;
};

struct mac_addr {
	bool		pan_coord;				// common
	uint8_t		lddn_addr;				// for lazurite
	uint16_t	pan_id;					// for lazurite
	uint16_t	short_addr;				// for lazurite
	uint8_t		ieee_addr[8];			// for lazurite
};
struct mach_param {
	struct macl_param *macl;
	struct mac_addr my_addr;
	struct mac_addr coord_addr;
	struct mac_header tx;
	struct mac_header rx;
	struct mac_header rx_prev;
	struct mac_header ack;
	bool coordinator;
	bool sending;
	struct rf_param *rf;
};

extern struct mach_param *mach_init(void);
extern int mach_sleep(void);
extern int mach_setup(struct rf_param *rf);
extern int mach_set_my_short_addr(uint16_t panid,uint16_t short_addr);
extern int mach_set_dst_ieee_addr(uint16_t panid,uint8_t *addr);
extern int mach_set_dst_short_addr(uint16_t panid,uint16_t short_addr);
extern int mach_set_src_addr(uint8_t addr_mode);
extern int mach_tx(struct mac_fc_alignment fc,uint8_t addr_type,BUFFER *txbuf);
extern int mach_start(BUFFER *rxbuf);
extern int mach_stop(void);
extern int mach_parse_data(struct mac_header *header);
extern int mach_ed(uint8_t *ed);
extern int mach_rx_irq(int status, struct mac_header *rx);
extern int mach_set_promiscuous(bool on);
extern void mach_get_enhance_ack(uint8_t **data, int *size);
extern bool mach_set_enhance_ack(uint8_t *data, int size);
extern void mach_set_ack_tx_interval(uint16_t interval);

#endif

