/* bp3596.c - SDK API
 *
 * Copyright (c) 2015  Communication Technology Inc.,
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

#define Version 1,4  /* バージョン番号: Major, Miner */


#ifdef LAZURITE_IDE
#include <stdint.h>
#include <string.h>
#else
//#include "../others/stdint.h"
#include <linux/string.h>
#include <linux/kernel.h>
#endif

#include "../core/ml7396.h"
#include "../core/endian.h"
#include "../core/ieee802154.h"
#include "bp3596.h"
#include "../phy.h"
//#include "mac.h"
#include "aes.h"

#ifdef DEBUG_AES
#include "Serial.h"
#endif

/* 内部エラーコード
 */
#define BP3596_STATUS_UNKNOWN INT_MIN  /* システムエラー */

/* 送受信バッファサイズ
 */
#define RXBUFFER_CAPACITY ML7396_BUFFER_CAPACITY  /* 受信バッファ */
#define TXBUFFER_CAPACITY ML7396_BUFFER_CAPACITY  /* 送信バッファ */

/* APIグローバル変数
 */
typedef struct {
	uint8_t *buf;
	int16_t size;
}RF_Buffer;
static struct {
	bool flag;
	MAC_PANID myPanid;
	MAC_ADDR myAddr;
	MAC_PANID dstPanid;
	MAC_ADDR dstAddr;
	PHY_INIT_PARAM phy;
	uint8_t seq;
    struct {
        //ML7396_Buffer buffer;
		RF_Buffer buf;
        void (*done)(const uint8_t *data, uint8_t rssi, int status);  /* コールバック関数 */
    } rx;
    struct {
        //ML7396_Buffer buffer;
		RF_Buffer buf;
        void (*done)(uint8_t rssi, int status);  /* コールバック関数 */
    } tx;
} api = {
    false  /* 未初期化設定を addr==NUKLL で判定 */
};


/* 受信完了コールバック関数 */
static void rxdone(ML7396_Buffer *buffer) {
    if (api.rx.done)
        api.rx.done((void *)buffer->data, buffer->opt.common.ed, buffer->status);  /*@ ED値をそのままrssiとして返しているが変換が必要? */
}

/* 送信完了コールバック関数 */
static void txdone(ML7396_Buffer *buffer) {
    if (api.tx.done)
        api.tx.done(buffer->opt.common.ed, buffer->status);  /*@ ED値をそのままrssiとして返しているが変換が必要? */
}

/* 受信フィルタ関数 */

/******************************************************************************/
/*! @brief rxfilter
  @issue                 not in use??
 */
/******************************************************************************/
/*
static int rxfilter(const MAC_Header *header) {
    int filter = 0;

    if (
		// (api.rx.filter.dstpanid == 0 && api.rx.filter.dstaddr0 == 0 && api.rx.filter.dstaddr1 == 0) ||
        (header->dstpanid == api.rx.filter.dstpanid) ||
        (header->dstaddr == api.rx.filter.dstaddr0) ||
        (header->dstaddr == api.rx.filter.dstaddr1) )
        filter = !0;
    return filter;
}
*/
/* 送信データ作成
 *
 * header構造体を解析して下記情報をdataのMACヘッダに埋め込む:
 *  フレームコントロールのPANID圧縮
 *  フレームコントロールのシーケンス番号圧縮
 *  フレームコントロールの受信アドレスモード
 *  フレームコントロールの送信アドレスモード
 *  シーケンス番号
 *  宛て先PANID
 *  宛て先アドレス
 *  送り元PANID
 *  送り元アドレス
 *
 *  data: 送信データバッファ
 *  size: 送信データバッファサイズ
 *  *header: 送信データに展開するヘッダ情報
 *  戻り値: ペイロードデータの先頭アドレス
 *          戻り値 - data = MACヘッダサイズ
 *          MACヘッダサイズ + ペイロードサイス = 送信データサイズ
 *
 */

	/******************************************************************************/
	/*! @brief make mac header
	  @param[in] *data start pointer of output buffer
	  @param[in] *size length of header
	  @param[in] *header  pointer of mac header
	     mandatory
		 header->addr_type
		 header->dstpanid
		 header->srcpanid
		 header->dstaddr
		 header->srcaddr
		 header->fc
		 	frame_type
			sec_enb
			pending
			ack_reg (1: auto, 0: no ack)
			ielist
	  @return    false= invalid data, true valid data
	  @exception none
	  @issue     move to mac
	  @issue     check ack condision
	       | dstpanid | dstaddr | srcpanid | srcaddr | ack     | tx mode   |
		   |----------+---------+----------+---------+---------|-----------|
		   |   ff     |   ff    |   ---    |  ---    | no ack  | broadcast |
		   |  ---     |   ff    |   ---    |  ---    | no ack  | groupcast |
		   |  ---     |   no    |   ---    |  ---    |  ack    | unicast   |
		   |   ff     |  64bit  |          |  ---    |  ack    | unicast   |
		   | ff/no    |  0/8/16 |          |  ---    | no ack  |  error    |
		   |  ---     |  ---    |    ff    |  ---    |  ack    | unicast   |
		   |  ---     |  ---    |   ---    |   ff    |  ack    | unicast   |
		   |  ---     |  ---    |   ---    |   no    |  ack    | unicast   |
	 ******************************************************************************/
static bool make_mac_header(uint8_t *data, uint16_t *size, MAC_Header *header) {
	uint16_t offset=2;
	bool isValid=false;
	bool broadcast = true;
	int i;
	// input param = addr_mode
	// enb_addr_bit		4bit:	dstaddr
	// 					3bit:	srcaddr
	// 					2bit:	panid_comp
	// 					1bit:	dstpanid
	// 					0bit:	srcpanid
	const uint8_t enb_addr_bit[] = {0x00,0x06,0x09,0x0c,0x12,0x14,0x1a,0x1c};
	const uint8_t addr_len[] = {0x00,0x01,0x02,0x08};

	// set panid comp
	SET_PANID_COMP(header->fc,((enb_addr_bit[header->addr_type] & 0x04) ? 1:0));

	// sequence number
	if(!GET_SEQ_COMP(header->fc)) {
		data[offset] = header->seq,offset++;
	}

	// dst panid
	if(enb_addr_bit[header->addr_type] & 0x02)
	{
		if(header->dstpanid.enb == 0)
		{
			isValid = false;
			goto error;
		} else {
    		u2v16_set(header->dstpanid.panid, data+offset), offset+=2;
		}
	}

	// dst addr
	if(enb_addr_bit[header->addr_type] & 0x10)
	{
		int i;
		bool broadcast = true;
		switch(header->dstaddr.mode)
		{
			case 0:
				isValid = false;
				goto error;
				break;
			case 1:
				if((header->dstpanid.panid == 0xffff) ||(header->dstpanid.enb == false))
				{
					isValid = false;
					goto error;
				}
				data[offset] = header->dstaddr.addr.addr8,offset++;
				if(header->dstaddr.addr.addr8 != 0xff) broadcast = false;
				break;
			case 2:
				if((header->dstpanid.panid == 0xffff) ||(header->dstpanid.enb == false))
				{
					isValid = false;
					goto error;
				}
				u2v16_set(header->dstaddr.addr.addr16, data+offset), offset+=2;
				if(header->dstaddr.addr.addr16 != 0xffff) broadcast = false;
				break;
			case 3:
				break;
				for(i = 0;i<addr_len[header->dstaddr.mode];i++)
				{
					data[offset] = header->dstaddr.addr.addr64[i],offset++;
					if(header->dstaddr.addr.addr64[i] != 0xff) broadcast = false;
				}
		}
		if(broadcast) SET_ACK_REQ(header->fc,0);
	}

	// src panid
	if(enb_addr_bit[header->addr_type] & 0x01)
	{
		if(header->srcpanid.enb == 0)
		{
			isValid = false;
			goto error;
		} else {
			u2v16_set(header->srcpanid.panid, data+offset), offset+=2;
		}
	}
	// src addr
	if(enb_addr_bit[header->addr_type] & 0x08)
	{
		switch(header->srcaddr.mode)
		{
			case 0:
				isValid = false;
				goto error;
				break;
			case 1:
				data[offset] = header->srcaddr.addr.addr8,offset++;
				if(header->srcaddr.addr.addr8 != 0xff) broadcast = false;
				break;
			case 2:
				u2v16_set(header->srcaddr.addr.addr16, data+offset), offset+=2;
				if(header->srcaddr.addr.addr16 != 0xffff) broadcast = false;
				break;
			case 3:
				for(i = 0;i<addr_len[header->dstaddr.mode];i++)
				{
					data[offset] = header->dstaddr.addr.addr64[i],offset++;
					if(header->srcaddr.addr.addr64[i] != 0xff) broadcast = false;
				}
				break;
		}
	}
	isValid = true;

#if 0
	/* IEEE 802.15.4e フレームのビーコンとデータ、ACK以外は未対応 */
	switch (header->fc & (IEEE802154_FC_IEEE802154_MASK|IEEE802154_FC_TYPE_MASK)) {
		case IEEE802154_FC_IEEE802154_E|IEEE802154_FC_TYPE_BEACON:
		case IEEE802154_FC_IEEE802154_E|IEEE802154_FC_TYPE_DATA:
		case IEEE802154_FC_IEEE802154_E|IEEE802154_FC_TYPE_ACK:
			break;
		default:
			goto error;
	}
	/* ヘッダ情報から宛て先/送り元のPANID/アドレスとシーケンス番号のフィールドサイズを取得 */
	fc.dstaddrmode = header->dstaddr == ML7396_HEADER_ADDRNONE ? IEEE802154_FC_DAMODE_NONE : IEEE802154_FC_DAMODE_SHORT;
	fc.srcaddrmode = header->srcaddr == ML7396_HEADER_ADDRNONE ? IEEE802154_FC_SAMODE_NONE : IEEE802154_FC_SAMODE_SHORT;
	switch (fc.dstaddrmode | fc.srcaddrmode) {  /* 規格上無効な組み合わせは未対応 */
		case IEEE802154_FC_DAMODE_NONE|IEEE802154_FC_SAMODE_NONE:
			if (header->dstpanid == ML7396_HEADER_PANIDNONE && header->srcpanid == ML7396_HEADER_PANIDNONE)
				fc.panidcomps = 0;
			else if (header->dstpanid != ML7396_HEADER_PANIDNONE && header->srcpanid == ML7396_HEADER_PANIDNONE)
				fc.panidcomps = IEEE802154_FC_PANID_COMPS;
			else
				goto error;
			break;
		case IEEE802154_FC_DAMODE_NONE|IEEE802154_FC_SAMODE_SHORT:
			if (header->dstpanid == ML7396_HEADER_PANIDNONE && header->srcpanid == ML7396_HEADER_PANIDNONE)
				fc.panidcomps = IEEE802154_FC_PANID_COMPS;
			else if (header->dstpanid == ML7396_HEADER_PANIDNONE && header->srcpanid != ML7396_HEADER_PANIDNONE)
				fc.panidcomps = 0;
			else
				goto error;
			break;
		case IEEE802154_FC_DAMODE_SHORT|IEEE802154_FC_SAMODE_NONE:
		case IEEE802154_FC_DAMODE_SHORT|IEEE802154_FC_SAMODE_SHORT:
			if (header->dstpanid == ML7396_HEADER_PANIDNONE && header->srcpanid == ML7396_HEADER_PANIDNONE)
				fc.panidcomps = IEEE802154_FC_PANID_COMPS;
			else if (header->dstpanid != ML7396_HEADER_PANIDNONE && header->srcpanid == ML7396_HEADER_PANIDNONE)
				fc.panidcomps = 0;
			else
				goto error;
			break;
		default:
			goto error;
	}
	fc.seqsuppress = header->seq == ML7396_HEADER_SEQNONE ? IEEE802154_FC_SEQ_SUPPRESS : 0;
	if (size < 2)
		goto error;
	/* MACヘッダのフィールドコントロールに宛て先/送り元のPANID/アドレスとシーケンス番号のフィールドサイズ情報を反映 */
	header->fc &= ~(IEEE802154_FC_PANID_COMPS|IEEE802154_FC_SEQ_SUPPRESS|IEEE802154_FC_DAMODE_MASK|IEEE802154_FC_SAMODE_MASK);
	header->fc |= fc.dstaddrmode | fc.srcaddrmode | fc.panidcomps | fc.seqsuppress;
	u2v16_set(header->fc, data), data += 2, size -= 2;
	/* MACヘッダに宛て先/送り元のPANID/アドレスとシーケンス番号を付加 */
	if (!fc.seqsuppress) {
		if (size < 1)
			goto error;
		*data++ = header->seq, --size;
	}
	if (header->dstpanid != ML7396_HEADER_PANIDNONE) {
		if (size < 2)
			goto error;
		u2v16_set(header->dstpanid, data), data += 2, size -= 2;
	}
	if (header->dstaddr != ML7396_HEADER_ADDRNONE) {
		if (size < 2)
			goto error;
		u2v16_set(header->dstaddr, data), data += 2, size -= 2;
	}
	if (header->srcpanid != ML7396_HEADER_PANIDNONE) {
		if (size < 2)
			goto error;
		u2v16_set(header->srcpanid, data), data += 2, size -= 2;
	}
	if (header->srcaddr != ML7396_HEADER_ADDRNONE) {
		if (size < 2)
			goto error;
		u2v16_set(header->srcaddr, data), data += 2, size -= 2;
	}
	/* ペイロードの先頭アドレスを返す */
	payload = data;
#endif
error:
	return isValid;
}


int BP3596_reset(void) {
	int status = BP3596_STATUS_UNKNOWN;
	//static uint8_t rxdata[RXBUFFER_CAPACITY], txdata[TXBUFFER_CAPACITY];  /* 送受信バッファ */

	ml7396_reset();
	memset(&api, 0, sizeof(api));  /* API共有データをクリア */
	/* 受信バッファ初期化 */
	api.rx.buffer.data = rxdata;
	api.rx.buffer.capacity = RXBUFFER_CAPACITY;
	api.rx.buffer.opt.rx.done = rxdone;
	// @issue is it in use?
	api.rx.buffer.opt.rx.next = &api.rx.buffer;
	/*	does not use software filter
	// @issue need to check
#ifndef SNIFFER
	api.rx.buffer.opt.rx.filter = rxfilter;
#endifo*/
	// initializing tx buffer
	api.tx.buffer.data = txdata;
	api.tx.buffer.capacity = TXBUFFER_CAPACITY;
	api.tx.buffer.opt.tx.done = txdone, api.tx.buffer.opt.tx.next = NULL;
	// initializing address
	api.rx.srcpanid.enb = false;
	api.rx.srcaddr.mode = IEEEE802154_ADDR_NONE;
	api.rx.dstpanid.enb = false;
	api.rx.dstaddr.mode = IEEEE802154_ADDR_NONE;
	// Initialize sequence number
	api.seq = 0;

	status = BP3596_STATUS_OK;

	return status;
}

int BP3596_setup(uint8_t channel, uint8_t rate, uint8_t txPower, uint8_t senseTime,
		uint8_t txRetry, uint16_t txInterval, uint16_t ccaWait ) {
	int status = BP3596_STATUS_UNKNOWN;
	struct {
		uint8_t channel;
		uint8_t rate;
		uint8_t txPower;
		uint16_t address;
	} setup;

	setup.channel = channel;
	setup.rate = rate, setup.txPower = txPower;
	if (ml7396_setup(&setup) < 0) {
		status = BP3596_STATUS_ERROR_PARAM;
		goto error;
	}
	api.addr = ml7396_myaddr(), *api.addr = setup.address;
	api.panID = ml7396_mypanid(), *api.panID = 0;
	/* 送信バッファ設定 */
	api.tx.buffer.opt.tx.ack.wait = txInterval, api.tx.buffer.opt.tx.ack.retry = txRetry;
	//  api.tx.buffer.opt.tx.cca.wait = 100, api.tx.buffer.opt.tx.cca.retry = senseTime;
	api.tx.buffer.opt.tx.cca.wait = ccaWait , api.tx.buffer.opt.tx.cca.retry = senseTime;
	status = BP3596_STATUS_OK;
error:
	return status;
}

int BP3596_getMyAddr(uint16_t *addr) {
	int status = BP3596_STATUS_UNKNOWN;

	if (addr == NULL) {
		status = BP3596_STATUS_ERROR_PARAM;
		goto error;
	}
	if (api.addr == NULL) {
		status = BP3596_STATUS_ERROR_STATE;
		goto error;
	}
	*addr = *api.addr;
	status = BP3596_STATUS_OK;
error:
	return status;
}

int BP3596_setMyPANID(uint16_t panID) {
	int status = BP3596_STATUS_UNKNOWN;

	if (api.addr == NULL) {
		status = BP3596_STATUS_ERROR_STATE;
		goto error;
	}
	*api.panID = panID;
	status = BP3596_STATUS_OK;
error:
	return status;
}

int BP3596_setFilter(uint16_t panID, uint16_t addr0, uint16_t addr1) {
	int status = BP3596_STATUS_UNKNOWN;

	api.rx.filter.dstpanid = panID;
	api.rx.filter.dstaddr0 = addr0;
	api.rx.filter.dstaddr1 = addr1;
	ml7396_setAddrFilter((uint8_t *)&api.rx.filter);
	status = BP3596_STATUS_OK;
	return status;
}

// 2016.03.14 tx send event
void BP3596_sendIdle(void)
{
	ml7396_txidle();
}

int BP3596_send(const void *data, uint16_t size,
		uint8_t addrType, uint16_t dstAddr, uint16_t dstPANID ) {
	int status = BP3596_STATUS_UNKNOWN;
	//static uint8_t seq = 0;
	MAC_Header header;
	uint8_t *payload;
	uint16_t mac_size;

	if (data == NULL || size == 0) {
		status = BP3596_STATUS_ERROR_PARAM;
		goto error;
	}
	if (api.addr == NULL) {
		status = BP3596_STATUS_ERROR_STATE;
		goto error;
	}
	header.fc = IEEE802154_FC_IEEE802154_E|IEEE802154_FC_TYPE_DATA|IEEE802154_FC_ACKREQ;
	header.addr_type = addrType;
	header.dstpanid.enb = true;
	header.dstpanid.panid = dstPANID;
	header.dstaddr.mode = dstAddr;
	header.dstaddr.addr.addr16 = IEEE802154_ADDR_SHORT;
	header.srcaddr.addr.addr16  = *api.addr;
	//header.dstpanid.enb = 0;
	//header.dstaddr.mode = 0;
	//header.srcpanid.enb = 0;
	//header.srcaddr.mode  =0;
	/*
	switch (addrType) {
		case 0:
			break;
		case 1:
			if (dstPANID == ML7396_HEADER_PANIDNONE) {
				status = BP3596_STATUS_ERROR_PARAM;
				goto error;
			}
			header.dstpanid = dstPANID;
			break;
		case 2:
			if (*api.addr == ML7396_HEADER_ADDRNONE ||
					*api.panID == ML7396_HEADER_PANIDNONE ) {
				status = BP3596_STATUS_ERROR_PARAM;
				goto error;
			}
			header.srcpanid = *api.panID;
			header.srcaddr  = *api.addr;
			break;
		case 3:
			if (*api.addr == ML7396_HEADER_ADDRNONE) {
				status = BP3596_STATUS_ERROR_PARAM;
				goto error;
			}
			header.srcaddr  = *api.addr;
			break;
		case 4:
			if (dstPANID == ML7396_HEADER_PANIDNONE ||
					dstAddr == ML7396_HEADER_ADDRNONE ) {
				status = BP3596_STATUS_ERROR_PARAM;
				goto error;
			}
			header.dstpanid = dstPANID;
			header.dstaddr  = dstAddr;
			break;
		case 5:
			if (dstAddr == ML7396_HEADER_ADDRNONE) {
				status = BP3596_STATUS_ERROR_PARAM;
				goto error;
			}
			header.dstaddr  = dstAddr;
			break;
		case 6:
			if (dstPANID == ML7396_HEADER_PANIDNONE ||
					dstAddr == ML7396_HEADER_ADDRNONE ||
					*api.addr == ML7396_HEADER_ADDRNONE ) {
				status = BP3596_STATUS_ERROR_PARAM;
				goto error;
			}
			if (dstAddr != 0xffff)
				header.fc |= IEEE802154_FC_ACKREQ;
			header.dstpanid = dstPANID;
			header.dstaddr  = dstAddr;
			header.srcaddr  = *api.addr;
			break;
		case 7:
			if (dstAddr == ML7396_HEADER_ADDRNONE ||
					*api.addr == ML7396_HEADER_ADDRNONE ) {
				status = BP3596_STATUS_ERROR_PARAM;
				goto error;
			}
			if (dstAddr != 0xffff)
				header.fc |= IEEE802154_FC_ACKREQ;
			header.dstaddr  = dstAddr;
			header.srcaddr  = *api.addr;
			break;
		default:
			status = BP3596_STATUS_ERROR_PARAM;
			goto error;
	}
	*/
	if (AES128_getStatus()){
		header.fc |= IEEE802154_FC_SECURITY;
	}
	if(!make_mac_header(api.tx.buffer.data, &mac_size, &header)) goto error;
	payload = api.tx.buffer.data + mac_size;
	api.tx.buffer.size = size + (payload - api.tx.buffer.data);
	if (api.tx.buffer.size > api.tx.buffer.capacity) {
		status = BP3596_STATUS_ERROR_PARAM;
		goto error;
	}
	if (AES128_getStatus()){
		uint8_t seq;
		uint8_t pad;

		if (header.fc&IEEE802154_FC_SEQ_SUPPRESS){
			seq = 0;
		}else{
			seq = header.seq;
		}

		pad = AES128_CBC_encrypt(payload, (uint8_t *)data, size, seq); 
		api.tx.buffer.size += pad;
#ifdef DEBUG_AES
		{
			uint8_t i;
			Serial.print(data);
			Serial.print("\r\n");
			for(i=0;i<size-1;i++)
			{
				Serial.print_long((long)*((uint8_t *)data+i),HEX);
			}
			Serial.print("\r\n");
			Serial.print("total,payload,pad,seq: ");
			Serial.print_long( api.tx.buffer.size, DEC);
			Serial.print(" ");
			Serial.print_long( size, DEC);
			Serial.print(" ");
			Serial.print_long( pad, DEC);
			Serial.print(" ");
			Serial.print_long( seq, DEC);
			Serial.print("\r\n");
			for(i=0;i<size+pad-1;i++)
			{
				Serial.print_long((long)*(payload+i),HEX);
			}
			Serial.print("\r\n");
		}
#endif
	}else{
		memcpy(payload, data, size);
	}
	if (ml7396_txstart(&api.tx.buffer) < 0) {
		status = BP3596_STATUS_ERROR_STATE;
		goto error;
	}
	status = BP3596_STATUS_OK;
error:
	return status;
}

int BP3596_sendRaw(const void *data, uint16_t size) {
	int status = BP3596_STATUS_UNKNOWN;

	if (data == NULL || size == 0) {
		status = BP3596_STATUS_ERROR_PARAM;
		goto error;
	}
	if (api.addr == NULL) {
		status = BP3596_STATUS_ERROR_STATE;
		goto error;
	}
	if (size > TXBUFFER_CAPACITY) {
		status = BP3596_STATUS_ERROR_PARAM;
		goto error;
	}
	memcpy(api.tx.buffer.data, data, size), api.tx.buffer.size = size;
	if (ml7396_txstart(&api.tx.buffer) < 0) {
		status = BP3596_STATUS_ERROR_STATE;
		goto error;
	}
	status = BP3596_STATUS_OK;
error:
	return status;
}

int BP3596_setFuncSendComplete(void (*sendComplete)(uint8_t rssi, int status)) {
	int status = BP3596_STATUS_UNKNOWN;

	if (sendComplete == NULL) {
		status = BP3596_STATUS_ERROR_PARAM;
		goto error;
	}
	api.tx.done = sendComplete;
	status = BP3596_STATUS_OK;
error:
	return status;
}

int BP3596_recvEnable(void) {
	int status = BP3596_STATUS_UNKNOWN;

	if (api.addr == NULL) {
		status = BP3596_STATUS_ERROR_STATE;
		goto error;
	}
	if (ml7396_rxstart(&api.rx.buffer) < 0) {
		status = BP3596_STATUS_ERROR_STATE;
		goto error;
	}
	status = BP3596_STATUS_OK;
error:
	return status;
}

int BP3596_recvDisable(void) {
	int status = BP3596_STATUS_UNKNOWN;

	if (api.addr == NULL) {
		status = BP3596_STATUS_ERROR_STATE;
		goto error;
	}
	if (ml7396_rxstop() < 0) {  /* 処理内容は上の同じだがエラー判定のレイヤが違うので別にしておく */
		status = BP3596_STATUS_ERROR_STATE;
		goto error;
	}
	status = BP3596_STATUS_OK;
error:
	return status;
}

int BP3596_setFuncRecvComplete(void (*recvComplete)(const uint8_t *data, uint8_t rssi, int status)) {
	int status = BP3596_STATUS_UNKNOWN;

	if (recvComplete == NULL) {
		status = BP3596_STATUS_ERROR_PARAM;
		goto error;
	}
	api.rx.done = recvComplete;
	status = BP3596_STATUS_OK;
error:
	return status;
}

int BP3596_sleep(void) {
	int status = BP3596_STATUS_UNKNOWN;

	if (api.addr == NULL) {
		status = BP3596_STATUS_ERROR_STATE;
		goto error;
	}
	if (ml7396_sleep() < 0) {  /* 処理内容は上の同じだがエラー判定のレイヤが違うので別にしておく */
		status = BP3596_STATUS_ERROR_STATE;
		goto error;
	}
	status = BP3596_STATUS_OK;
error:
	return status;
}

int BP3596_wakeup(void) {
	int status = BP3596_STATUS_UNKNOWN;

	if (api.addr == NULL) {
		status = BP3596_STATUS_ERROR_STATE;
		goto error;
	}
	if (ml7396_wakeup() < 0) {  /* 処理内容は上の同じだがエラー判定のレイヤが違うので別にしておく */
		status = BP3596_STATUS_ERROR_STATE;
		goto error;
	}
	status = BP3596_STATUS_OK;
error:
	return status;
}

int BP3596_getState(void) {
	int status = BP3596_STATUS_UNKNOWN;

	switch (ml7396_state()) {
		case ML7396_StateReset:
			status = BP3596_STATUS_STATE_RESET;
			break;
		case ML7396_StateIdle:
			status = ml7396_rxbuffer() != NULL ? BP3596_STATUS_STATE_RECV : BP3596_STATUS_STATE_IDLE;
			break;
		case ML7396_StateSendACK:
			status = BP3596_STATUS_STATE_RECV;
			break;
		case ML7396_StateSending:
			status = BP3596_STATUS_STATE_SEND;
			break;
		case ML7396_StateWaitACK:
			status = BP3596_STATUS_STATE_SEND;
			break;
		case ML7396_StateSleep:
			status = BP3596_STATUS_STATE_SLEEP;
			break;
	}
	return status;
}

static uint16_t ver2u16(uint8_t Maj, uint8_t Min) {
	return (uint16_t)Maj << 8 | (uint16_t)Min << 0;  /* Version を 16ビット数値に変換 */
}

int BP3596_getVersion(uint16_t *version) {
	int status = BP3596_STATUS_UNKNOWN;

	*version = ver2u16(Version);
	status = BP3596_STATUS_OK;
	return status;
}
