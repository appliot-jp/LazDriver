/*
 * IEEE802.15.4e command interface
 * 
 * File:  cmdif.c
 * 
 * Copyright 2016 Lapis Semiconductor Co.,Ltd.
 * Author: Naotaka Saito
 * 
 * The program is based on BP3596 driver by Communication Technology
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/ioctl.h>
#include <linux/parport.h>
#include <linux/ctype.h>
#include <linux/poll.h>
#include <linux/slab.h>
#include <linux/major.h>
#include <linux/errno.h>
#include <linux/input.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/time.h>

#include "common_802154e.h"

#include "drv-802154e.h"
#include "mac-802154e.h"
#include "ieee802154e.h"

// Device driver IO
// mode = 0 :
//		read size = 2:				receiving packet size
//		read size = packet size:	raw data output
// mode = 1: sniffer
//		read size = 2:				receiving packet size
//		read size = packet size:	raw data output
// mode = 2 : MODE_STREAM
//		read size = 2				output data size
//		read size = data size
//			command			16bit
//				0x0000				nop
//				0x0101				phy reset
//				0x0201				send data
//				0x0301				set rx parameter(does not include payload)
//				0x0302				receiving data packet
//				0x0401				set to read ed value
//				0x0402				read ed value
//			time.tv_sec		32bit	current time (32bit epoch gime)
//			time.tv_nsec	32bit	nano sec time(000,000,000ns ~ 999,999,999ns) of current time
//			area			16bit	area code. currently support only "JP"
//			ch				16bit	24-61=frequency, -1=default
//			rate			16bit	50 or 100=bit rate, -1=default
//			pwr				16bit	1 or 20 output power, -1=default
//			header			32bit	0-0xFFFF = mac_header, -1= default
//			rxPanid			32bit	0-0xFFFF = panid,  -1= default, -2=ommit
//			rxAddrType		8bit	0: omit, 1=8bit, 2=16bit, 3=128bit
//			rxAddr			64bit
//			txPanid			32bit	0-0xFFFF = panid,  -1= default, -2=omitted
//			txAddrType		8bit	0=omit, 0> txaddr, 0< mac_addr
//							abs(1)=8bit, abs(2)=16bit, abs(3)=128bit
//			txAddr			64bit
//			rssi			8bit
//			payload			flexible length

#define PHY_DATA_SIZE		512		//250 + 1

// IEEE802.15.4e custom parameter
extern t_802154E_SETTING	mac_init_param;

// *****************************************************************
//			transfer process (input from chrdev)
// *****************************************************************
static ssize_t dec_data_to_header(const uint8_t *in,ssize_t size, t_MAC_HEADER *hdr) {
	ssize_t ret=size;
	int16_t offset = 12;
	int16_t raw_offset = 0;
	int16_t i;
	int32_t tmp32;
	int8_t tmp16;
	int8_t tmp8;
	int32_t mac_header;
	bool check_txaddr;
	// inputからmacのデータを生成する
	// channel
	tmp16 = *(uint16_t *)(in + offset),offset += sizeof(uint16_t);
	if(tmp16<0) {
		hdr->ch=mac_init_param.ch;
	}
	else
	{
		hdr->ch=tmp16;
	}
	// rate
	tmp16 = *(uint16_t *)(in + offset),offset += sizeof(uint16_t);
	if(tmp16<0) {
		hdr->rate=mac_init_param.bitrate;
	}
	else
	{
		hdr->rate=tmp16;
	}
	// pwr
	tmp16 = *(uint16_t *)(in + offset),offset += sizeof(uint16_t);
	if(tmp16<0) {
		hdr->pwr=mac_init_param.tx_pwr;
	}
	else
	{
		hdr->pwr=tmp16;
	}
	// header
	tmp32 = *(uint32_t *)(in + offset),offset += sizeof(uint32_t);
	if(tmp32<0) {
		mac_header = 0xa821;
	} else {
		mac_header = (uint16_t)tmp32;
	}
	dec_mac_header(mac_header,hdr);

	// get rxPanid from input
	tmp32 = *(uint32_t *)(in + offset),offset += sizeof(uint32_t);
	hdr->rx_addr.panid = (uint16_t)tmp32;
	if(tmp32==-2) {
		hdr->rx_addr.panid_enb = 0;
	} else if(tmp32 <0) {
		hdr->rx_addr.panid_enb = 1;
		hdr->rx_addr.panid = mac_init_param.panid;
	} else {
		hdr->rx_addr.panid_enb = 1;
	}

	// get rxAddrType from input
	tmp8 = *(uint8_t *)(in + offset),offset += sizeof(uint8_t);
	if((tmp8<0) || (tmp8>3)) {
		hdr->rx_addr.addr_type = 0;
	} else {
		hdr->rx_addr.addr_type = (uint8_t) tmp8;
	}

	// get rxAddr from input
	for(i = 7;i>=0;i--) {
		tmp8 = *(uint8_t *)(in + offset),offset += sizeof(uint8_t);
		hdr->rx_addr.addr.addr64[i] = (uint8_t)tmp8;
	}

	// get txPanid from input
	tmp32 = *(uint32_t *)(in + offset),offset += sizeof(uint32_t);
	hdr->tx_addr.panid = (uint16_t)tmp32;
	if(tmp32==-2) {
		hdr->tx_addr.panid_enb = 0;
	} else if(tmp32 <0) {
		hdr->tx_addr.panid_enb = 1;
		hdr->tx_addr.panid = mac_init_param.panid;
	} else {
		hdr->tx_addr.panid_enb = 1;
	}

	// get txAddrType and txAddr from input
	// txAddrType == -1, phy address is in use.
	tmp8 = *(uint8_t *)(in + offset),offset += sizeof(uint8_t);
	if(tmp8<0)
	{
		hdr->tx_addr.addr_type = (uint8_t) abs(tmp8);
		mac.get_myaddr(hdr->tx_addr.addr.addr64);
		offset += 8;
	}
	else
	{
		hdr->tx_addr.addr_type = (uint8_t) tmp8;
		for(i = 7;i>=0;i--) {
			tmp8 = *(uint8_t *)(in + offset),offset += sizeof(uint8_t);
			hdr->tx_addr.addr.addr64[i] = (uint8_t)tmp8;
			if(tmp8 != -1) check_txaddr = false;
		}
	}

	// rssi
	offset++;

	// generate mac header
	mac_header = enc_mac_header(hdr);
	if(mac_header < 0) {
		ret = -ESRCH;
		goto ERROR;
	}

	// make raw data
	*((uint16_t *)(hdr->raw.data+raw_offset)) = (uint16_t)mac_header, raw_offset += sizeof(uint16_t);
	if(hdr->seq_comp == 0)
	{
		*((uint8_t *)(hdr->raw.data+raw_offset)) = get_seq_num(),raw_offset += sizeof(uint8_t);
	}
	if(hdr->rx_addr.panid_enb)
	{
		*((uint16_t *)(hdr->raw.data+raw_offset)) = hdr->rx_addr.panid,raw_offset += sizeof(uint16_t);
	}
	switch(hdr->rx_addr.addr_type)
	{
		case 0:
			break;
		case 1:
			*((uint8_t *)(hdr->raw.data+raw_offset)) = hdr->rx_addr.addr.addr8,raw_offset += sizeof(uint8_t);
			break;
		case 2:
			*((uint16_t *)(hdr->raw.data+raw_offset)) = hdr->rx_addr.addr.addr16,raw_offset += sizeof(uint16_t);
			break;
		case 3:
			for(i=0;i<8;i++)
			{
				*((uint8_t *)(hdr->raw.data+raw_offset)) = hdr->rx_addr.addr.addr64[i],raw_offset += sizeof(uint8_t);
			}
			break;
	}
	if(hdr->tx_addr.panid_enb)
	{
		*((uint16_t *)(hdr->raw.data+raw_offset)) = hdr->tx_addr.panid,raw_offset += sizeof(uint16_t);
	}
	switch(hdr->tx_addr.addr_type)
	{
		case 0:
			break;
		case 1:
			*((uint8_t *)(hdr->raw.data+raw_offset)) = hdr->tx_addr.addr.addr8,raw_offset += sizeof(uint8_t);
			break;
		case 2:
			*((uint16_t *)(hdr->raw.data+raw_offset)) = hdr->tx_addr.addr.addr16,raw_offset += sizeof(uint16_t);
			break;
		case 3:
			for(i=0;i<8;i++)
			{
				*((uint8_t *)(hdr->raw.data+raw_offset)) = hdr->tx_addr.addr.addr64[i],raw_offset += sizeof(uint8_t);
			}
			break;
	}
	if(hdr->ielist.len>0)
	{
		memcpy(hdr->raw.data+raw_offset,hdr->ielist.data,hdr->ielist.len),raw_offset += hdr->ielist.len;
	}
	hdr->payload.data = hdr->raw.data + raw_offset;
	memcpy(hdr->raw.data + raw_offset,in + offset,size-offset);
	hdr->payload.len = size-offset;
	hdr->raw.len = raw_offset + hdr->payload.len;

ERROR:
	DEBUGONDISPLAY(MODE_STREAM_DEBUG,printk(KERN_INFO "[DRV-802154E]ch=%d\n", hdr->ch));
	DEBUGONDISPLAY(MODE_STREAM_DEBUG,printk(KERN_INFO "[DRV-802154E]pwr=%d\n", hdr->pwr));
	DEBUGONDISPLAY(MODE_STREAM_DEBUG,printk(KERN_INFO "[DRV-802154E]rate=%d\n", hdr->rate));
	DEBUGONDISPLAY(MODE_STREAM_DEBUG,printk(KERN_INFO "[DRV-802154E]frame_type=%d\n", hdr->frame_type));
	DEBUGONDISPLAY(MODE_STREAM_DEBUG,printk(KERN_INFO "[DRV-802154E]frame_ver=%d\n", hdr->frame_ver));
	DEBUGONDISPLAY(MODE_STREAM_DEBUG,printk(KERN_INFO "[DRV-802154E]seq_comp=%d\n", hdr->seq_comp));
	DEBUGONDISPLAY(MODE_STREAM_DEBUG,printk(KERN_INFO "[DRV-802154E]seq_enb=%d\n", hdr->pending));
	DEBUGONDISPLAY(MODE_STREAM_DEBUG,printk(KERN_INFO "[DRV-802154E]ack_req=%d\n", hdr->ack_req));

	DEBUGONDISPLAY(MODE_STREAM_DEBUG,printk(KERN_INFO "[DRV-802154E]rx=%d %04x %d %02x %02x %02x %02x %02x %02x %02x %02x\n",
				hdr->rx_addr.panid_enb,
				hdr->rx_addr.panid,
				hdr->rx_addr.addr_type,
				hdr->rx_addr.addr.addr64[7],
				hdr->rx_addr.addr.addr64[6],
				hdr->rx_addr.addr.addr64[5],
				hdr->rx_addr.addr.addr64[4],
				hdr->rx_addr.addr.addr64[3],
				hdr->rx_addr.addr.addr64[2],
				hdr->rx_addr.addr.addr64[1],
				hdr->rx_addr.addr.addr64[0]));
	DEBUGONDISPLAY(MODE_STREAM_DEBUG,printk(KERN_INFO "[DRV-802154E]tx=%d %04x %d %02x %02x %02x %02x %02x %02x %02x %02x\n",
				hdr->tx_addr.panid_enb,
				hdr->tx_addr.panid,
				hdr->tx_addr.addr_type,
				hdr->tx_addr.addr.addr64[7],
				hdr->tx_addr.addr.addr64[6],
				hdr->tx_addr.addr.addr64[5],
				hdr->tx_addr.addr.addr64[4],
				hdr->tx_addr.addr.addr64[3],
				hdr->tx_addr.addr.addr64[2],
				hdr->tx_addr.addr.addr64[1],
				hdr->tx_addr.addr.addr64[0] ));	

	DEBUGONDISPLAY(MODE_STREAM_DEBUG, PAYLOADDUMP(hdr->raw.data,hdr->raw.len));
	DEBUGONDISPLAY(MODE_STREAM_DEBUG, PAYLOADDUMP(hdr->payload.data,hdr->payload.len));
	return ret;
}

static ssize_t cmd_phy_reset(const uint8_t *in,size_t size) {
	uint16_t ret = 0;
	mac.phy_reset();
	return ret;
}
static ssize_t cmd_send_data(const uint8_t *in, size_t size, t_MAC_HEADER* hdr) {
	uint16_t ret = 0;
	ret = dec_data_to_header(in,size,hdr);
	DEBUGONDISPLAY(MODE_STREAM_DEBUG,printk(KERN_INFO "[DRV-802154E]SEND2 ret=%d",ret));
	if(ret <0) goto ERROR;
	//ret = mac.send2(&tx);
ERROR:
	return ret;
}
static ssize_t cmd_set_rx_param(const uint8_t *in, size_t size, t_MAC_HEADER* hdr) {
	uint16_t ret = 0;
	t_MAC_HEADER tx;
	mac.set_rx_param(&tx);
	return ret;
}
ssize_t cmd_get_ed_val(const uint8_t *in, size_t size, t_MAC_HEADER* hdr) {
	uint16_t ret = 0;
	t_MAC_HEADER tx;
	mac.get_ed_val(&tx);
	return ret;
}
#define		CMD_NOP				0x0000
#define		CMD_PHY_RESET		0x0101
#define		CMD_SEND_DATA		0x0201
#define		CMD_SET_RX_PARAM	0x0301
#define		CMD_GET_ED_VAL		0x0401
ssize_t gen_tx_stream(const uint8_t *in, ssize_t size) {
	ssize_t ret=size;
	uint16_t tmp16;

	t_MAC_HEADER tx;
	uint8_t raw[PHY_DATA_SIZE];

	// initializing buffer for raw
	tx.raw.data = raw;
	tx.raw.len = 0;

	tmp16 = *((uint16_t *) (in + 0));

	switch(tmp16) {
		case CMD_PHY_RESET:
			ret = cmd_phy_reset(in,size);
			break;
		case CMD_SEND_DATA:
			ret = cmd_send_data(in,size,&tx);
			break;
		case CMD_SET_RX_PARAM:
			ret = cmd_set_rx_param(in,size,&tx);
			break;
		case CMD_GET_ED_VAL:
			ret = cmd_get_ed_val(in,size,&tx);
			break;
		case CMD_NOP:
			break;
		default:
			ret = -ESRCH;
			break;
	}
	return ret;
}
// *****************************************************************
//			receiving process (output to chrdev)
// *****************************************************************
uint16_t gen_rx_stream(uint8_t *out, t_MAC_HEADER *phdr) {
	uint16_t offset=0;
	struct timespec time;

	// output temprary 
	uint16_t tmp16;
	uint32_t tmp32;
	uint8_t tmp8;

#define MEM_TO_BUFFER(A,B,C)	memcpy(A+C,&B,sizeof(B));\
	C+=sizeof(B);
	// write command 
	tmp16 = 0x03;
	MEM_TO_BUFFER(out,tmp16,offset);

	// write tv_sec & tv_nsec
	getnstimeofday(&time);
	MEM_TO_BUFFER(out,time.tv_sec,offset);
	MEM_TO_BUFFER(out,time.tv_nsec,offset);

	// area code
	tmp8 = 'J';
	MEM_TO_BUFFER(out,tmp8,offset);		// write area
	tmp8 = 'P';
	MEM_TO_BUFFER(out,tmp8,offset);		// write area
	tmp16 = mac_init_param.ch;
	MEM_TO_BUFFER(out,tmp16,offset);	// write ch
	tmp16 = mac_init_param.bitrate;
	MEM_TO_BUFFER(out,tmp16,offset);	// write rate
	tmp16 = mac_init_param.tx_pwr;
	MEM_TO_BUFFER(out,tmp16,offset);	// write pwr

	tmp32 = (uint32_t)(*(unsigned short*)phdr->raw.data);	// header

	MEM_TO_BUFFER(out,tmp32,offset);

	// rx_panid
	if(phdr->rx_addr.panid_enb) tmp32 = (uint32_t)phdr->rx_addr.panid;
	else tmp32 = 0xffffffff;
	MEM_TO_BUFFER(out,tmp32,offset);

	// rx_addr type
	tmp8 = (uint32_t)phdr->rx_addr.addr_type;
	MEM_TO_BUFFER(out,tmp8,offset);

	// rx_addr
	switch(phdr->rx_addr.addr_type) {
		case 0:
			tmp8 = 0xff;
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			break;
		case 1:
			tmp8 = 0;
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			tmp8 = phdr->rx_addr.addr.addr8;
			MEM_TO_BUFFER(out,tmp8,offset);
			break;
		case 2:
			tmp8 = 0;
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			tmp8 = (uint8_t)(phdr->rx_addr.addr.addr16>>8);
			MEM_TO_BUFFER(out,tmp8,offset);
			tmp8 = (uint8_t)phdr->rx_addr.addr.addr16&0x00ff;
			MEM_TO_BUFFER(out,tmp8,offset);
			break;
		case 3:
			MEM_TO_BUFFER(out,phdr->rx_addr.addr.addr64[7],offset);
			MEM_TO_BUFFER(out,phdr->rx_addr.addr.addr64[6],offset);
			MEM_TO_BUFFER(out,phdr->rx_addr.addr.addr64[5],offset);
			MEM_TO_BUFFER(out,phdr->rx_addr.addr.addr64[4],offset);
			MEM_TO_BUFFER(out,phdr->rx_addr.addr.addr64[3],offset);
			MEM_TO_BUFFER(out,phdr->rx_addr.addr.addr64[2],offset);
			MEM_TO_BUFFER(out,phdr->rx_addr.addr.addr64[1],offset);
			MEM_TO_BUFFER(out,phdr->rx_addr.addr.addr64[0],offset);
			break;
	}

	// tx_panid
	if(phdr->tx_addr.panid_enb) tmp32 = (uint32_t)phdr->tx_addr.panid;
	else tmp32 = 0xffffffff;
	MEM_TO_BUFFER(out,tmp32,offset);

	// tx_addr type
	tmp8 = (uint32_t)phdr->tx_addr.addr_type;
	MEM_TO_BUFFER(out,tmp8,offset);

	// tx_addr
	switch(phdr->tx_addr.addr_type) {
		case 0:
			tmp8 = 0xff;
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			break;
		case 1:
			tmp8 = 0;
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			tmp8 = phdr->tx_addr.addr.addr8;
			MEM_TO_BUFFER(out,tmp8,offset);
			break;
		case 2:
			tmp8 = 0;
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			MEM_TO_BUFFER(out,tmp8,offset);
			tmp8 = (uint8_t)(phdr->tx_addr.addr.addr16>>8);
			MEM_TO_BUFFER(out,tmp8,offset);
			tmp8 = (uint8_t)phdr->tx_addr.addr.addr16&0x00ff;
			MEM_TO_BUFFER(out,tmp8,offset);
			break;
		case 3:
			MEM_TO_BUFFER(out,phdr->tx_addr.addr.addr64[7],offset);
			MEM_TO_BUFFER(out,phdr->tx_addr.addr.addr64[6],offset);
			MEM_TO_BUFFER(out,phdr->tx_addr.addr.addr64[5],offset);
			MEM_TO_BUFFER(out,phdr->tx_addr.addr.addr64[4],offset);
			MEM_TO_BUFFER(out,phdr->tx_addr.addr.addr64[3],offset);
			MEM_TO_BUFFER(out,phdr->tx_addr.addr.addr64[2],offset);
			MEM_TO_BUFFER(out,phdr->tx_addr.addr.addr64[1],offset);
			MEM_TO_BUFFER(out,phdr->tx_addr.addr.addr64[0],offset);
			break;
	}

	// rssi
	tmp8 = phdr->rssi;
	MEM_TO_BUFFER(out,tmp8,offset);

	// payload
	memcpy(out+offset,phdr->payload.data,phdr->payload.len);
	offset+=phdr->payload.len;
	return offset;
}


