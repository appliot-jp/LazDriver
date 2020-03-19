/* macl.c
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

#ifdef SUBGHZ_OTA
	#pragma SEGCODE "OTA_SEGCODE"
	#pragma SEGINIT "OTA_SEGINIT"
	#pragma SEGNOINIT "OTA_SEGNOINIT"
	#pragma SEGCONST "OTA_SEGCONST"
#endif
#if defined LAZURITE_IDE
	#include <driver_irq.h>
	#include "serial.h"
#else
	#include <linux/module.h>
	#include "common-lzpi.h"
	#include "hwif/random-lzpi.h"
#endif

#include "mach.h"
#include "macl.h"
#include "errno.h"
#include "endian.h"
#include "hwif/hal.h"

// TIMEOUT
#define CCA_IDLE_DETECT_ABORT_TIME	50


struct macl_param macl;
#if defined(TW) || defined(JP)
//static const uint8_t HOPPING_SEARCH_LIST[] = { 24, 26, 28, 30, 34, 36, 38, 40, 42, 44 };
static const uint8_t HOPPING_SEARCH_LIST[] = { 24, 24, 24, 24, 24, 24, 24, 24, 24, 24 };
static uint8_t cmd_data_buf[64];
static BUFFER  buf_cache;
#endif
#define SUBGHZ_HOPPING_SYNC_REQUEST	0x80
#define SUBGHZ_HOPPING_SYNC_OK			0x81
const uint8_t SUBGHZ_HOPPING_ID[] = {0x00,0x1D,0x12,0x90};
/*
 ******************************************************
 Private handler section
 ******************************************************
 */
static void macl_dummy_handler(void);
static void macl_rxfifo_handler(void);
static bool macl_rxdone_handler(void);
static void macl_ack_txdone_handler(void);
static void macl_ack_txdone_abort_handler(void);
static void macl_txfifo_handler(void);
static void macl_ccadone_handler(void);
static void macl_ccadone_abort_handler(void);
static void macl_txdone_handler(void);
static void macl_txdone_abort_handler(void);
static void macl_ack_rxdone_handler(void);
static void macl_ack_rxdone_abort_handler(void);
#if defined(DEBUG)
static const char macl_condition_string[][32] = {
	"SUBGHZ_ST_INIT",
	"SUBGHZ_ST_INIT_FAIL",
	"SUBGHZ_ST_SLEEP",
	"SUBGHZ_ST_SLEEPED",
	"SUBGHZ_ST_SETUP",
	"SUBGHZ_ST_STANDBY",
	"SUBGHZ_ST_STOP",
	"SUBGHZ_ST_TX_START",
	"SUBGHZ_ST_CCA",
	"SUBGHZ_ST_CCA_ABORT",
	"SUBGHZ_ST_CCA_DONE",
	"SUBGHZ_ST_CCA_FAIL",
	"SUBGHZ_ST_TX_FIFO",
	"SUBGHZ_ST_TX_DONE",
	"SUBGHZ_ST_TX_ABORT",
	"SUBGHZ_ST_ACK_RX_DONE",
	"SUBGHZ_ST_ACK_RX_ABORT",
	"SUBGHZ_ST_ACK_RX_CRC",
	"SUBGHZ_ST_RX_START",
	"SUBGHZ_ST_RX_STARTED",
	"SUBGHZ_ST_RX_DONE",
	"SUBGHZ_ST_RX_FIFO",
	"SUBGHZ_ST_ACK_TX",
	"SUBGHZ_ST_ACK_TX_ABORT",
	"SUBGHZ_ST_ACK_TX_DONE",
	"SUBGHZ_ST_DUMMY"
};
static const char *macl_state_to_string(int condition) {
	return macl_condition_string[condition];
}
/*
static const char cca_state_str[][16] = {
	"CCA_IDLE",
	"CCA_FAST",
	"IDLE_DETECT",
	"CCA_RETRY",
	"CCA_FAILURE"
};
static const char *macl_cca_to_str(int condition) {
	return cca_state_str[condition];
}
*/
#endif

static int macl_total_transmission_time(uint16_t len) {
	uint32_t current_time;
	uint32_t duration;
	int status=STATUS_OK;

	current_time = HAL_millis();

#ifdef JP
	if((macl.ch >= 24)&&(macl.ch<=32)) {
		duration = 50 - (current_time - macl.last_send_time);
		if((duration <= 50) && (duration > 0)) HAL_sleep(duration);
		// restore time
		macl.last_send_time = HAL_millis();
	} else {
		duration = 2 - (current_time - macl.last_send_time);
		if((duration <= 2) && (duration > 0)) HAL_delayMicroseconds(duration*1000);
		// check total send bytes in an hours -- an hours
		duration = current_time - macl.start_send_time;
		if(duration > 3600000L) {
			macl.total_send_bytes = 0;
			macl.start_send_time = current_time;
		}

		// check total send bytes in an hours -- calcurate total send bytes
		switch(macl.pages) {
			case 1:  /*  50kbps */
				if(macl.total_send_bytes+len>2250000L) status = -EAGAIN;
				break;
			case 2:  /* 100kbps */
				if(macl.total_send_bytes+len>4500000L) status = -EAGAIN;
				break;
			case 4:  /* 80kbps */
				if(macl.total_send_bytes+len>3600000L) status = -EAGAIN;
				break;
			case 8:  /* 200kbps */
				if(macl.total_send_bytes+len>9000000L) status = -EAGAIN;
				break;
			default:
				status = -EAGAIN;
				break;
		}
		if (status == STATUS_OK) macl.total_send_bytes+=len;
	}
#endif

	return status;
}

int macl_cca_setting(void) {
	uint8_t be;
	uint16_t bo;
	uint16_t cca_time;
	static const char s1[] = "phy.unit_backoff_period is not set";
#ifdef JP
	be = (uint8_t)(macl.ccaMinBe + macl.ccaCount);
	if(be >= macl.ccaMaxBe) be = macl.ccaMaxBe;
	if(macl.phy->unit_backoff_period == 0) {
		alert(s1);
		return -EINVAL;
	}
	bo = (rand()%(( 1 << be) - 1))*macl.phy->unit_backoff_period;
	if((macl.ch >= 24) && (macl.ch <= 32)) {
		cca_time = 5000;
	} else {
		cca_time = 2000;
	}
#endif
	phy_timer_start(CCA_IDLE_DETECT_ABORT_TIME+(bo%3)*10,macl_ccadone_abort_handler);
	phy_sint_handler(macl_ccadone_handler);
	phy_ccaCtrl((uint32_t)cca_time+bo);
	return STATUS_OK;
}

void macl_hopping_cmd_rx(void *buff) {
	struct mac_header *mh;
	mh = buff;
	switch(macl.ch) {
		case SUBGHZ_HOPPING_TS_S:
			//PAYLOADDUMP(mh->raw.data,mh->raw.len);
			macl.hoppingdone = true;
			break;
		case SUBGHZ_HOPPING_TS_H:
			switch(mh->payload.data[0]) {
				case SUBGHZ_HOPPING_SYNC_REQUEST:
					{
						macl_timesync_search_request_cmd *req;
						req = (macl_timesync_search_request_cmd *)mh->raw->data;
						if(memcmp(req->payload.id,SUBGHZ_HOPPING_ID,sizeof(SUBGHZ_HOPPING_ID)) != 0) {
							break;
						}
					}
					{
						macl_timesync_params_cmd *res;

						phy_stop();
						phy_timer_stop();

						res = (macl_timesync_params_cmd *)macl.phy->out.data;
						macl.phy->out.len = 37+sizeof(HOPPING_SEARCH_LIST);

						res->mac_header = 0xEC23;
						res->seq = (uint8_t)rand();
						macl.sequenceNum= res->seq;
						res->panid = 0xFFFF;
						memcpy(res->dst,mh->src.addr.ieee_addr,8);
						memcpy(res->src,macl.parent->my_addr.ieee_addr,8);
						res->payload.cmd = SUBGHZ_HOPPING_SYNC_OK;
						res->payload.index = macl.hopping.host.ch_index;
						res->payload.size = (uint8_t) sizeof(HOPPING_SEARCH_LIST);
						res->payload.sync_interval = SUBGHZ_HOPPING_CH_DURATION;
						res->payload.sync_from = HAL_millis() - macl.hopping.host.sync_time;
						res->payload.sync_time = 0;
						memcpy(res->payload.ch_list,HOPPING_SEARCH_LIST,sizeof(HOPPING_SEARCH_LIST));

						macl.hopping_state = SUBGHZ_ST_HOPPING_HOST_CMD_TX;

						macl.status = macl_total_transmission_time(macl.phy->out.len+TX_TTL_OFFSET);
						if (macl.status != STATUS_OK){
							break;
						}

						macl.hoppingdone = false;

						macl.status=STATUS_OK;
						macl.resendingNum = 0;
						macl.ccaCount=0;
						macl.tx_callback = NULL;

						phy_txpre(MANUAL_TX);
						macl_cca_setting();
						macl.condition=SUBGHZ_ST_CCA;
						HAL_GPIO_enableInterrupt();
#if !defined(LAZURITE_IDE) && defined(DEBUG)
						printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
	return;
}

static void macl_timesync_host_isr(void) {
	if(macl.txdone && macl.rxdone) {
		HAL_GPIO_disableInterrupt();
		phy_timer_stop();
		macl.hopping.host.sync_time = HAL_millis();
		macl.hopping.host.ch_index++;
		if(macl.hopping.host.ch_index >= sizeof(HOPPING_SEARCH_LIST)) {
			macl.hopping.host.ch_index=0;
		}
		// close
		phy_stop();
		// set channel
		phy_setup(macl.pages,HOPPING_SEARCH_LIST[macl.hopping.host.ch_index],macl.txPower,macl.antsw);
		// rxEnable
		phy_sint_handler(macl_rxfifo_handler);
		phy_rxstart();
		HAL_GPIO_enableInterrupt();
		macl.bit_params.hopping_sync_host_irq = false;
#ifdef LAZURITE_IDE
		Serial.println("macl_timesync_host_isr");
#else
		printk(KERN_INFO"%s\n",__func__);
#endif
	} else {
		macl.bit_params.hopping_sync_host_irq = true;
	}
	return;
}

static void macl_txdone(void) {
	switch(macl.hopping_state) {
		case SUBGHZ_ST_HOPPING_NOP:
			macl.txdone = true;
			if(macl.bit_params.hopping_sync_host_irq) macl_timesync_host_isr();
			break;
		case SUBGHZ_ST_HOPPING_SLAVE_SYNC_REQ:
			break;
		default:
			macl.hoppingdone = true;
			macl.hopping_state = SUBGHZ_ST_HOPPING_NOP;
			break;
	}
	return;
}

static bool macl_timesync_search_gateway(void){
	uint8_t ch_index;
	uint8_t ch_scan_count = 0;
	uint8_t ch_scan_cycle = SUBGHZ_HOPPING_SEARCH_CYCLE;
	struct mac_fc_alignment fc;
	macl_timesync_search_request_cmd *req;
	macl_timesync_params_cmd *res;

	//printk(KERN_INFO"%s start %d\n",__func__,HZ);
	ch_index = 0;
	//initializing search gateway
	ch_index = 0;

	// mac header of search gateway
	memset(&fc,0,sizeof(fc));
	fc.frame_type = IEEE802154_FC_TYPE_CMD;
	fc.frame_ver = IEEE802154_FC_VER_4E;
	fc.ack_req = 1;

	// 送信するデータは一時退避しておく
	memcpy(&buf_cache,&macl.phy->out,sizeof(BUFFER));
	macl.phy->out.data = &cmd_data_buf[1];
	macl.phy->out.size = sizeof(cmd_data_buf)-1;

	// sync requestのコマンドをセットする
	req = (macl_timesync_search_request_cmd *)macl.phy->out.data;
	req->mac_header = 0xE803;
	req->seq = (uint8_t) rand();
	req->panid = 0xFFFF;
	req->dst = 0xFFFF;
	memcpy(req->src,macl.parent->my_addr.ieee_addr,8);
	req->payload.cmd = SUBGHZ_HOPPING_SYNC_REQUEST;
	memcpy(req->payload.id,SUBGHZ_HOPPING_ID,sizeof(SUBGHZ_HOPPING_ID));;
	macl.phy->out.len= sizeof(macl_timesync_search_request_cmd);
#ifdef LAZURITE_IDE
	Serial.print("macl_timesync_search_request_cmd:: ");
	Serial.print_long((long)macl.phy->out.len,DEC);
	Serial.print(",");
	Serial.println_long((long)sizeof(macl_timesync_search_request_cmd),DEC);
	delay(20);
#endif
	/*
		 PAYLOADDUMP(macl.phy->out.data,macl.phy->out.len);
		 */

	macl.bit_params.sync_enb = false;
	macl.hopping_state = SUBGHZ_ST_HOPPING_SLAVE_SYNC_REQ;
	macl.hopping.slave.sync_cmd = NULL;
	while((ch_scan_cycle > ch_scan_count) &&
			(macl.bit_params.sync_enb == false)) {
		while(ch_index < sizeof(HOPPING_SEARCH_LIST)) {
			if(macl.bit_params.stop == true) {
				macl.status = -ENOPROTOOPT;
				goto error;
			}
			macl.status = macl_total_transmission_time(macl.phy->out.len+TX_TTL_OFFSET);
			if (macl.status != STATUS_OK){
				goto error;
			}
			// CH切り替え
			HAL_GPIO_disableInterrupt();
			phy_timer_stop();
			phy_stop();
			phy_setup(macl.pages,HOPPING_SEARCH_LIST[ch_index],macl.txPower,macl.antsw);
			// subghz_send
			phy_txpre(MANUAL_TX);
			HAL_GPIO_enableInterrupt();
			macl.condition=SUBGHZ_ST_CCA;
			macl.hoppingdone = false;
			macl_cca_setting();
			// wait receive sync_cmd
#ifdef NOT_INLINE
			HAL_wait_event_interruptible_timeout(&macl.que,&macl.hoppingdone,SUBGHZ_HOPPING_SEARCH_INTERVAL);
#else
			HAL_wait_event_interruptible_timeout(macl.que,macl.hoppingdone,SUBGHZ_HOPPING_SEARCH_INTERVAL);
#endif
			//printk(KERN_INFO"end of HAL_wait_event_interruptible_timeout\n");
			if(macl.parent->rx.raw->len > 0) {
				res = (macl_timesync_params_cmd *) macl.parent->rx.raw->data;
				if(res->payload.cmd == SUBGHZ_HOPPING_SYNC_OK) {
					res->payload.sync_time = HAL_millis()-res->payload.sync_from;
					memcpy(cmd_data_buf,macl.parent->rx.raw->data,macl.parent->rx.raw->len);
					macl.bit_params.sync_enb = true;
					macl.bit_params.timer_sync = false;
					macl.hopping.slave.sync_cmd = res;
					break;
				}
			} else {
				ch_index++;
			}
		}
		ch_scan_count++;
		ch_index = 0;
	}
	memcpy(&macl.phy->out,&buf_cache,sizeof(BUFFER));
error:
	macl.hoppingdone = true;
	//printk(KERN_INFO"%s end\n",__func__);
	macl.hopping_state = SUBGHZ_ST_HOPPING_NOP;
	return macl.bit_params.sync_enb;
}

static void macl_timesync_slave_isr(void) {
	uint32_t now;
	uint32_t timer;
	uint32_t ch;
	{
		macl_timesync_params_cmd *sf;
		sf = (macl_timesync_params_cmd *) cmd_data_buf;
		now = HAL_millis();
		timer = sf->payload.sync_interval - (now - sf->payload.sync_time)%sf->payload.sync_interval;
		if(timer < 50) {
			timer += sf->payload.sync_interval;
			ch = (sf->payload.index + (now - sf->payload.sync_time)/sf->payload.sync_interval + 1)%sf->payload.size;
		} else {
			ch = (sf->payload.index + (now - sf->payload.sync_time)/sf->payload.sync_interval + 0)%sf->payload.size;
		}
	}
	/*
		 timer4.set(timer,macl_timesync_slave_isr);
		 timer4.start();
		 */
	phy_stop();
	phy_setup(macl.pages,HOPPING_SEARCH_LIST[macl.hopping.host.ch_index],macl.txPower,macl.antsw);
	phy_rxstart();
	return;
}

static void macl_dummy_handler(void)
{
	macl.condition = SUBGHZ_ST_DUMMY;
	return;
}
static void macl_rxdone_abort_handler(void) {
	macl.rxdone = true;
	// macl_start();
	phy_sint_handler(macl_rxfifo_handler);
	phy_rxstart();
	macl.condition=SUBGHZ_ST_RX_STARTED;
	HAL_wake_up_interruptible(&macl.que);
}
static void macl_rxfifo_handler(void)
{
	int status;
	macl.rxdone = false;
	macl.condition=SUBGHZ_ST_RX_FIFO;
	phy_timer_stop();
	status = phy_rxdone();

#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s,%d\n",__func__,__LINE__,macl_state_to_string(macl.condition),status);
#endif
	switch(status) {
		case FIFO_CONT:			// next data 
			phy_timer_start(100,macl_rxdone_abort_handler);
			break;
		case FIFO_DONE:		// rxdone
			// my packet
			if(macl.bit_params.promiscuousMode) {
				// macl_start();
				phy_sint_handler(macl_rxfifo_handler);
				phy_rxstart();
				macl.condition=SUBGHZ_ST_RX_STARTED;
				macl_rxdone_handler();
				macl.rxdone = true;
			} else if ((((macl.phy->in.data[0]&0x07) == IEEE802154_FC_TYPE_CMD) || ((macl.phy->in.data[0]&0x07) == IEEE802154_FC_TYPE_DATA) )){
				if(macl_rxdone_handler() == true) {
					macl.status = STATUS_OK;
					// macl_start();
					phy_sint_handler(macl_rxfifo_handler);
					phy_rxstart();
					macl.condition=SUBGHZ_ST_RX_STARTED;
					macl.rxdone = true;
					break;
				} else {
					// send ACK or CMD
					break;
				}
			} else {
				// Disposal packet continue to CRC_ERROR
			}
		case CRC_ERROR:		// rxdone
		default:			// error
			macl.condition=SUBGHZ_ST_RX_START;
#if !defined(LAZURITE_IDE) && defined(DEBUG)
			printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
			// macl_start();
			phy_sint_handler(macl_rxfifo_handler);
			phy_rxstart();
			macl.condition=SUBGHZ_ST_RX_STARTED;
			macl.rxdone = true;
			break;
	}
	HAL_wake_up_interruptible(&macl.que);
	return;
}

static bool macl_rxdone_handler(void)
{
	int status;
	bool result;
	bool isAck;

	macl.condition=SUBGHZ_ST_RX_DONE;
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
	status = macl_rx_irq(&isAck);

	if (macl.bit_params.promiscuousMode) {
		macl.status = STATUS_OK;
		phy_rxstart();
		macl_rx_irq(NULL);
		result = true;
		goto end;
	}
	if (status != STATUS_OK) {
		macl.status = status;
		result = true;
		goto end;
	}
	if(isAck){
#ifdef JP
		if(macl.ch >= 33) {
			status = macl_total_transmission_time(macl.phy->out.len+TX_TTL_OFFSET);
			if(status != STATUS_OK) {
				macl.status = status;
				macl_rx_irq(NULL);
				phy_rxstart();
				result = true;
				goto end;
			}
		}
#endif
		HAL_delayMicroseconds((uint32_t)macl.tx_ack_interval);
		phy_timer_start(20,macl_ack_txdone_abort_handler);
		phy_sint_handler(macl_ack_txdone_handler);
		phy_txpre(AUTO_TX);
		macl.status = STATUS_OK;
		macl.condition = SUBGHZ_ST_ACK_TX;
		result = false;
	} else {
		macl.status = STATUS_OK;
		macl_rx_irq(NULL);
		result = macl.hoppingdone;
	}
end:
	return result;
}

static void macl_txfifo_handler(void)
{
	FIFO_STATE fifo_state;
	macl.condition = SUBGHZ_ST_TX_FIFO;
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
	fifo_state = phy_txfifo();
	switch(fifo_state) {
		case CRC_ERROR:
			macl_txdone_abort_handler();
			break;
		case FIFO_DONE:
			macl_txdone_handler();
			break;
		default:
			break;
	}
	return;
}

static void macl_ack_txdone_handler(void)
{
	macl.condition=SUBGHZ_ST_ACK_TX_DONE;
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
	phy_timer_stop();
	phy_txdone();

	macl.status = STATUS_OK;
	macl_rx_irq(NULL);				// rx callback
	//  macl_start();
	phy_sint_handler(macl_rxfifo_handler);
	phy_rxstart();
	macl.condition=SUBGHZ_ST_RX_STARTED;
	macl.rxdone = true;
	HAL_wake_up_interruptible(&macl.que);

	return;
}
extern int reg_access_check;
static void macl_ack_txdone_abort_handler(void)
{
	static const char s1[] = "macl_txdone_abort_handler";
	phy_timer_stop();
	if(phy_txfifo() == FIFO_DONE) {
		macl.status = STATUS_OK;
	} else {
		alert(s1);
		macl.status=-EDEADLK;
	}
	phy_txdone();
	macl_rx_irq(NULL);				// rx callback
	// macl_start();
	phy_sint_handler(macl_rxfifo_handler);
	phy_rxstart();
	macl.condition=SUBGHZ_ST_RX_STARTED;
	macl.rxdone = true;
	HAL_wake_up_interruptible(&macl.que);
	return;
}

static void macl_ccadone_handler(void)
{
	int status = STATUS_OK;
	uint8_t cca_idle;

#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif

	macl.condition=SUBGHZ_ST_CCA_DONE;

	phy_timer_stop();

	cca_idle = phy_ccadone();
	phy_timer_start(160,macl_txdone_abort_handler);
	phy_sint_handler(macl_txfifo_handler);
	status = phy_txstart();
	if(status != STATUS_OK) {
		macl.status = status;
		if(macl.tx_callback) macl.tx_callback(0,macl.status);
		if(macl.bit_params.rxOnEnable == true) {
			// macl_start()
			phy_sint_handler(macl_rxfifo_handler);
			phy_rxstart();
			macl.condition=SUBGHZ_ST_RX_STARTED;
		}
		macl_txdone();
		if(macl.bit_params.hopping_sync_host_irq) macl_timesync_host_isr();
	}

	HAL_wake_up_interruptible(&macl.que);
	return;
}

static void macl_ccadone_abort_handler(void)
{
	uint8_t ccadone;
	phy_timer_stop();
	macl.status = -EBUSY;
	macl.condition=SUBGHZ_ST_CCA_ABORT;

	ccadone = phy_ccadone();
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%02x\n",__func__,__LINE__,ccadone);
#endif
	if(macl.tx_callback) macl.tx_callback(0,macl.status);
	if(macl.bit_params.rxOnEnable == true) {
		// macl_start
		phy_sint_handler(macl_rxfifo_handler);
		phy_rxstart();
		macl.condition=SUBGHZ_ST_RX_STARTED;
	}
	macl_txdone();
	HAL_wake_up_interruptible(&macl.que);
	return;
}

static void macl_txdone_abort_handler(void)
{
	static const char s1[] = "macl_txdone_abort_handler";
	macl.condition=SUBGHZ_ST_TX_ABORT;
	phy_timer_stop();
	alert(s1);
	phy_monitor();
	phy_stop();
	//phy_monitor();
	macl.status = -EDEADLK;
	if(macl.tx_callback) macl.tx_callback(0,macl.status);

	macl_txdone();
	HAL_wake_up_interruptible(&macl.que);
}

static void macl_txdone_handler(void)
{
	uint8_t ack_req;
	uint16_t ack_timeout;
	macl.condition=SUBGHZ_ST_TX_DONE;
	phy_timer_stop();
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
	phy_txdone();
	ack_req = (uint8_t)(macl.phy->out.data[0]&0x20);
	if(ack_req){
		ack_timeout = (uint16_t)(macl.ack_timeout == 0 ? 20: macl.ack_timeout);
		phy_timer_start(ack_timeout,macl_ack_rxdone_abort_handler);
		phy_sint_handler(macl_ack_rxdone_handler);
		phy_rxstart();
	}else{
		if(macl.tx_callback) macl.tx_callback(0,STATUS_OK);
		if((macl.bit_params.rxOnEnable == true) || (macl.hoppingdone == false)) {
			// macl_start();
			phy_sint_handler(macl_rxfifo_handler);
			phy_rxstart();
			macl.condition=SUBGHZ_ST_RX_STARTED;
		}
		macl_txdone();
	}
	HAL_wake_up_interruptible(&macl.que);
}

static void macl_ack_rxdone_handler(void) {
	FIFO_STATE rxtype;
	bool isAck;
	macl.condition=SUBGHZ_ST_ACK_RX_DONE;
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
	phy_timer_stop();

	rxtype = phy_rxdone();

	switch(rxtype) {
		case FIFO_CONT:
			break;
		case FIFO_DONE:
			if(((macl.phy->in.data[0]&0x07) == IEEE802154_FC_TYPE_ACK) && (macl.phy->in.data[2] == macl.sequenceNum)){
				phy_timer_stop();
				macl_rx_irq(&isAck);
				if(macl.tx_callback) macl.tx_callback(macl.phy->in.data[macl.phy->in.len-1],STATUS_OK);
				if((macl.bit_params.rxOnEnable == true) || (macl.hoppingdone == false)) {
					// macl_start();
					phy_sint_handler(macl_rxfifo_handler);
					phy_rxstart();
					macl.condition=SUBGHZ_ST_RX_STARTED;
				}
				macl_txdone();
			} else {
				macl_ack_rxdone_abort_handler();
			}
			break;
		case CRC_ERROR:
		default:
			macl.condition = SUBGHZ_ST_ACK_RX_CRC;
			macl_ack_rxdone_abort_handler();
			break;
	}
	HAL_wake_up_interruptible(&macl.que);
}

static void macl_ack_rxdone_abort_handler(void) {
	static const char s1[] = "macl_ack_txdone txpre error";
	macl.condition=SUBGHZ_ST_ACK_RX_ABORT;
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s,%d\n",__func__,__LINE__,macl_state_to_string(macl.condition),macl.condition);
#endif
	phy_timer_stop();
	phy_stop();
	macl.resendingNum++;
	if(macl.resendingNum <= macl.txRetries) {
		macl.status = macl_total_transmission_time(macl.phy->out.len+TX_TTL_OFFSET);
		if(macl.status != STATUS_OK) {
			goto error;
		}
		if(macl.hopping_state == SUBGHZ_ST_HOPPING_HOST_CMD_TX) {
			macl_timesync_params_cmd *res;
			res = (macl_timesync_params_cmd *)macl.phy->out.data;
			res->payload.sync_from = HAL_millis() - macl.hopping.host.sync_time;
		}
		macl.status = phy_txpre(MANUAL_TX);
		if(macl.status != STATUS_OK) {
			alert(s1);
			macl.status = -EDEADLK;
			goto error;
		}
		macl.status = macl_cca_setting();
		if(macl.status != STATUS_OK) {
			goto error;
		}
		HAL_wake_up_interruptible(&macl.que);
		return;
	} else {
		macl.status = -ETIMEDOUT;
		goto error;
	}
error:
	if(macl.tx_callback) macl.tx_callback(0,macl.status);
	if(macl.bit_params.rxOnEnable == true) {
		//macl_start();
		phy_sint_handler(macl_rxfifo_handler);
		phy_rxstart();
		macl.condition=SUBGHZ_ST_RX_STARTED;
	}
	macl_txdone();
	HAL_wake_up_interruptible(&macl.que);
}

/*
 ******************************************************
 Public function section
 ******************************************************
 */
struct macl_param *macl_init(void* parent)
{
	memset(&macl,0,sizeof(struct macl_param));
	macl.parent = (struct mach_param*) parent;
	macl.txdone = true;
	macl.rxdone = true;
	macl.hoppingdone = true;
	macl.condition = SUBGHZ_ST_INIT;
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif

	// 0:normal, 1:wait at fifodone, 2:no cca
	macl.phy = phy_init();
	phy_sint_handler(macl_dummy_handler);
	if(macl.phy == NULL) {
		goto error;
	}

	macl.tx_ack_interval = 1000;

	HAL_init_waitqueue_head(&macl.que);
	macl.condition = SUBGHZ_ST_SLEEPED;
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
	return &macl;
error:
	macl.condition = SUBGHZ_ST_INIT_FAIL;
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
	macl.status = -EIO;
	return NULL;
}


/********************************************************************/
/*! @brief macl start 
	mac low layer rx on
	@return			0=STATUS_OK, other = error
	@exception	return NULL
 ********************************************************************/
int macl_start(void) {
	int status=STATUS_OK;
	uint8_t ch;
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
	macl.condition=SUBGHZ_ST_RX_START;
	switch(macl.ch) {
		case SUBGHZ_HOPPING_TS_H:
			phy_stop();
			phy_timer_stop();
			HAL_GPIO_disableInterrupt();
			macl.hopping.host.ch_index=0;
			ch = HOPPING_SEARCH_LIST[macl.hopping.host.ch_index];
			phy_setup(macl.pages,ch,macl.txPower,macl.antsw);
			macl.hopping.host.sync_time = HAL_millis();
			timer4.set(SUBGHZ_HOPPING_CH_DURATION,macl_timesync_host_isr);
			timer4.start();
			HAL_GPIO_enableInterrupt();
			break;
		case SUBGHZ_HOPPING_TS_S:
			if(macl.bit_params.sync_enb == false) {
				if(macl_timesync_search_gateway() == true) {
					timer4.set(macl.hopping.host.ch_duration,macl_timesync_slave_isr);
					timer4.start();
				} else {
					return -ENOPROTOOPT;
				}
			} else {
				// TODO: 送信により時刻同期済状態でRX STARTする。
				// OFFSET時刻を計算して最初のタイマー時間をセットする
			}
			break;
		default:
			ch = macl.ch;
			break;
	}
	macl.rxdone = true;
	macl.bit_params.rxOnEnable = 1;
	phy_sint_handler(macl_rxfifo_handler);
	phy_rxstart();
	macl.condition=SUBGHZ_ST_RX_STARTED;
	HAL_GPIO_enableInterrupt();
	return status;
}

int	macl_stop(void)
{
	int status=STATUS_OK;
	macl.condition=SUBGHZ_ST_STOP;
	macl.bit_params.rxOnEnable = 0;
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
	HAL_GPIO_disableInterrupt();
	phy_stop();
	phy_timer_stop();
	phy_sint_handler(macl_dummy_handler);
	macl.condition=SUBGHZ_ST_STANDBY;
	return status;
}

int	macl_xmit_sync(BUFFER *buff) {
	static const char s0[] = "rxdone abort in tx";
	uint32_t time;
	uint32_t diff_time;
	uint32_t now;
	uint16_t ch_index;
	uint16_t time_offset;
	macl.condition=SUBGHZ_ST_TX_START;

#ifdef NOT_INLINE
	//uint32_t HAL_wait_event_interruptible_timeout(wait_queue_head_t *q,volatile int *condition,uint32_t ms)
	{
		volatile uint32_t st_time = millis();
		volatile uint32_t status;
		const uint32_t ms = 100L;
		do {
			status = st_time+ms-millis();
			if(status > ms) {
				status = 0;
			}
		} while(((macl.rxdone & macl.hoppingdone) == false) && (status > 0));
		time = status;
	}
#else
	time =  HAL_wait_event_interruptible_timeout(macl.que,macl.rxdone&macl.hoppingdone,100L);
#endif
	HAL_GPIO_disableInterrupt();
	phy_stop();
	phy_timer_stop();
	macl.txdone = false;
	if(time == 0) {
		alert(s0);
	}
	switch(macl.ch) {
		case SUBGHZ_HOPPING_TS_S:
			// 時刻同期
			if(macl.bit_params.sync_enb == false) {
				if(macl_timesync_search_gateway() != false) {
					macl.status = -ENOPROTOOPT;
					goto error;
				}
			}
			// 時刻同期の結果に基づき使用するCHを計算し周波数設定を行う。
			{
				/*
				uint32_t diff_time;
				uint32_t now = HAL_millis();
				uint16_t ch_index;
				uint16_t time_offset;
				*/
				now = HAL_millis();
				diff_time = now - macl.hopping.slave.sync_cmd->payload.sync_time;
				ch_index = diff_time/macl.hopping.slave.sync_cmd->payload.sync_interval;
				ch_index += macl.hopping.slave.sync_cmd->payload.index;
				ch_index = ch_index % macl.hopping.slave.sync_cmd->payload.size;
				time_offset = diff_time%macl.hopping.slave.sync_cmd->payload.sync_interval;
				if(macl.hopping.slave.sync_cmd->payload.sync_interval < time_offset + 100) {
					ch_index++;
				}
				phy_setup(macl.pages,macl.hopping.slave.sync_cmd->payload.ch_list[ch_index],macl.txPower,macl.antsw);
			}
			break;
		case SUBGHZ_HOPPING_TS_H:
		default:
			break;
	}
	macl.status=STATUS_OK;
	macl.phy->out = *buff;
	macl.resendingNum = 0;
	macl.ccaCount=0;
	macl.sequenceNum= buff->data[2];
	macl.tx_callback = NULL;

	macl.status = macl_total_transmission_time(macl.phy->out.len+TX_TTL_OFFSET);
	if (macl.status != STATUS_OK){
		goto error;
	}

	phy_txpre(MANUAL_TX);
	macl_cca_setting();
	macl.condition=SUBGHZ_ST_CCA;
	HAL_GPIO_enableInterrupt();
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif

#ifdef NOT_INLINE
	time =  HAL_wait_event_interruptible_timeout(&macl.que,&macl.txdone,1000L);
#else
	time =  HAL_wait_event_interruptible_timeout(macl.que,macl.txdone,1000L);
#endif
	if(time == 0) {
		if(macl.bit_params.rxOnEnable == true) {
			// macl_start();
			phy_sint_handler(macl_rxfifo_handler);
			phy_rxstart();
			macl.condition=SUBGHZ_ST_RX_STARTED;
		}
		macl.status = -EDEADLK;
	}
error:
	return macl.status;
}

int	macl_xmit_async(BUFFER *buff,void (*callback)(uint8_t rssi, int status))
{
	static const char s0[] = "rxdone abort in tx";
	uint32_t time;
	macl.condition=SUBGHZ_ST_TX_START;

#ifdef NOT_INLINE
	time =  HAL_wait_event_interruptible_timeout(&macl.que,&macl.rxdone,100L);
#else
	time =  HAL_wait_event_interruptible_timeout(macl.que,macl.rxdone,100L);
#endif
	HAL_GPIO_disableInterrupt();
	macl.txdone = false;
	if(time == 0) {
		alert(s0);
	}
	phy_stop();
	phy_timer_stop();
	phy_sint_handler(macl_dummy_handler);

	macl.status=STATUS_OK;
	macl.phy->out = *buff;
	macl.resendingNum = 0;
	macl.ccaCount=0;
	macl.sequenceNum= buff->data[2];
	macl.tx_callback = callback;

	macl.status = macl_total_transmission_time(macl.phy->out.len+TX_TTL_OFFSET);
	if (macl.status != STATUS_OK){
		goto error;
	}

	phy_txpre(MANUAL_TX);
	macl_cca_setting();
	macl.condition=SUBGHZ_ST_CCA;
	HAL_GPIO_enableInterrupt();
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif

error:
	return macl.status;
}

int	macl_set_modulation(int8_t mod, int8_t sf)
{
	return phy_setModulation(mod, sf);
}

int	macl_get_modulation(int8_t *mod, int8_t *sf)
{
	return phy_getModulation(mod,sf);
}

int	macl_set_channel(uint8_t page,uint8_t ch, uint32_t mbm, uint8_t antsw)
{
	int status=STATUS_OK;
	macl.condition = SUBGHZ_ST_SETUP;

	if(macl.bit_params.rxOnEnable) {
		phy_stop();
	}
	macl.pages = page;
	macl.ch = ch;
	macl.antsw = antsw;

	if (mbm == 100){ 
		macl.txPower = 1;
	}else {
		macl.txPower = 20;
	}
	if(macl.ch < SUBGHZ_HOPPING) {
		status = phy_setup(macl.pages,macl.ch,macl.txPower,macl.antsw);
	}
	macl.condition = SUBGHZ_ST_STANDBY;
	return status;
}

int	macl_set_hw_addr_filt(struct ieee802154_my_addr *filt,uint32_t changed)
{
	int status=STATUS_OK;
	phy_addrFilt(filt->pan_id, filt->ieee_addr, filt->short_addr,0xffff);
	return status;
}

int	macl_set_csma_params(uint8_t min_be, uint8_t max_be, uint8_t retries)
{
	int status=STATUS_OK;
	macl.ccaRetries = retries;
	macl.ccaMinBe = min_be;
	macl.ccaMaxBe = max_be;
	return status;
}
int	macl_set_frame_retries(uint8_t retries,uint32_t timeout)
{
	int status=STATUS_OK;
	macl.txRetries = retries;
	macl.ack_timeout = (uint16_t)timeout;
	return status;
}
int	macl_set_promiscuous_mode(bool on)
{
	int status=STATUS_OK;

	macl.bit_params.promiscuousMode = on;
	if (macl.bit_params.promiscuousMode){
		phy_clrAddrFilt();
	}
	return status;
}

int	macl_sleep(void)
{
	int status=STATUS_OK;
	macl.condition = SUBGHZ_ST_SLEEP;
	phy_sleep();
	macl.condition = SUBGHZ_ST_SLEEPED;
	return status;
}

void macl_set_ack_tx_interval(uint16_t interval) {
	macl.tx_ack_interval = interval;
}
void macl_set_antsw(uint8_t antsw) {
	macl.antsw = antsw;
}
void macl_force_stop(void) {
	macl.bit_params.stop = true;
}

