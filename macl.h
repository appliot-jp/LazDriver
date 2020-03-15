/* macl.h - 
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

#ifndef _MACL_H_
#define _MACL_H_

#ifdef LAZURITE_IDE
	//#include <common.h>
	//#include <hwif/hal.h>
#endif

#include "common_subghz.h"
#include "phy.h"

#ifdef JP
	#define PREAMBLE_OFFSET	4
	#define SFD_OFFSET			2
	#define CRC_OFFSET			2
	#define TX_TTL_OFFSET (PREAMBLE_OFFSET + SFD_OFFSET + CRC_OFFSET)
#endif

#define SUBGHZ_HOPPING				( 0xF0 )
#define SUBGHZ_HOPPING_TS_H		( SUBGHZ_HOPPING + 0 )
#define SUBGHZ_HOPPING_TS_S		( SUBGHZ_HOPPING + 1 )
#define SUBGHZ_HOPPING_PB_H		( SUBGHZ_HOPPING + 2 )
#define SUBGHZ_HOPPING_PB_S		( SUBGHZ_HOPPING + 3 )

#define SUBGHZ_HOPPING_SEARCH_CYCLE				2
#define SUBGHZ_HOPPING_SEARCH_INTERVAL		200L
#define SUBGHZ_HOPPING_CH_DURATION				1000L

#define SUBGHZ_HOPPING_SYNC_FRAME_SIZE 16

typedef enum {
	SUBGHZ_ST_INIT = 0,
	SUBGHZ_ST_INIT_FAIL,				// 1
	SUBGHZ_ST_SLEEP,						// 2
	SUBGHZ_ST_SLEEPED,					// 3
	SUBGHZ_ST_SETUP,						// 4
	SUBGHZ_ST_STANDBY,					// 5
	SUBGHZ_ST_STOP,							// 6
	SUBGHZ_ST_TX_START,					// 7
	SUBGHZ_ST_CCA,							// 8
	SUBGHZ_ST_CCA_ABORT,				// 9
	SUBGHZ_ST_CCA_DONE,					// 10
	SUBGHZ_ST_CCA_FAIL,					// 11
	SUBGHZ_ST_TX_FIFO,					// 12
	SUBGHZ_ST_TX_DONE,					// 13
	SUBGHZ_ST_TX_ABORT,					// 14
	SUBGHZ_ST_ACK_RX_DONE,			// 15
	SUBGHZ_ST_ACK_RX_ABORT,			// 16
	SUBGHZ_ST_ACK_RX_CRC,				// 17
	SUBGHZ_ST_RX_START,					// 18
	SUBGHZ_ST_RX_STARTED,				// 19
	SUBGHZ_ST_RX_DONE,					// 20
	SUBGHZ_ST_RX_FIFO,					// 21
	SUBGHZ_ST_ACK_TX,						// 22
	SUBGHZ_ST_ACK_TX_ABORT,			// 23
	SUBGHZ_ST_ACK_TX_DONE,			// 24
	SUBGHZ_ST_DUMMY							// 28
} SUBGHZ_MAC_STATE;

typedef enum {
	SUBGHZ_ST_HOPPING_NOP,				//0
	SUBGHZ_ST_HOPPING_HOST_CMD_TX,				//1
	SUBGHZ_ST_HOPPING_SLAVE_CMD_RX	//2
} SUBGHZ_HOPPING_STATE;
#ifdef LAZURITE_IDE
typedef __packed struct {
	uint16_t mac_header;
	uint8_t  seq;
	uint16_t panid;
	uint16_t dst;
	uint8_t src[8];
	struct {
		uint8_t cmd;
		uint8_t id[4];
	} payload;
} macl_timesync_search_request_cmd;

typedef __packed struct  {
	uint16_t mac_header;
	uint8_t  seq;
	uint16_t panid;
	uint8_t dst[8];
	uint8_t src[8];
	struct {
		uint8_t cmd;
		uint8_t index;
		uint8_t size;
		uint8_t reserve;
		uint32_t sync_interval;
		uint32_t sync_from;
		uint32_t base;
		uint8_t ch_list [32];
	} payload;
} macl_timesync_params_cmd;

#else
typedef struct {
	uint16_t mac_header;
	uint8_t  seq;
	uint16_t panid;
	uint16_t dst;
	uint8_t src[8];
	struct {
		uint8_t cmd;
		uint8_t id[4];
	} payload;
} __attribute__((packed)) macl_timesync_search_request_cmd;

typedef struct  {
	uint16_t mac_header;
	uint8_t  seq;
	uint16_t panid;
	uint8_t dst[8];
	uint8_t src[8];
	struct {
		uint8_t cmd;
		uint8_t index;
		uint8_t size;
		uint8_t reserve;
		uint32_t sync_interval;
		uint32_t sync_from;
		uint32_t base;
		uint8_t ch_list [32];
	} payload;
} __attribute__((packed)) macl_timesync_params_cmd;
#endif
struct macl_param {
	struct mach_param* parent;
	uint8_t pages;
	uint8_t ch;
	uint8_t txPower;
	uint8_t antsw;
	uint8_t ccaMode;
	uint8_t ccaMinBe;
	uint8_t ccaMaxBe;
	uint8_t ccaCount;
	uint8_t ccaRetries;
	uint8_t txRetries;
	uint8_t sequenceNum;
	uint8_t resendingNum;
	uint16_t ack_timeout;
	int status;
	uint8_t condition;
	uint8_t hopping_state;
	volatile int  txdone;
	volatile int  hoppingdone;
	volatile int  rxdone;
	uint16_t tx_ack_interval;
	void (*tx_callback)(uint8_t rssi, int status);
	uint32_t total_send_bytes;
	uint32_t start_send_time;
	uint32_t last_send_time;
	struct phy_param *phy;
	wait_queue_head_t que;
	struct {
		uint8_t hopping_sync_host_irq:1;
		uint8_t hopping_sync_slave_irq:1;
		uint8_t hopping:1;
		uint8_t sync_enb:1;
		uint8_t rxOnEnable:1;
		uint8_t promiscuousMode:1;
	} bit_params;
	BUFFER cmd;
	union {
		struct {
			uint8_t ch_scan_cycle;					// hopping mode only. cycle time of scan
			uint8_t ch_scan_count;					// hopping mode only. cycle time of scan
			uint16_t backoff_unit;					// hopping mode only. cycle time of scan
			uint32_t backoff_time;					// hopping mode only. cycle time of scan
		} slave;
		struct { 
			uint8_t ch_index;						// hopping mode only. ch index.
			uint32_t sync_time;							// hopping mode only. sync time(millis)
			uint32_t ch_duration;		// hopping mode only. sync time(millis)
		} host;
	} hopping;
};

struct ieee802154_my_addr {
	uint16_t	pan_id;					// for lazurite
	uint16_t	short_addr;				// for lazurite
	uint8_t		ieee_addr[8];			// for lazurite
	bool		pan_coord;				// common
};

extern int	macl_start(void);
extern struct macl_param *macl_init(void *parent);
extern int	macl_stop(void);
extern int	macl_xmit_sync(BUFFER *buff);
extern int	macl_xmit_async(BUFFER *buff,void (*callback)(uint8_t rssi, int status));
extern int	macl_set_channel(uint8_t page,uint8_t ch,uint32_t mbm,uint8_t antsw);
extern int	macl_set_hw_addr_filt(struct ieee802154_my_addr *filt,uint32_t changed);
extern int	macl_set_cca_ed_level(uint32_t mbm);
extern int	macl_set_csma_params(uint8_t min_be, uint8_t max_be, uint8_t retries);
extern int	macl_set_frame_retries(uint8_t retries,uint32_t timeout);
extern int	macl_set_promiscuous_mode(bool on);

extern int	macl_rx_irq(bool *isAck);
extern int	macl_rx_irq_notification(void);

extern int	macl_sleep(void);
extern void	macl_set_ack_tx_interval(uint16_t interval);

extern int	macl_set_modulation(int8_t mod, int8_t sf);
extern int	macl_get_modulation(int8_t *mod, int8_t *sf);
extern void macl_set_antsw(uint8_t antsw);
extern void macl_hopping_cmd_rx(void *buff);
#endif

