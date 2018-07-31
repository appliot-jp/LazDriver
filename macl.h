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

#ifdef LAZURIE_IDE
	#include <common.h>
#endif

#include "common_subghz.h"
#include "phy.h"

typedef enum {
    SUBGHZ_ST_TX_START = 0,
    SUBGHZ_ST_CCA_FAST,             // 1
    SUBGHZ_ST_CCA_IDLE_DETECT,      // 2
    SUBGHZ_ST_CCA_ABORT,            // 3
    SUBGHZ_ST_CCA_RETRY,            // 4
    SUBGHZ_ST_CCA_FAILURE,          // 5
    SUBGHZ_ST_CCA_DONE,             // 6
    SUBGHZ_ST_TX_DONE,              // 7
    SUBGHZ_ST_TX_ACK_TIMEOUT,       // 8
    SUBGHZ_ST_TX_ACK_DONE,          // 9
    SUBGHZ_ST_RX_START,             // 10
    SUBGHZ_ST_RX_DONE,              // 11
    SUBGHZ_ST_RX_ACK_DONE,          // 12
    SUBGHZ_ST_NONE                  // --
} SUBGHZ_MAC_STATE;


typedef struct {
	uint8_t condition;
	uint8_t pages;
	uint8_t ch;
	uint8_t ccaRetry;
	uint8_t ccaBe;
    uint8_t ccaCount;
	uint8_t txPower;
	uint8_t txRetry;
	uint8_t txMode;
    uint8_t sequnceNum;
	uint8_t resendingNum;
	uint8_t rxOnEnable;
	bool promiscuousMode;
	uint16_t ack_timeout;
	int status;
    unsigned long total_send_bytes;
	unsigned long start_send_time;
	unsigned long last_send_time;
	PHY_PARAM *phy;
	BUFFER ack;
	uint16_t tx_ack_interval;
} MACL_PARAM;

struct ieee802154_my_addr {
	uint16_t	pan_id;					// for lazurite
	uint16_t	short_addr;				// for lazurite
	uint8_t		ieee_addr[8];			// for lazurite
	bool		pan_coord;				// common
};
extern MACL_PARAM* macl_init(void);	
extern int	macl_start(void);
extern int	macl_stop(void);
extern int	macl_xmit_sync(BUFFER buff);
extern int	macl_ed(uint8_t *level);
extern int	macl_set_channel(uint8_t page,uint8_t ch,uint32_t mbm);
extern int	macl_set_hw_addr_filt(struct ieee802154_my_addr *filt,unsigned long changed);
extern int	macl_set_cca_ed_level(uint32_t mbm);
extern int	macl_set_csma_params(uint8_t min_be, uint8_t max_be, uint8_t retries);
extern int	macl_set_frame_retries(uint8_t retries,uint16_t timeout);
extern int	macl_set_promiscuous_mode(bool on);

extern int	macl_rx_irq(BUFFER *rx,BUFFER *ack);
extern int	macl_rx_irq_notification(void);

extern int	macl_sleep(bool on);
extern uint8_t	macl_getCondition(void);
extern void	macl_set_ack_tx_interval(uint16_t interval);

#endif

