/* subghz_api.c
 *
 * Copyright (c) 2015  Lapis Semiconductor Co.,Ltd.
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
#ifdef LAZURITE_IDE
	#include <common.h>
	#include <string.h>
	#include <lp_manage.h>
	#include <driver_irq.h>
#else
	#include <linux/string.h>
	#include <linux/sched.h>
	#include <linux/wait.h>
	#include "common-lzpi.h"
	#include "hwif/random-lzpi.h"
#endif

#include "common_subghz.h"
#include "mach.h"
#include "subghz_api.h"
#include "errno.h"
#include "hwif/hal.h"
#include "aes/aes.h"

#ifndef LAZURITE_IDE
	extern wait_queue_head_t tx_done;
	extern int que_th2ex;
#endif

// this proto-type is for linux
static void subghz_decMac(SUBGHZ_MAC_PARAM *mac,uint8_t *raw,uint16_t raw_len);
uint8_t subghz_api_status = 0;

// local parameters
static struct {
	uint8_t addr_type;
	bool read;
	bool ack_req;
	bool broadcast_enb;
	SUBGHZ_STATUS tx_stat;
	SUBGHZ_STATUS rx_stat;
	volatile bool sending;
	volatile bool open;
	void (*rx_callback)(const uint8_t *data, uint8_t rssi, int status);		// change api
	void (*tx_callback)(uint8_t rssi, int status);
	struct rf_param rf;
	struct mach_param *mach;
	uint16_t panid;
	uint16_t short_addr;
	BUFFER tx;
	BUFFER rx;
} subghz_param;


static SUBGHZ_MSG subghz_init(void)
{
	SUBGHZ_MSG msg;
	int result;

	// clear parameter memory
	memset(&subghz_param,0,sizeof(subghz_param));
	subghz_param.addr_type = 6;
	subghz_param.ack_req = true;
	subghz_param.broadcast_enb = true;
	subghz_param.rf.cca_min_be = 0;
	subghz_param.rf.cca_max_be = 5;
	subghz_param.rf.cca_retry = 20;
	subghz_param.rf.cca_level = DBM_TO_MBM(-80);
	subghz_param.rf.tx_min_be = 0;
	subghz_param.rf.tx_max_be = 7;
	subghz_param.rf.tx_retry = 3;
	subghz_param.rf.tx_power = DBM_TO_MBM(13);
	subghz_param.rf.ack_timeout = 0;
	subghz_param.rf.tx_retry = 3;
    AES128_setKey(NULL);

	// reset
	if((subghz_param.mach = mach_init())==NULL)
	{
		result = -EIO;
		msg = SUBGHZ_RESET_FAIL;
		goto error;
	}

	// initializing parameters
	subghz_param.sending = false;
	subghz_param.read = false;
	subghz_param.open = false;

	// data to myaddress and grobal address in specified PANID can be received.
	subghz_param.short_addr = (uint16_t)subghz_param.mach->my_addr.ieee_addr[0] | 
		((uint16_t)subghz_param.mach->my_addr.ieee_addr[1]<<8);
	srand((uint16_t)subghz_param.short_addr);
	msg =  SUBGHZ_OK;

error:
	subghz_param.tx_stat.status = result;
	return msg;
}

static SUBGHZ_MSG subghz_remove(void)
{
	SUBGHZ_MSG msg=0;

	msg = HAL_remove();

	return msg;
}
static SUBGHZ_MSG subghz_begin(uint8_t ch, uint16_t panid, SUBGHZ_RATE rate, SUBGHZ_POWER txPower)
{
	SUBGHZ_MSG msg = SUBGHZ_OK;
	int result;

	if(subghz_param.open == false)
	{
		// start clock of ml7386
		if((result = mach_sleep(false))!=STATUS_OK)
		{
			subghz_param.open = true;
			msg = SUBGHZ_WAKEUP_FAIL;
			goto error;
		}
	}
	//initializing parameter
	subghz_param.sending = false;
	subghz_param.read = false;
	// 
	subghz_param.rf.ch = ch;
	if(rate == 50) {
		subghz_param.rf.pages = 1;
	} else if (rate == 100) {
		subghz_param.rf.pages = 2;
	} else {
		msg = SUBGHZ_SETUP_FAIL;
		goto error;
	}
	
	subghz_param.panid = panid;
	if((result = mach_set_my_short_addr(subghz_param.panid,subghz_param.short_addr)) != STATUS_OK) {
		msg = SUBGHZ_MYADDR_FAIL;
		goto error;
	}

	if(txPower == 1) 
		subghz_param.rf.tx_power = DBM_TO_MBM(1);
	else if(txPower == 20) 
		subghz_param.rf.tx_power = DBM_TO_MBM(13);
	else goto error;

	if((result = mach_setup(&subghz_param.rf)) != STATUS_OK) {
		msg = SUBGHZ_SETUP_FAIL;
		goto error;
	}
	
	msg = SUBGHZ_OK;

error:
	subghz_param.tx_stat.status = result;
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACH_DEBUG) {
		printk(KERN_INFO"%s %s %d %d %d \n",__FILE__,__func__,__LINE__,msg,result);
	}
#endif
	return msg;
}

static SUBGHZ_MSG subghz_close(void)
{
	SUBGHZ_MSG msg;
	int result;
	result = mach_sleep(true);
	if( result != STATUS_OK)
	{
		msg = SUBGHZ_SLEEP_FAIL;
		goto error;
	}
	subghz_param.open = false;

	msg = SUBGHZ_OK;
error:
	subghz_param.tx_stat.status = result;
	subghz_api_status = 0;
	return msg;
}

static SUBGHZ_MSG subghz_tx64le(uint8_t *addr_le, uint8_t *data, uint16_t len, void (*callback)(uint8_t rssi, int status)) {
	SUBGHZ_MSG msg;
	int result;
	uint8_t addr_type;
	struct mac_fc_alignment fc;

	subghz_api_status |= SUBGHZ_API_SEND64LE;

	// initializing buffer
	subghz_param.tx.data = data;
	subghz_param.tx.size = len;
	subghz_param.tx.len = len;
	subghz_param.tx_callback = callback;

	// initializing frame control
	memset(&fc,0,sizeof(fc));
	fc.frame_type = IEEE802154_FC_TYPE_DATA;
	fc.frame_ver = IEEE802154_FC_VER_4E;
	fc.ack_req = subghz_param.ack_req;

	mach_set_dst_ieee_addr(0xffff,addr_le);
	mach_set_src_addr(IEEE802154_FC_ADDR_IEEE);
	subghz_param.sending = true;
	addr_type = subghz_param.addr_type;

	result = mach_tx(fc,addr_type,&subghz_param.tx);

	//mach_ed(&rssi);
	//subghz_txdone(rssi,result);
	subghz_param.sending = false;

	if(result >= 0){
		msg = SUBGHZ_OK;
		subghz_param.tx_stat.rssi = result;
		subghz_param.tx_stat.status = 0;
	} else {
		subghz_param.tx_stat.rssi = 0;
		if(result == -EBUSY) msg = SUBGHZ_TX_CCA_FAIL;
		else if(result == -ETIMEDOUT) msg = SUBGHZ_TX_ACK_FAIL;
		else msg = SUBGHZ_TX_FAIL;
	}
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACH_DEBUG) {
		printk(KERN_INFO"%s,%s,%d,%d.%d\n",__FILE__,__func__,__LINE__,
			msg,subghz_param.tx_stat.rssi);
	}
#endif
	if(callback) {
		callback(subghz_param.tx_stat.rssi,msg);
	}

	subghz_api_status &= ~SUBGHZ_API_SEND64LE;

	return msg;
}

static SUBGHZ_MSG subghz_tx64be(uint8_t *addr_be, uint8_t *data, uint16_t len, void (*callback)(uint8_t rssi, int status)) {
	uint8_t addr_le[8];
	SUBGHZ_MSG msg;

	subghz_api_status |= SUBGHZ_API_SEND64BE;
	addr_le[7] = addr_be[0];
	addr_le[6] = addr_be[1];
	addr_le[5] = addr_be[2];
	addr_le[4] = addr_be[3];
	addr_le[3] = addr_be[4];
	addr_le[2] = addr_be[5];
	addr_le[1] = addr_be[6];
	addr_le[0] = addr_be[7];
	msg = subghz_tx64le(addr_le,data,len,callback);
	subghz_api_status &= ~SUBGHZ_API_SEND64BE;

	return msg;
}

static SUBGHZ_MSG subghz_tx(uint16_t panid, uint16_t dstAddr, uint8_t *data, uint16_t len, void (*callback)(uint8_t rssi, int status))
{
	SUBGHZ_MSG msg;
	int result;
	struct mac_fc_alignment fc;

	subghz_api_status |= SUBGHZ_API_SEND;

	// initializing buffer
	subghz_param.tx.data = data;
	subghz_param.tx.size = len;
	subghz_param.tx.len = len;
	subghz_param.tx_callback = callback;

	// initializing frame control
	memset(&fc,0,sizeof(fc));
	fc.frame_type = IEEE802154_FC_TYPE_DATA;
	fc.frame_ver = IEEE802154_FC_VER_4E;
	fc.ack_req = subghz_param.ack_req;
	if(panid < 0xFFFE) {
		mach_set_dst_short_addr(panid,dstAddr);
		mach_set_src_addr(IEEE802154_FC_ADDR_SHORT);
		subghz_param.sending = true;
		result = mach_tx(fc,subghz_param.addr_type,&subghz_param.tx);
	} else {
		uint8_t broadcast_addr[8] = {
			0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
		};
		mach_set_dst_ieee_addr(0xffff,broadcast_addr);
		mach_set_src_addr(IEEE802154_FC_ADDR_IEEE);
		subghz_param.sending = true;
		result = mach_tx(fc,subghz_param.addr_type,&subghz_param.tx);
	}

	//mach_ed(&rssi);
	//subghz_txdone(rssi,result);
	subghz_param.sending = false;

	if(result >= 0){
		msg = SUBGHZ_OK;
		subghz_param.tx_stat.rssi = result;
		subghz_param.tx_stat.status = 0;
	} else {
		subghz_param.tx_stat.rssi = 0;
		if(result == -EBUSY) msg = SUBGHZ_TX_CCA_FAIL;
		else if(result == -ETIMEDOUT) msg = SUBGHZ_TX_ACK_FAIL;
		else msg = SUBGHZ_TX_FAIL;
	}
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACH_DEBUG) {
		printk(KERN_INFO"%s,%s,%d,%d.%d\n",__FILE__,__func__,__LINE__,
				msg,subghz_param.tx_stat.rssi);
	}
#endif
	if(callback) {
		callback(subghz_param.tx_stat.rssi,msg);
	}

	subghz_api_status &= ~SUBGHZ_API_SEND;

	return msg;
}

int mach_rx_irq(struct mac_header *rx)
{

	subghz_param.rx_stat.rssi = rx->rssi;
	subghz_param.rx_stat.status = rx->raw.len;
	if((!subghz_param.mach->macl->promiscuousMode) && (!subghz_param.broadcast_enb) && (rx->dst.panid.enb) && (rx->dst.panid.data == 0xFFFF) &&
			(rx->dst.addr_type == 0x02) && (rx->dst.addr.short_addr = 0xFFFF)) {
#ifndef LAZURITE_IDE
		if(module_test & MODE_MACH_DEBUG) {
			printk(KERN_INFO"Lazurite:: Ignore Broadcast\n");
			PAYLOADDUMP(rx->raw.data, rx->raw.len);
		}
#endif
	} else {
#ifndef LAZURITE_IDE
		if(module_test & MODE_MACH_DEBUG) {
			printk(KERN_INFO"[rx]%s,%s,%d\n",__FILE__,__func__,__LINE__);
			PAYLOADDUMP(rx->raw.data, rx->raw.len);
		}
#endif
		if (rx->fc.fc_bit.sec_enb && AES128_getStatus()){
			uint8_t mhr_len;
			uint8_t pad;
			uint8_t outbuf[256];
			if (rx->fc.fc_bit.seq_comp){
				rx->seq=0;
			}
			mhr_len = rx->raw.len - rx->payload.len;
			memcpy(outbuf, rx->raw.data,mhr_len);
			pad = AES128_CBC_decrypt(outbuf+mhr_len, rx->payload.data, rx->payload.len, rx->seq);
			rx->raw.len -= pad;
			memcpy(rx->raw.data, outbuf, rx->raw.len);
#ifdef DEBUG_AES
			Serial.print("AES ON: pad num: ");
			Serial.println_long(pad,DEC);
#endif
		}

		if(subghz_param.rx_callback != NULL) {
			subghz_param.rx_callback(rx->raw.data, rx->rssi,rx->raw.len);
		} 
		memcpy(subghz_param.rx.data,rx->raw.data,rx->raw.len);
		subghz_param.rx.len = rx->raw.len;
	}
	return STATUS_OK;
}

static short subghz_readData(uint8_t *data, uint16_t max_size)
{
	short result = 0;
#ifdef	LAZURITE_IDE
	//  SUBGHZ_MAC_PARAM mac;
	//	__DI();
	dis_interrupts(DI_SUBGHZ);
#endif
	if(subghz_param.rx.len == 0)
	{
		result = 0;
	} else {
		max_size = (max_size > subghz_param.rx.len) ? subghz_param.rx.len : max_size;
		memcpy(data,subghz_param.rx.data,max_size);
		result = subghz_param.rx.len;
		subghz_param.rx.len = 0;
	}
#ifdef LAZURITE_IDE
	enb_interrupts(DI_SUBGHZ);
#endif

	return result;
}
// 
static SUBGHZ_MSG subghz_rxEnable(void (*callback)(const uint8_t *data, uint8_t rssi, int status))
{
	static uint8_t data[256];
	int result;
	SUBGHZ_MSG msg = SUBGHZ_OK;

	subghz_param.rx.data = data;
	subghz_param.rx.size = sizeof(data);
	subghz_param.rx.len = 0;

	subghz_param.rx_callback = callback;
	if(subghz_param.read == false)
	{
		if((result=mach_start(&subghz_param.rx))!=STATUS_OK) {
			msg = SUBGHZ_RX_ENB_FAIL;
			goto error;
		}
	}
	subghz_param.read = true;
	subghz_api_status |= SUBGHZ_API_RXENABLE;

error:

	return msg;
}

static SUBGHZ_MSG subghz_rxDisable(void)
{
	SUBGHZ_MSG msg;
	int result;

	result = mach_stop();
	if(result != STATUS_OK)
	{
		msg = SUBGHZ_RX_DIS_FAIL;
		goto error;						//2016.5.1 add 
	}
	subghz_param.read = false;
	msg = SUBGHZ_OK;
	subghz_api_status &= ~SUBGHZ_API_RXENABLE;

error:
	subghz_param.rx_stat.status = result;

	return msg;
}

/*static SUBGHZ_MSG subghz_setPANID(uint16_t panid)
	{
	SUBGHZ_MSG msg;
	int result;

	result = BP3596_setMyPANID(panid);
	if(result != BP3596_STATUS_OK)
	{
	msg = SUBGHZ_PANID;
	goto error;
	}
	msg = SUBGHZ_OK;
error:
subghz_param.tx_stat.status = result;
return msg;
}
*/
static void subghz_getStatus(SUBGHZ_STATUS *tx, SUBGHZ_STATUS *rx)
{
	if (tx != NULL)
	{
		memcpy(tx,&subghz_param.tx_stat, sizeof(subghz_param.tx_stat));
	}
	if (rx != NULL)
	{
		memcpy(rx,&subghz_param.rx_stat, sizeof(subghz_param.rx_stat));
	}
	return;
}

void subghz_get_my_ieee_addr(uint8_t *ieee_addr)
{
	memcpy(ieee_addr,subghz_param.mach->my_addr.ieee_addr,8);
}
void subghz_get_my_short_addr(uint16_t *short_addr)
{
	*short_addr = subghz_param.mach->my_addr.short_addr;
}
static uint16_t subghz_getMyAddress(void)
{
	return subghz_param.short_addr;
}
static void subghz_getMyAddr64(uint8_t *addr)
{
	if(addr) {
		addr[0] = subghz_param.mach->my_addr.ieee_addr[7];
		addr[1] = subghz_param.mach->my_addr.ieee_addr[6];
		addr[2] = subghz_param.mach->my_addr.ieee_addr[5];
		addr[3] = subghz_param.mach->my_addr.ieee_addr[4];
		addr[4] = subghz_param.mach->my_addr.ieee_addr[3];
		addr[5] = subghz_param.mach->my_addr.ieee_addr[2];
		addr[6] = subghz_param.mach->my_addr.ieee_addr[1];
		addr[7] = subghz_param.mach->my_addr.ieee_addr[0];
	}
	return ;
}

#ifdef LAZURITE_IDE
static const char subghz_msg0[] = "SUBGHZ_OK";
static const char subghz_msg1[] = "SUBGHZ_RESET_FAIL";
static const char subghz_msg2[] = "SUBGHZ_SETUP_FAIL";
static const char subghz_msg3[] = "SUBGHZ_SLEEP_FAIL";
static const char subghz_msg4[] = "SUBGHZ_WAKEUP_FAIL";
static const char subghz_msg5[] = "SUBGHZ_MYADDR_FAIL";
static const char subghz_msg6[] = "SUBGHZ_SETFIL_FAIL";
static const char subghz_msg7[] = "SUBGHZ_TX_COMP_FAIL";
static const char subghz_msg8[] = "SUBGHZ_TX_FAIL";
static const char subghz_msg9[] = "SUBGHZ_TX_CCA_FAIL";
static const char subghz_msg10[] = "SUBGHZ_TX_ACK_FAIL";
static const char subghz_msg11[] = "SUBGHZ_RX_ENB_FAIL";
static const char subghz_msg12[] = "SUBGHZ_RX_DIS_FAIL";
static const char subghz_msg13[] = "SUBGHZ_RX_COMP_FAIL";
static const char subghz_msg14[] = "SUBGHZ_PANID";
static const char subghz_msg15[] = "SUBGHZ_ERR_ADDRTYPE";
static const char subghz_msg16[] = "SUBGHZ_TTL_SEND_OVR";
static const char* subghz_msg[] = {
	subghz_msg0,
	subghz_msg1,
	subghz_msg2,
	subghz_msg3,
	subghz_msg4,
	subghz_msg5,
	subghz_msg6,
	subghz_msg7,
	subghz_msg8,
	subghz_msg9,
	subghz_msg10,
	subghz_msg11,
	subghz_msg12,
	subghz_msg13,
	subghz_msg14,
	subghz_msg15,
	subghz_msg16,
};
#endif
static void subghz_msgOut(SUBGHZ_MSG msg)
{
#ifdef LAZURITE_IDE
	static uint8_t s1[] = "\t";
	static uint8_t s2[] = "RSSI=";
	static uint8_t s3[] = "\tSTATUS=";

	if((msg>=SUBGHZ_OK)&&(msg<=SUBGHZ_TTL_SEND_OVR)){
		Serial.print(subghz_msg[msg]);
		Serial.print(s1);
	}

no_error:
	Serial.print(s2);
	Serial.print_long((long)subghz_param.tx_stat.rssi,DEC);
	Serial.print(s3);
	Serial.println_long((long)subghz_param.tx_stat.status,DEC);
	return;
#endif
}

static SUBGHZ_MSG subghz_getSendMode(SUBGHZ_PARAM *param)
{
	param->addrType = subghz_param.addr_type;
	param->senseTime = subghz_param.rf.cca_max_be;
	param->txRetry = subghz_param.rf.tx_retry;
	param->txInterval = subghz_param.rf.ack_timeout;
	//	param->ccaWait = subghz_param.rf.cca_duration;
	param->myAddress = subghz_param.mach->my_addr.short_addr; 

	return SUBGHZ_OK;
}

static SUBGHZ_MSG subghz_setSendMode(SUBGHZ_PARAM *param)
{
	// check addr_type
	if( param->addrType > 7 )
	{
		return SUBGHZ_ERR_ADDRTYPE;
	}
	// interval is calcurated from max_be.
	subghz_param.addr_type = param->addrType;
	subghz_param.rf.cca_max_be= param->senseTime;
	subghz_param.rf.tx_retry = param->txRetry;
	subghz_param.rf.ack_timeout = param->txInterval;
	//	subghz_param.rf.cca_interval = param->ccaWait;
	subghz_param.mach->my_addr.short_addr = param->myAddress;

	return SUBGHZ_OK;
}


static void subghz_decMac(SUBGHZ_MAC_PARAM *mac,uint8_t *raw,uint16_t raw_len)
{
	struct mac_header header;
	header.input.data = raw;
	header.input.len = raw_len;
	header.input.size = raw_len;
	header.raw.data = raw;
	header.raw.len = raw_len;
	header.raw.size = raw_len;
	mach_parse_data(&header);

	mac->mac_header.fc16=header.fc.fc16;
	mac->seq_num=header.seq;
	mac->addr_type=header.addr_type;
	if(header.dst.panid.enb)
		mac->dst_panid=header.dst.panid.data;
	else
		mac->dst_panid=0xfffe;
	if(header.src.panid.enb)
		mac->src_panid=header.src.panid.data;
	else
		mac->src_panid=0xfffe;
	memcpy(mac->dst_addr,header.dst.addr.ieee_addr,8);
	memcpy(mac->src_addr,header.src.addr.ieee_addr,8);
	mac->raw = raw;
	mac->raw_len = raw_len;
	mac->payload = header.payload.data;
	mac->payload_len = header.payload.len;

	return;
}

static SUBGHZ_MSG subghz_setKey(uint8_t *key)
{
	AES128_setKey(key);
	return SUBGHZ_OK;
}

static SUBGHZ_MSG subghz_setMyAddress(uint16_t my_addr)
{
	if(my_addr == 0xffff) return SUBGHZ_MYADDR_FAIL;
	subghz_param.short_addr = my_addr;
	return SUBGHZ_OK;
}

static SUBGHZ_MSG subghz_setPromiscuous(bool on) {
	mach_set_promiscuous(on);
	return SUBGHZ_OK;
}
static SUBGHZ_MSG subghz_setAckReq(bool on) {
	subghz_param.ack_req = on;
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACH_DEBUG) {
		printk(KERN_INFO"%s,%s,%d,%d\n",__FILE__,__func__,__LINE__,subghz_param.ack_req);
	}
#endif
	return SUBGHZ_OK;
}
static SUBGHZ_MSG subghz_setBroadcastEnb(bool on) {
	subghz_param.broadcast_enb = on;
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACH_DEBUG) {
		printk(KERN_INFO"%s,%s,%d,%d\n",__FILE__,__func__,__LINE__,subghz_param.broadcast_enb);
	}
#endif
	return SUBGHZ_OK;
}

static bool subghz_set_enhance_ack(uint8_t *data, int size){
	return mach_set_enhance_ack(data,size);
}

static void subghz_get_enhance_ack(uint8_t **data,int *size){
	mach_get_enhance_ack(data,size);
	return;
}
static void subghz_set_ack_tx_interval(uint16_t interval){
	mach_set_ack_tx_interval(interval);
}

static void subghz_get_ed_value(uint8_t *rssi){
    mach_ed(rssi);
}

// setting of function
const SubGHz_CTRL SubGHz = {
	subghz_init,
	subghz_remove,
	subghz_begin,
	subghz_close,
	subghz_tx,
	subghz_tx64le,
	subghz_tx64be,
	subghz_rxEnable,
	subghz_setPromiscuous,
	subghz_setAckReq,
	subghz_setBroadcastEnb,
	subghz_rxDisable,
	subghz_readData,
	subghz_getMyAddress,
	subghz_getMyAddr64,
	subghz_setMyAddress,
	subghz_getStatus,
	subghz_msgOut,
	subghz_setSendMode,
	subghz_getSendMode,
	subghz_decMac,
	subghz_setKey,
	subghz_set_enhance_ack,
	subghz_get_enhance_ack,
	subghz_set_ack_tx_interval,
	subghz_get_ed_value
};
