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
	SUBGHZ_ST_DUMMY							// 25
} SUBGHZ_MAC_STATE;


struct macl_param {
	uint8_t pages;
	uint8_t ch;
	uint8_t ccaMode;
	uint8_t ccaMinBe;
	uint8_t ccaMaxBe;
	uint8_t ccaCount;
	uint8_t ccaRetries;
	uint8_t txPower;
	uint8_t txRetries;
	uint8_t sequenceNum;
	uint8_t resendingNum;
	uint8_t rxOnEnable;
	bool promiscuousMode;
	uint16_t ack_timeout;
	int status;
	int condition;
	volatile int  done;
	uint16_t tx_ack_interval;
	void (*tx_callback)(uint8_t rssi, int status);
	uint32_t total_send_bytes;
	uint32_t start_send_time;
	uint32_t last_send_time;
	struct phy_param *phy;
	wait_queue_head_t que;
	//BUFFER ack;
};

struct ieee802154_my_addr {
	uint16_t	pan_id;					// for lazurite
	uint16_t	short_addr;				// for lazurite
	uint8_t		ieee_addr[8];			// for lazurite
	bool		pan_coord;				// common
};
extern struct macl_param *macl_init(void);	
extern int	macl_start(void);
extern int	macl_stop(void);
extern int	macl_xmit_sync(BUFFER buff);
extern int	macl_xmit_async(BUFFER buff,void (*callback)(uint8_t rssi, int status));
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

extern int	macl_set_modulation(int8_t mod, int8_t sf, int8_t size);
extern int	macl_get_modulation(int8_t *mod, int8_t *sf, int8_t *size);
#endif

