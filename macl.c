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
static const uint8_t HOPPING_SEARCH_LIST[] = { 24, 26, 28, 30, 34, 36, 38, 40, 42, 44 };
//static const uint8_t HOPPING_SEARCH_LIST[] = { 24, 24, 24, 24, 24, 24, 24, 24, 24, 24 };
static uint8_t cmd_data_buf[64];
static BUFFER  buf_cache;
#endif
#define SUBGHZ_HOPPING_SYNC_REQUEST	0x81
#define SUBGHZ_HOPPING_SYNC_OK			0x82
const uint8_t SUBGHZ_HOPPING_ID[] = {0x00,0x1D,0x12,0x90};
/*
 ******************************************************
 Private handler section
 ******************************************************
 */
static void macl_dummy_handler(void);
static void macl_rxfifo_handler(void);
static void macl_rxdone_handler(void);
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
#endif

static union {
	struct {
		volatile uint32_t now;
		volatile uint32_t diff_time;
		volatile uint16_t diff_ch;
	} host;
	struct {
		volatile uint32_t time;
		volatile uint32_t diff_time;
		volatile uint16_t ch_index;
		volatile uint16_t time_offset;
	} slave;
} local;

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
	union {
		macl_timesync_search_request_raw16 *req16;
		macl_timesync_search_request_raw64 *req64;
	} req;
	union {
		//macl_timesync_params_raw16 *res16;		support only 64bit addressing mode
		macl_timesync_params_raw64 *res64;
	} res;
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
						req.req16 = (macl_timesync_search_request_raw16 *)mh->raw->data;
						if(memcmp(req.req16->payload.id,SUBGHZ_HOPPING_ID,sizeof(SUBGHZ_HOPPING_ID)) != 0) {
							break;
						}
					}
					{
						phy_stop();
						phy_timer_stop();

						res.res64 = (macl_timesync_params_raw64 *)macl.phy->out.data;
						macl.phy->out.len = 37+sizeof(HOPPING_SEARCH_LIST);

						res.res64->mac_header = 0xEC23;
						res.res64->seq = (uint8_t)rand();
						macl.sequenceNum= mh->seq;
						res.res64->panid = 0xFFFF;
						memcpy(res.res64->dst,mh->src.addr.ieee_addr,8);
						memcpy(res.res64->src,macl.parent->my_addr.ieee_addr,8);
						res.res64->payload.cmd = SUBGHZ_HOPPING_SYNC_OK;
						res.res64->payload.index = macl.hopping.host.ch_index;
						res.res64->payload.size = (uint8_t) sizeof(HOPPING_SEARCH_LIST);
						res.res64->payload.sync_interval = SUBGHZ_HOPPING_CH_DURATION;
						res.res64->payload.sync_from = HAL_millis() - macl.hopping.host.sync_time;
						res.res64->payload.sync_time = 0;
						memcpy(res.res64->payload.ch_list,HOPPING_SEARCH_LIST,sizeof(HOPPING_SEARCH_LIST));

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
#ifdef LAZURITE_IDE
						Serial.println_long(__LINE__,DEC);
#endif
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

static void macl_hopping_host_phy_setup(void) {
	local.host.now = HAL_millis();
	macl.bit_params.hopping_sync_host_irq = false;
	local.host.diff_time = local.host.now - macl.hopping.host.sync_time;
	local.host.diff_ch = local.host.diff_time / SUBGHZ_HOPPING_CH_DURATION;
	macl.hopping.host.ch_index += local.host.diff_ch;
	if(macl.hopping.host.ch_index >= sizeof(HOPPING_SEARCH_LIST)) {
		macl.hopping.host.ch_index = macl.hopping.host.ch_index % sizeof(HOPPING_SEARCH_LIST);
	}
	macl.hopping.host.sync_time = macl.hopping.host.sync_time + SUBGHZ_HOPPING_CH_DURATION * local.host.diff_ch;

	phy_stop();
	phy_setup(macl.pages,HOPPING_SEARCH_LIST[macl.hopping.host.ch_index],macl.txPower,macl.antsw);
}

static uint32_t macl_hopping_slave_phy_setup(void) {
	local.slave.time = HAL_millis();
	local.slave.diff_time = local.slave.time - macl.hopping.slave.sync->payload.sync_time;
	local.slave.ch_index = (uint16_t) (local.slave.diff_time/macl.hopping.slave.sync->payload.sync_interval);
	local.slave.ch_index += macl.hopping.slave.sync->payload.index;
	local.slave.ch_index = local.slave.ch_index % macl.hopping.slave.sync->payload.size;
	local.slave.time_offset = (uint16_t)(macl.hopping.slave.sync->payload.sync_interval - (uint16_t)(local.slave.diff_time%macl.hopping.slave.sync->payload.sync_interval));
	if(local.slave.time_offset < 10) {
		local.slave.ch_index++;
		local.slave.time_offset += macl.hopping.slave.sync->payload.sync_interval;
	}
	if(local.slave.ch_index >= macl.hopping.slave.sync->payload.size) {
		local.slave.ch_index = 0;
	}
	macl.hopping.slave.ch_index = (uint8_t)local.slave.ch_index;
	phy_stop();
	phy_setup(macl.pages,macl.hopping.slave.sync->payload.ch_list[local.slave.ch_index],macl.txPower,macl.antsw);
/*
#ifdef LAZURITE_IDE
	Serial.print("macl_hopping_slave_phy_setup: ");
	Serial.print_long((long)local.slave.ch_index,DEC);
	Serial.print(",");
	Serial.print_long((long)HOPPING_SEARCH_LIST[local.slave.ch_index],DEC);
	Serial.print(",");
	Serial.println_long((long)local.slave.diff_time,DEC);
#endif
*/
	return local.slave.time_offset;
}
static void macl_timesync_host_isr(void) {
	if((macl.bit_params.txReserve == false) && macl.txdone && macl.rxdone && macl.hoppingdone) {
		macl.hoppingdone = false;
#ifndef LAZURITE_IDE
		ACCESS_PUSH(1);
#endif
		// set channel
		macl_hopping_host_phy_setup();
/*
#ifdef LAZURITE_IDE
		Serial.print("macl_timesync_host_isr: ");
		Serial.print_long((long)macl.hopping.host.ch_index,DEC);
		Serial.print(",");
		Serial.print_long((long)HOPPING_SEARCH_LIST[macl.hopping.host.ch_index],DEC);
		Serial.print(",");
		Serial.println_long((long)macl.bit_params.sync_enb,DEC);
#endif
*/
		// rxEnable
		phy_sint_handler(macl_rxfifo_handler);
		phy_rxstart();
		macl.condition=SUBGHZ_ST_RX_STARTED;
/*
#ifdef LAZURITE_IDE
		Serial.println("macl_timesync_host_isr");
#else
		printk(KERN_INFO"%s index=%d CH=%d\n",__func__,macl.hopping.host.ch_index, HOPPING_SEARCH_LIST[macl.hopping.host.ch_index]);
#endif
*/
		macl.hoppingdone = true;
		HAL_wake_up_interruptible(&macl.que);
	} else {
		macl.bit_params.hopping_sync_host_irq = true;
	}
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif
	return;
}

static void macl_timesync_slave_isr(void) {
	if(macl.bit_params.sync_enb == false) {
		macl.bit_params.timer_sync = false;
		timer4.stop();
		macl.bit_params.hopping_sync_slave_irq = false;
		return;
	}
	if((macl.bit_params.txReserve == false) && macl.txdone && macl.rxdone && macl.hoppingdone) {
		macl.hoppingdone = false;
		macl.bit_params.hopping_sync_slave_irq = false;
		if(macl.bit_params.timer_sync == false) {
			timer4.stop();
			timer4.set(macl.hopping.slave.sync->payload.sync_interval,macl_timesync_slave_isr);
			timer4.start();
			macl.bit_params.timer_sync = true;
		}
#ifndef LAZURITE_IDE
		ACCESS_PUSH(2);
#endif

		macl.hopping.slave.ch_index++;
		if(macl.hopping.slave.ch_index >= macl.hopping.slave.sync->payload.size) {
			macl.hopping.slave.ch_index = 0;
		}
		macl_hopping_slave_phy_setup();
		/*
			 phy_stop();
			 phy_setup(macl.pages,macl.hopping.slave.sync->payload.ch_list[macl.hopping.slave.ch_index],macl.txPower,macl.antsw);
			 */

/*
#ifdef LAZURITE_IDE
		Serial.print("timesync_slave_isr: ");
		Serial.print_long((long)millis(),DEC);
		Serial.print(",");
		Serial.print_long((long)macl.hopping.slave.ch_index,DEC);
		Serial.print(",");
		Serial.print_long((long)macl.hopping.slave.sync->payload.ch_list[macl.hopping.slave.ch_index],DEC);
		Serial.print(",");
		Serial.println_long((long)macl.bit_params.sync_enb,DEC);
#endif
*/

		phy_sint_handler(macl_rxfifo_handler);
		phy_rxstart();
		macl.condition=SUBGHZ_ST_RX_STARTED;

		macl.hoppingdone = true;
		HAL_wake_up_interruptible(&macl.que);
	} else {
		macl.bit_params.hopping_sync_slave_irq = true;
	}
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif
	return;
}

static void macl_txdone(void) {
	switch(macl.hopping_state) {
		case SUBGHZ_ST_HOPPING_HOST_CMD_TX:
			// hoppingのsync_okコマンド送信。イベント完了してrxonする
			macl.hoppingdone = true;
			macl.hopping_state = SUBGHZ_ST_HOPPING_NOP;
		case SUBGHZ_ST_HOPPING_SLAVE_SYNC_REQ:
			// macl_search_gateway内でイベント終了を待つ
			phy_sint_handler(macl_rxfifo_handler);
			phy_rxstart();
			macl.condition=SUBGHZ_ST_RX_STARTED;
#ifdef LAZURITE_IDE
			Serial.println_long(__LINE__,DEC);
#endif
			break;
		case SUBGHZ_ST_HOPPING_NOP:
		default:
			// 通常の送信完了
			macl.txdone = true;
			macl.hopping_state = SUBGHZ_ST_HOPPING_NOP;
			if(macl.bit_params.txReserve == false) {
				if(macl.bit_params.hopping_sync_host_irq){
					macl_timesync_host_isr();
				} else if(macl.bit_params.hopping_sync_slave_irq){
					macl_timesync_slave_isr();
				} else if(macl.bit_params.rxOnEnable) {
					phy_sint_handler(macl_rxfifo_handler);
					phy_rxstart();
					macl.condition=SUBGHZ_ST_RX_STARTED;
#ifdef LAZURITE_IDE
					Serial.println_long(__LINE__,DEC);
#endif
				}
			}
			break;
	}
	return;
}

static void macl_rxdone(void) {
	macl.rxdone = true;
	if(macl.bit_params.txReserve == false) {
		if(macl.bit_params.hopping_sync_host_irq){
			macl_timesync_host_isr();
		} else if(macl.bit_params.hopping_sync_slave_irq){
			macl_timesync_slave_isr();
		} else if(macl.bit_params.rxOnEnable) {
			phy_sint_handler(macl_rxfifo_handler);
			phy_rxstart();
			macl.condition=SUBGHZ_ST_RX_STARTED;
#ifdef LAZURITE_IDE
			Serial.println_long(__LINE__,DEC);
#endif
		}
	}
	return;
}

static bool macl_timesync_search_gateway(void){
	uint8_t ch_index;
	uint8_t ch_scan_count = 0;
	uint8_t ch_scan_cycle = SUBGHZ_HOPPING_SEARCH_CYCLE;
	struct mac_fc_alignment fc;
	union {
		macl_timesync_search_request_raw16 *req16;
		macl_timesync_search_request_raw64 *req64;
	} req;
	union {
		//macl_timesync_params_raw16 *res16;		support only 64bit addressing mode
		macl_timesync_params_raw64 *res64;
	} res;

#ifndef LAZURITE_IDE
	ACCESS_PUSH(3);
#endif
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
	if(macl.parent->tx.dst.addr_type == 3) {
		req.req64 = (macl_timesync_search_request_raw64 *)macl.phy->out.data;
		req.req64->mac_header = 0xEC03;
		req.req64->seq = (uint8_t) rand();
		req.req64->panid = 0xFFFF;
		memcpy(req.req64->dst,macl.parent->tx.dst.addr.ieee_addr,8);
		memcpy(req.req64->src,macl.parent->my_addr.ieee_addr,8);
		req.req64->payload.cmd = SUBGHZ_HOPPING_SYNC_REQUEST;
		memcpy(req.req64->payload.id,SUBGHZ_HOPPING_ID,sizeof(SUBGHZ_HOPPING_ID));;
		macl.phy->out.len= sizeof(macl_timesync_search_request_raw64);
	} else {
		req.req16 = (macl_timesync_search_request_raw16 *)macl.phy->out.data;
		req.req16->mac_header = 0xE803;
		req.req16->seq = (uint8_t) rand();
		if((macl.parent->tx.dst.addr_type == 2) && (macl.parent->tx.dst.panid.enb)) {
			req.req16->panid = macl.parent->tx.dst.panid.data;
			req.req16->dst = macl.parent->tx.dst.addr.short_addr;
		} else {
			req.req16->panid = 0xFFFF;
			req.req16->dst = 0xFFFF;
		}
		memcpy(req.req16->src,macl.parent->my_addr.ieee_addr,8);
		req.req16->payload.cmd = SUBGHZ_HOPPING_SYNC_REQUEST;
		memcpy(req.req16->payload.id,SUBGHZ_HOPPING_ID,sizeof(SUBGHZ_HOPPING_ID));;
		macl.phy->out.len= sizeof(macl_timesync_search_request_raw16);
	}

	macl.bit_params.sync_enb = false;
	macl.hopping_state = SUBGHZ_ST_HOPPING_SLAVE_SYNC_REQ;
	macl.hopping.slave.sync = NULL;
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
			macl.phy->in.len = 0;
			phy_stop();
			phy_setup(macl.pages,HOPPING_SEARCH_LIST[ch_index],macl.txPower,macl.antsw);
/*
#ifdef LAZURITE_IDE
			Serial.print("timesync_search_gateway: ");
			Serial.print_long((long)ch_index,DEC);
			Serial.print(",");
			Serial.print_long((long)HOPPING_SEARCH_LIST[ch_index],DEC);
			Serial.print(",");
			Serial.println_long((long)macl.bit_params.sync_enb,DEC);
#endif
*/
			// subghz_send
			phy_txpre(MANUAL_TX);
			HAL_GPIO_enableInterrupt();
			macl.condition=SUBGHZ_ST_CCA;
#ifdef LAZURITE_IDE
			Serial.println_long(__LINE__,DEC);
#endif
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
				res.res64 = (macl_timesync_params_raw64 *) macl.parent->rx.raw->data;
				if(res.res64->payload.cmd == SUBGHZ_HOPPING_SYNC_OK) {
					res.res64->payload.sync_time = HAL_millis()-res.res64->payload.sync_from;
					memcpy(cmd_data_buf,macl.parent->rx.raw->data,macl.parent->rx.raw->len);
					macl.bit_params.sync_enb = true;
					macl.hopping.slave.sync = (macl_timesync_params_raw64 *)cmd_data_buf;
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
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif
	return macl.bit_params.sync_enb;
}

static void macl_dummy_handler(void)
{
	macl.condition = SUBGHZ_ST_DUMMY;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
	return;
}
static void macl_rxdone_abort_handler(void) {
#ifndef LAZURITE_IDE
	ACCESS_PUSH(4);
#endif
	macl_rxdone();
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif
	HAL_wake_up_interruptible(&macl.que);
}
static void macl_rxfifo_handler(void)
{
	int status;
#ifndef LAZURITE_IDE
	ACCESS_PUSH(5);
#endif
	macl.rxdone = false;
	macl.condition=SUBGHZ_ST_RX_FIFO;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
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
			if((macl.bit_params.promiscuousMode) ||
					((macl.phy->in.data[0]&0x07) == IEEE802154_FC_TYPE_CMD) ||
					((macl.phy->in.data[0]&0x07) == IEEE802154_FC_TYPE_DATA)) {
				macl_rxdone_handler();
				break;
			} else {
				// Disposal packet continue to CRC_ERROR
			}
		case CRC_ERROR:		// rxdone
		default:			// error
			macl.condition=SUBGHZ_ST_RX_START;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
#if !defined(LAZURITE_IDE) && defined(DEBUG)
			printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
			macl_rxdone();
			break;
	}
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif
	HAL_wake_up_interruptible(&macl.que);
	return;
}

static void macl_rxdone_handler(void)
{
	int status;
	bool isAck;

	macl.condition=SUBGHZ_ST_RX_DONE;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
	status = macl_rx_irq(&isAck);

	if (macl.bit_params.promiscuousMode) {
		macl.status = STATUS_OK;
		macl_rxdone();
		macl_rx_irq(NULL);
		goto end;
	}
	if (status != STATUS_OK) {
		macl.status = status;
		macl_rxdone();
		macl_rx_irq(NULL);
		goto end;
	}
	if(isAck){
#ifdef JP
		if(macl.ch >= 33) {
			status = macl_total_transmission_time(macl.phy->out.len+TX_TTL_OFFSET);
			if(status != STATUS_OK) {
				macl.status = status;
				macl_rx_irq(NULL);
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
#ifdef LAZURITE_IDE
		Serial.println_long(__LINE__,DEC);
#endif
	} else {
		macl.status = STATUS_OK;
		macl_rx_irq(NULL);
		if(macl.hoppingdone) macl_rxdone();			// hopping処理中は受信設定しない
		macl.rxdone = true;											// 受信処理自体は終了にしておく
	}
end:
	return;
}

static void macl_txfifo_handler(void)
{
	FIFO_STATE fifo_state;
#ifndef LAZURITE_IDE
	ACCESS_PUSH(6);
#endif
	macl.condition = SUBGHZ_ST_TX_FIFO;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
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
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif
	return;
}

static void macl_ack_txdone_handler(void)
{
	phy_timer_stop();
	if(macl.condition==SUBGHZ_ST_ACK_TX){
		macl.condition=SUBGHZ_ST_ACK_TX_DONE;
#ifdef LAZURITE_IDE
		Serial.println_long(__LINE__,DEC);
#endif
#ifndef LAZURITE_IDE
		ACCESS_PUSH(7);
#endif
		phy_txdone();
		macl_rxdone();
#if !defined(LAZURITE_IDE) && defined(DEBUG)
		printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
		macl.status = STATUS_OK;
		macl_rx_irq(NULL);				// rx callback
#ifndef LAZURITE_IDE
		ACCESS_POP();
#endif
	} else {
		if(macl.rxdone == false) {
			macl.status = STATUS_OK;
			macl_rx_irq(NULL);				// rx callback
		}
		macl.rxdone = true;
	}
	HAL_wake_up_interruptible(&macl.que);

	return;
}
static void macl_ack_txdone_abort_handler(void)
{
	static const char s1[] = "macl_txdone_abort_handler";
	phy_timer_stop();
	if(macl.condition==SUBGHZ_ST_ACK_TX){
#ifndef LAZURITE_IDE
		ACCESS_PUSH(8);
#endif
		if(phy_txfifo() == FIFO_DONE) {
			macl.status = STATUS_OK;
		} else {
			alert(s1);
			macl.status=-EDEADLK;
		}
		phy_txdone();
		macl_rx_irq(NULL);				// rx callback
		macl_rxdone();
#ifndef LAZURITE_IDE
		ACCESS_POP();
#endif
	} else {
		if(macl.rxdone == false) {
			macl.status=-EDEADLK;
			macl_rx_irq(NULL);				// rx callback
		}
	}
	macl.rxdone = true;
	HAL_wake_up_interruptible(&macl.que);
	return;
}

static void macl_ccadone_handler(void)
{
	int status = STATUS_OK;
	uint8_t cca_idle;
#ifndef LAZURITE_IDE
	ACCESS_PUSH(9);
#endif

#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif

	macl.condition=SUBGHZ_ST_CCA_DONE;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
	phy_timer_stop();

	cca_idle = phy_ccadone();
	phy_timer_start(160,macl_txdone_abort_handler);
	phy_sint_handler(macl_txfifo_handler);
	status = phy_txstart();
	if(status != STATUS_OK) {
		macl.status = status;
		if(macl.tx_callback) macl.tx_callback(0,macl.status);
		macl_txdone();
	}
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif
	HAL_wake_up_interruptible(&macl.que);
	return;
}

static void macl_ccadone_abort_handler(void)
{
	uint8_t ccadone;
#ifndef LAZURITE_IDE
	ACCESS_PUSH(10);
#endif
	phy_timer_stop();
	macl.status = -EBUSY;
	macl.condition=SUBGHZ_ST_CCA_ABORT;

	ccadone = phy_ccadone();
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%02x\n",__func__,__LINE__,ccadone);
#endif
	if(macl.tx_callback) macl.tx_callback(0,macl.status);
	macl_txdone();
	HAL_wake_up_interruptible(&macl.que);
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif
	return;
}

static void macl_txdone_abort_handler(void)
{
	static const char s1[] = "macl_txdone_abort_handler";
#ifndef LAZURITE_IDE
	ACCESS_PUSH(11);
#endif
	macl.condition=SUBGHZ_ST_TX_ABORT;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
	phy_timer_stop();
	alert(s1);
	phy_monitor();
	phy_stop();
	//phy_monitor();
	macl.status = -EDEADLK;
	if(macl.tx_callback) macl.tx_callback(0,macl.status);

	macl_txdone();
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif
	HAL_wake_up_interruptible(&macl.que);
}

static void macl_txdone_handler(void)
{
	uint8_t ack_req;
	uint16_t ack_timeout;
#ifndef LAZURITE_IDE
	ACCESS_PUSH(12);
#endif
	macl.condition=SUBGHZ_ST_TX_DONE;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
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
		macl_txdone();
	}
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif
	HAL_wake_up_interruptible(&macl.que);
}

static void macl_ack_rxdone_handler(void) {
	FIFO_STATE rxtype;
	bool isAck;
#ifndef LAZURITE_IDE
	ACCESS_PUSH(13);
#endif
	macl.condition=SUBGHZ_ST_ACK_RX_DONE;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
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
				macl_txdone();
			} else {
				macl_ack_rxdone_abort_handler();
			}
			break;
		case CRC_ERROR:
		default:
			macl.condition = SUBGHZ_ST_ACK_RX_CRC;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
			macl_ack_rxdone_abort_handler();
			break;
	}
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif
	HAL_wake_up_interruptible(&macl.que);
}

static void macl_ack_rxdone_abort_handler(void) {
	static const char s1[] = "macl_ack_txdone txpre error";
#ifndef LAZURITE_IDE
	ACCESS_PUSH(14);
#endif
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
		switch(macl.ch) {
			case SUBGHZ_HOPPING_TS_S:
				macl_hopping_slave_phy_setup();
				break;
			case SUBGHZ_HOPPING_TS_H:
				if(macl.hopping_state == SUBGHZ_ST_HOPPING_HOST_CMD_TX) {
					macl_timesync_params_raw64 *res;
					res = (macl_timesync_params_raw64 *)macl.phy->out.data;
					res->payload.sync_from = HAL_millis() - macl.hopping.host.sync_time;
				}
				break;
			default:
				break;
		}
		macl.status = phy_txpre(MANUAL_TX);
		if(macl.status != STATUS_OK) {
			alert(s1);
			macl.bit_params.sync_enb = false;
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
		macl.bit_params.sync_enb = false;
		macl.status = -ETIMEDOUT;
		goto error;
	}
error:
	if(macl.tx_callback) macl.tx_callback(0,macl.status);
	macl_txdone();
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif
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
#ifndef LAZURITE_IDE
	memset(task,0,sizeof(task));
#endif
	macl.parent = (struct mach_param*) parent;
	macl.txdone = true;
	macl.rxdone = true;
	macl.hoppingdone = true;
	macl.bit_params.txReserve = false;
	macl.condition = SUBGHZ_ST_INIT;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
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
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
	return &macl;
error:
	macl.condition = SUBGHZ_ST_INIT_FAIL;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
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
#ifndef LAZURITE_IDE
	ACCESS_PUSH(15);
#endif
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
	macl.condition=SUBGHZ_ST_RX_START;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
	switch(macl.ch) {
		case SUBGHZ_HOPPING_TS_H:
			phy_timer_stop();
			HAL_GPIO_disableInterrupt();
			macl.hopping.host.ch_index=0;
			ch = HOPPING_SEARCH_LIST[macl.hopping.host.ch_index];
			phy_stop();
			phy_setup(macl.pages,ch,macl.txPower,macl.antsw);
/*
#ifdef LAZURITE_IDE
			Serial.print("macl_start: ");
			Serial.print_long((long)macl.hopping.host.ch_index,DEC);
			Serial.print(",");
			Serial.print_long((long)HOPPING_SEARCH_LIST[macl.hopping.host.ch_index],DEC);
			Serial.print(",");
			Serial.println_long((long)macl.bit_params.sync_enb,DEC);
#endif
*/
			macl.hopping.host.sync_time = HAL_millis();
			timer4.set(SUBGHZ_HOPPING_CH_DURATION,macl_timesync_host_isr);
			timer4.start();
			HAL_GPIO_enableInterrupt();
			break;
		case SUBGHZ_HOPPING_TS_S:
			if(macl.bit_params.sync_enb == false) {
				if(macl_timesync_search_gateway() == true) {
					macl.bit_params.timer_sync = false;
					timer4.set(macl_hopping_slave_phy_setup(),macl_timesync_slave_isr);
					timer4.start();
				} else {
					return -ENOPROTOOPT;
				}
			} else {
				macl.bit_params.timer_sync = false;
				timer4.set(macl_hopping_slave_phy_setup(),macl_timesync_slave_isr);
				timer4.start();
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
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
	HAL_GPIO_enableInterrupt();
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif
	return status;
}

int	macl_stop(void)
{
	int status=STATUS_OK;
#ifndef LAZURITE_IDE
	ACCESS_PUSH(16);
#endif
	macl.condition=SUBGHZ_ST_STOP;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
	macl.bit_params.rxOnEnable = 0;
	timer4.stop();
	macl.bit_params.timer_sync = false;
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif
	HAL_GPIO_disableInterrupt();
	phy_stop();
	phy_timer_stop();
	phy_sint_handler(macl_dummy_handler);
	macl.condition=SUBGHZ_ST_STANDBY;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif
	return status;
}

int	macl_xmit_sync(BUFFER *buff) {
	static const char s0[] = "rxdone abort in tx";
	uint32_t time;
	macl.bit_params.txReserve = true;

	// 受信完了待ち時間
	// 1秒だと送信処理と受信のACK送信完了処理がぶつかることがあるので2秒に修正した
#ifdef NOT_INLINE
	//uint32_t HAL_wait_event_interruptible_timeout(wait_queue_head_t *q,volatile int *condition,uint32_t ms)
	{
		volatile uint32_t st_time = millis();
		volatile uint32_t status;
		const uint32_t ms = 2000L;
		do {
			status = st_time+ms-millis();
			if(status > ms) {
				status = 0;
			}
		} while(((macl.rxdone & macl.hoppingdone) == false) && (status > 0));
		time = status;
	}
#else
	time =  HAL_wait_event_interruptible_timeout(macl.que,macl.rxdone&macl.hoppingdone,2000L);
	printk(KERN_INFO"%s %d %d %d\n",__func__,__LINE__,time,macl.condition);
	macl.condition=SUBGHZ_ST_TX_START;
#endif
#ifndef LAZURITE_IDE
	ACCESS_PUSH(17);
#endif
	macl.txdone = false;
	macl.rxdone = true;
	macl.hoppingdone = true;
	macl.bit_params.txReserve = false;
	HAL_GPIO_disableInterrupt();
	phy_stop();
	phy_timer_stop();
	if(time == 0) {
		alert(s0);
	}
	switch(macl.ch) {
		case SUBGHZ_HOPPING_TS_S:
			// 時刻同期
			if(macl.bit_params.sync_enb == false) {
				if(macl_timesync_search_gateway() == false) {
					macl.status = -ENOPROTOOPT;
					goto error;
				}
			}
			// 時刻同期の結果に基づき使用するCHを計算し周波数設定を行う。
			macl_hopping_slave_phy_setup();
			break;
		case SUBGHZ_HOPPING_TS_H:
			macl_hopping_host_phy_setup();
			break;
		default:
			break;
	}
	macl.status=STATUS_OK;
	macl.phy->out = *buff;
	macl.resendingNum = 0;
	macl.ccaCount=0;
	macl.sequenceNum= buff->data[2];
	macl.tx_callback = NULL;
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif

	macl.status = macl_total_transmission_time(macl.phy->out.len+TX_TTL_OFFSET);
	if (macl.status != STATUS_OK){
		goto error;
	}
#ifndef LAZURITE_IDE
	ACCESS_PUSH(18);
#endif

	phy_txpre(MANUAL_TX);
	macl_cca_setting();
	macl.condition=SUBGHZ_ST_CCA;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
	HAL_GPIO_enableInterrupt();
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif

#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif

#ifdef NOT_INLINE
	time =  HAL_wait_event_interruptible_timeout(&macl.que,&macl.txdone,1000L);
#else
	time =  HAL_wait_event_interruptible_timeout(macl.que,macl.txdone,1000L);
#endif
#ifndef LAZURITE_IDE
	ACCESS_PUSH(19);
#endif
	if(time == 0) {
		macl_txdone();
		macl.status = -EDEADLK;
	}
error:
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif
	return macl.status;
}

int	macl_xmit_async(BUFFER *buff,void (*callback)(uint8_t rssi, int status))
{
	static const char s0[] = "rxdone abort in tx";
	uint32_t time;
#ifndef LAZURITE_IDE
	ACCESS_PUSH(20);
#endif
	macl.bit_params.txReserve = true;

#ifdef NOT_INLINE
	time =  HAL_wait_event_interruptible_timeout(&macl.que,&macl.rxdone,2000L);
#else
	time =  HAL_wait_event_interruptible_timeout(macl.que,macl.rxdone,2000L);
#endif
	macl.condition=SUBGHZ_ST_TX_START;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#else
	printk(KERN_INFO"%s %d %d\n",__func__,__LINE__,macl.condition);
#endif
	macl.txdone = false;
	macl.rxdone = true;
	macl.hoppingdone = true;
	macl.bit_params.txReserve = false;
	if(time == 0) {
		alert(s0);
	}
	HAL_GPIO_disableInterrupt();
	phy_stop();
	phy_timer_stop();

	macl.status=STATUS_OK;
	macl.phy->out = *buff;
	macl.resendingNum = 0;
	macl.ccaCount=0;
	macl.sequenceNum= buff->data[2];
	macl.tx_callback = callback;

	macl.status = macl_total_transmission_time(macl.phy->out.len+TX_TTL_OFFSET);
	if (macl.status != STATUS_OK){
		macl_txdone();
		goto error;
	}

	phy_txpre(MANUAL_TX);
	macl_cca_setting();
	macl.condition=SUBGHZ_ST_CCA;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s,%d,%s\n",__func__,__LINE__,macl_state_to_string(macl.condition));
#endif

error:
#ifndef LAZURITE_IDE
	ACCESS_POP();
#endif
	HAL_GPIO_enableInterrupt();
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
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif

	macl.pages = page;
	macl.ch = ch;
	macl.antsw = antsw;

	if (mbm == 100){ 
		macl.txPower = 1;
	}else {
		macl.txPower = 20;
	}
	if(macl.ch < SUBGHZ_HOPPING) {
		phy_stop();
		status = phy_setup(macl.pages,macl.ch,macl.txPower,macl.antsw);
	}
	macl.condition = SUBGHZ_ST_STANDBY;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
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
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
	phy_sleep();
	macl.condition = SUBGHZ_ST_SLEEPED;
#ifdef LAZURITE_IDE
	Serial.println_long(__LINE__,DEC);
#endif
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

