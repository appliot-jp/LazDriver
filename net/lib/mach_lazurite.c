/* mach_lazurite.c - MAC(High level) for lazurite
 *
 * Copyright (c) 2015  Lapis Semiconductor Co.,Ltd
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
 * <http://www.gnu.org/licenses/>
 */

/*! @struct MACH_PARAM
  @brief  local parameter for mac high layer
  */
#include "errno.h"
#include "endian.h"
#include "common-lzpi.h"
#include "mach_lazurite.h"
#include "macl_lazurite.h"
#include "arib_lazurite.h"

static struct mach_param mach;
/*! @uint8_t ackbuf[32]
  @brief  data buffer to make ack data
  */
static uint8_t ackbuf[8];

/******************************************************************************/
/*! @brief enb_dst_panid
  enb/dis of dst_panid/src_panid at each addrType
0bit : addrType=0
1bit : addrType=1
...
*/
const uint8_t enb_dst_panid = 0x52;
const uint8_t enb_src_panid = 0x04;
const uint8_t addr_len[] = {0x00,0x01,0x02,0x08};

int	get_mac_addr(uint8_t *macaddr)
{
	int status=STATUS_OK;
	int i;
	const uint8_t from_eeprom[] = {
		0x00,0x1d,0x12,0x90,
		0x00,0x63,0x60,0x0c,
	};

	for (i=0;i<8;i++)
	{
		macaddr[i] = from_eeprom[7-i];
	}

	return status;
}

// local functions
/******************************************************************************/
/*! @brief make raw data
  @param[in] *data start pointer of output buffer
  @param[in] *size length of header
  @param[in] *header  pointer of mac header
  ack_reg (1: auto, 0: no ack)
  panid_comp,dst_addr_type,src_addr_type are generated from addr_type

  @return    false= invalid data, true valid data
  @exception	EINVAL data is not set according to addr_type

  dstpanid | dstaddr | srcpanid | srcaddr | ack     | tx mode   
  ----------|---------|----------|---------|---------|-----------
  ff     |   ff    |   ---    |  ---    | no ack  | broadcast 
  ---     |   ff    |   ---    |  ---    | no ack  | groupcast 
  ---     |   no    |   ---    |  ---    |  ack    | unicast   
  ff     |  64bit  |          |  ---    |  ack    | unicast   
  ff/no    |  0/8/16 |          |  ---    | no ack  |  error    
  ---     |  ---    |    ff    |  ---    |  ack    | unicast   
  ---     |  ---    |   ---    |   ff    |  ack    | unicast   
  ---     |  ---    |   ---    |   no    |  ack    | unicast   
 ******************************************************************************/

static int mach_make_header(struct mac_header *header) {
	uint16_t offset = 2;
	int status;
	bool dst_ffff = true;
	int i;

	// check data 
	if((header->payload.data==NULL) || (header->raw.data==NULL)) {
		printk(KERN_ERR"buffer error in %s,%s,%d,%lx,%lx\n",
				__FILE__,
				__func__,
				__LINE__,
				(long)header->payload.data,
				(long)header->raw.data);
		status = -ENOMEM;
		goto error;
	}

	// sequence number
	if(!header->fc.fc_bit.seq_comp) {
		if(header->raw.size >= (offset + 1)){
			header->seq++;
			header->raw.data[offset]=header->seq,offset++;
		} else {
			printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
			status = -ENOMEM;
			goto error;
		}
	}

	// dst panid
	if(enb_dst_panid&BIT(header->addr_type))
	{
		if(!header->dst.panid.enb)
		{
			printk(KERN_ERR"dst panid is invalid in %s,%s,%d\n", __FILE__, __func__, __LINE__);
			status = -EINVAL;
			goto error;
		} else {
			if(header->raw.size >= (offset + 2)){
				H2LBS(header->raw.data[offset],header->dst.panid.data), offset+=2;
			} else {
				printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
				status = -ENOMEM;
				goto error;
			}
		}
	}

	// dst addr
	// 2bit of addr type shows dst addr
	if(header->addr_type&BIT(1))
	{
		int i;
		switch(header->dst.addr_type)
		{
			case 0:
#ifndef LAZURITE_IDE
				if(module_test & MODE_MACH_DEBUG) {
					printk(KERN_ERR"dst address is not set in %s,%s,%d\n", __FILE__, __func__, __LINE__);
				}
#endif
				status = -EINVAL;
				goto error;
				break;
			case 1:
				if((header->dst.panid.data == 0xffff) ||
						(header->dst.panid.data == 0xfffe)||
						(header->dst.panid.enb == false))
				{
#ifndef LAZURITE_IDE
					if(module_test & MODE_MACH_DEBUG) {
						printk(KERN_ERR"invalid panid for short address.%s,%s,%d\n", __FILE__, __func__, __LINE__);
					}
#endif
					status = -EINVAL;
					goto error;
				}
				if(header->raw.size >= (offset + addr_len[1])){
					header->fc.fc_bit.dst_addr_type = IEEE802154_FC_ADDR_LDD;
					header->raw.data[offset] = header->dst.addr.lddn_addr,offset++;
					if(header->dst.addr.lddn_addr != 0xff) dst_ffff = false;
				} else {
					printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
					status = -ENOMEM;
					goto error;
				}
				break;
			case 2:
				if((header->dst.panid.data == 0xffff) ||
						(header->dst.panid.data == 0xfffe) ||
						(header->dst.panid.enb == false))
				{
#ifndef LAZURITE_IDE
					if(module_test & MODE_MACH_DEBUG) {
						printk(KERN_ERR"invalid panid for short address.%s,%s,%d\n", __FILE__, __func__, __LINE__);
					}
#endif
					status = -EINVAL;
					goto error;
				}
				if(header->raw.size >= (offset + addr_len[2])){
					header->fc.fc_bit.dst_addr_type = IEEE802154_FC_ADDR_SHORT;
					H2LBS(header->raw.data[offset],header->dst.addr.short_addr), offset+=2;
				} else {
					printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
					status = -ENOMEM;
					goto error;
				}
				if(header->dst.addr.short_addr != 0xffff) dst_ffff = false;
				break;
			case 3:
				if(header->raw.size >= (offset + addr_len[3])){
					for(i = 0;i<addr_len[header->dst.addr_type];i++)
					{
						header->raw.data[offset] = header->dst.addr.ieee_addr[i],offset++;
						if(header->dst.addr.ieee_addr[i] != 0xff) dst_ffff = false;
					}
					header->fc.fc_bit.dst_addr_type = IEEE802154_FC_ADDR_IEEE;
				} else {
					printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
					status = -ENOMEM;
					goto error;
				}
		}
		if(dst_ffff) header->fc.fc_bit.ack_req=0;
	} else {
		header->fc.fc_bit.src_addr_type = IEEE802154_FC_ADDR_NONE;
	}

	// src panid
	if(enb_src_panid&BIT(header->addr_type))
	{
		if(header->src.panid.enb == 0)
		{
			printk(KERN_ERR"src panid is invalid in %s,%s,%d\n", __FILE__, __func__, __LINE__);
			status = -EINVAL;
			goto error;
		} else {
			if(header->raw.size >= (offset + sizeof(uint16_t))){
				H2LBS(header->raw.data[offset],header->src.panid.data), offset+=2;
			} else {
				printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
				status = -ENOMEM;
				goto error;
			}
		}
	}
	// src addr
	if(header->addr_type & BIT(2))
	{
		switch(header->src.addr_type)
		{
			case 0:
				status = -EINVAL;
				goto error;
				break;
			case 1:
				if(header->raw.size < (offset + addr_len[1])){
					printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
					status = -ENOMEM;
					goto error;
				}
				if(header->src.addr.lddn_addr==0xff){
					printk(KERN_ERR"invalid src LDD address. %s,%s,%d\n", __FILE__, __func__, __LINE__);
					status = -EINVAL;
					goto error;
				}
				header->raw.data[offset] = header->src.addr.lddn_addr,offset++;
				header->fc.fc_bit.src_addr_type = IEEE802154_FC_ADDR_LDD;
				break;
			case 2:
				if(header->raw.size < (offset + addr_len[2])){
					printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
					status = -ENOMEM;
					goto error;
				}
				if(header->src.addr.short_addr==0xffff)
				{
					printk(KERN_ERR"invalid src short address. %s,%s,%d\n", __FILE__, __func__, __LINE__);
					status = -EINVAL;
					goto error;
				}
				H2LBS(header->raw.data[offset],header->src.addr.short_addr), offset+=2;
				header->fc.fc_bit.src_addr_type = IEEE802154_FC_ADDR_SHORT;
				break;
			case 3:
				if(header->raw.size < (offset + addr_len[3])){
					printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
					status = -ENOMEM;
					goto error;
				}
				for(i = 0;i<addr_len[header->src.addr_type];i++)
				{
					header->raw.data[offset] = header->src.addr.ieee_addr[i],offset++;
				}
				header->fc.fc_bit.src_addr_type = IEEE802154_FC_ADDR_IEEE;
				break;
		}
	} else {
		header->fc.fc_bit.dst_addr_type = IEEE802154_FC_ADDR_NONE;
	}

	// copy payload to raw buffer
	header->fc.fc_bit.panid_comp = header->addr_type & 0x01;
	header->fc.fc_bit.nop = 0;
	if(header->raw.size >= (offset + header->payload.len)) {
		if(header->payload.len != 0) {
			memcpy(&header->raw.data[offset], header->payload.data, header->payload.len);
		}
		offset+=header->payload.len;
		header->raw.len = offset;
	} else {
		status = -ENOMEM;
		goto error;
	}

	// write mac header
	H2LBS(header->raw.data[0],header->fc.fc16);

	status = STATUS_OK;

error:
	return status;
}

/******************************************************************************/
/*! @brief prawarse mac header
  @param[in] header pointer of mac header
  input = input buffer
  raw   = output buffer
  payload = pointer/length of payload
  @return    STATUS_OK, error num
  @exception ENOMEM = data size error
  in case of rx disable, this error is occured, when any data is received,
 ******************************************************************************/
int mach_parse_data(struct mac_header *header) {

	uint16_t offset = 0;
	int status;
	int i;

	// framce control
	LB2HS(header->fc,header->input.data[offset]),offset+=2;

	// addr type
	header->addr_type = header->fc.fc_bit.panid_comp;
	header->addr_type += (header->fc.fc_bit.src_addr_type ? 2: 0);
	header->addr_type += (header->fc.fc_bit.dst_addr_type ? 4: 0);
	header->src.addr_type = header->fc.fc_bit.src_addr_type;
	header->dst.addr_type = header->fc.fc_bit.dst_addr_type;

	// panid enb
	header->dst.panid.enb = (enb_dst_panid & BIT(header->addr_type)) ? 1: 0;
	header->src.panid.enb = (enb_src_panid & BIT(header->addr_type)) ? 1: 0;

	// sequence number
	if (!header->fc.fc_bit.seq_comp) {
		header->seq = header->input.data[offset],offset++;
	}
	// dst panid
	if(header->dst.panid.enb)
	{
		LB2HS(header->dst.panid.data,header->input.data[offset]),offset+=2;
	}
	// dst addr
	memset(header->dst.addr.ieee_addr,0,8);
	for(i=0;i< addr_len[header->fc.fc_bit.dst_addr_type];i++)
	{
		header->dst.addr.ieee_addr[i] = header->input.data[offset],offset++;
	}
	// src panid
	if(header->src.panid.enb)
	{
		LB2HS(header->src.panid.data,header->input.data[offset]),offset+=2;
	}
	// src addr
	memset(header->src.addr.ieee_addr,0,8);

	for(i=0;i< addr_len[header->fc.fc_bit.src_addr_type];i++)
	{
		header->src.addr.ieee_addr[i] = header->input.data[offset],offset++;
	}

	
	header->raw.len = header->input.len; // last byte is rss
	header->payload.data = (uint8_t *)(header->raw.data+offset);
	header->payload.len = header->raw.len - offset - 1; // -1 means rssi attathed on raw
	header->rssi = header->input.data[header->input.len];

	status = STATUS_OK;

	return status;
}

bool mach_match_seq_num(void)
{
	bool result=false;

	if((mach.rx.seq == mach.rx_prev.seq) &&
			memcmp(&mach.rx.src,&mach.rx_prev.src,sizeof(struct fc_addr))==0) {
		result=true;
	}

	return result;
}

/******************************************************************************/
/*! @brief make ack header
  @param[in] *ack mac header of ack
  @param[in] *rx mac header of receiving data
  @return    STATUS_OK
  @exception EINVAL		can not return ack
  rx.dst.addr | rx.src.addr | my.pancoord | coord.pancoord | rx    | ack
  -----------------------------------------------------------------------
  ieee      |     none    |  don't care |  don't care    | yes   |  no
  short/omit  |     none    |   true      |  don't care    | yes   |  no
  short/omit  |     none    |  false      |  don't care    | No    |  no

  ieee      |     ieee    |  don't care |  don't care    | yes   |  yes
  short/omit  |     ieee    |   true      |  don't care    | yes   |  yes
  short/omit  |     ieee    |  false      |  don't care    | No    |   no

  ieee      |  short/omit |  don't care |    true        | yes   |  yes
  short/omit  |  short/omit |   true      |    true        | yes   |  yes
  short/omit  |  short/omit |  false      |    true        | No    |   no

  ieee      |  short/omit |  don't care |    false        | yes  |  no
  short/omit  |  short/omit |   true      |    false        | yes  |  no
  short/omit  |  short/omit |  false      |    false        | No   |  no
 ******************************************************************************/
#define ACK_ENB	0x06
bool mach_make_ack_header(void) {

	bool ack_condition=false;
	uint16_t offset = 0;

	if((!(mach.rx.addr_type & ACK_ENB)) &&
			(mach.my_addr.pan_coord == true) &&
			(mach.coord_addr.pan_coord == true) &&
			((mach.rx.dst.addr.short_addr == 0xFFFF) ||
			 (mach.rx.dst.addr.short_addr == 0xFFFE) )&&
			((mach.rx.src.addr.short_addr == 0xFFFF) ||
			 (mach.rx.src.addr.short_addr == 0xFFFE) ))
		goto noack;
	if( (mach.rx.fc.fc_bit.panid_comp == 1) &&
			(mach.my_addr.pan_id != mach.coord_addr.pan_id))
		goto noack;
	if( (mach.rx.fc.fc_bit.panid_comp == 0) &&
			(mach.my_addr.pan_id != mach.rx.dst.panid.data))
		goto noack;

	// genenrate ack data
	mach.ack.fc.fc16 = 0;
	mach.ack.fc.fc_bit.frame_type = IEEE802154_FC_TYPE_ACK;
	mach.ack.fc.fc_bit.panid_comp = 1;
	mach.ack.fc.fc_bit.seq_comp = mach.rx.fc.fc_bit.seq_comp;
	mach.ack.fc.fc_bit.frame_ver = mach.rx.fc.fc_bit.frame_ver;
	ack_condition = true;

	// output mac header to memory
	H2LBS(mach.ack.raw.data[offset],mach.ack.fc.fc16), offset+=2;

	// output sequence number
	if(!mach.ack.fc.fc_bit.seq_comp) {
		mach.ack.seq = mach.rx.seq;
		mach.ack.raw.data[offset] = mach.ack.seq,offset++;
	}
	mach.ack.raw.len = offset;


noack:
	return ack_condition;
}
int mach_update_rx_data(void)
{
	int status = STATUS_OK;

	return status;
}
/*********************************************************************/
/*! @brief mach init 
  mac high layer initialization
  @return    pointer of MACH_PARAM
  @exception  return NULL
 *********************************************************************/
struct mach_param *mach_init(void)
{
	memset(&mach,0,sizeof(struct mach_param));
	mach.macl = macl_init();
	if(mach.macl == NULL) return NULL;

	// set data buffer for ack
	mach.ack.raw.data = ackbuf;
	mach.ack.raw.size = sizeof(ackbuf);
	mach.ack.raw.len = 0;
	macl_sleep(true);
	get_mac_addr(mach.my_addr.ieee_addr);
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACH_DEBUG) {
		printk(KERN_INFO"mach_setup,%02x%02x%02x%02x%02x%02x%02x%02x\n",
				mach.my_addr.ieee_addr[7],
				mach.my_addr.ieee_addr[6],
				mach.my_addr.ieee_addr[5],
				mach.my_addr.ieee_addr[4],
				mach.my_addr.ieee_addr[3],
				mach.my_addr.ieee_addr[2],
				mach.my_addr.ieee_addr[1],
				mach.my_addr.ieee_addr[0]
			  );
	}
#endif

	return &mach;
}

/********************************************************************/
/*! @brief mach start 
  mac high layer rx on
  @return     STATUS_OK
  @exception  depends on macl_start
 ********************************************************************/
int mach_start(BUFFER *rxbuf) {
	int status = STATUS_OK;

	// initialize phy  <== ml7396_reset();
	mach.rx.raw.data = rxbuf->data;
	mach.rx.raw.size = rxbuf->size;
	mach.rx.raw.len = 0;
	mach.rx.payload.data = NULL;
	mach.rx.payload.size = rxbuf->size;
	mach.rx.payload.len = 0;

	status = macl_start();

	return status;
}

/********************************************************************/
/*! @brief mach stop 
  mac high layer rx off
  @return    STATUS_OK
  @exception  depends on macl_stop
 ********************************************************************/
int mach_stop(void) {
	return macl_stop();
}

int mach_setup(struct rf_param *rf) {
	int status;
	struct wpan_phy_cca cca;

	// link parameter
	mach.rf = rf;

	// set channel
	if((status = macl_set_channel(rf->pages,rf->ch)) != STATUS_OK){
		goto error;
	}

	// @issue txPower
	macl_set_txpower(rf->tx_power);

	// set setting CCA
	macl_set_csma_params(rf->cca_min_be,rf->cca_max_be,rf->cca_retry);
	macl_set_frame_retries(rf->tx_retry);
	macl_ch_scan(rf->cca_interval);				// add 
	cca.mode = rf->cca_mode;
	cca.opt = rf->cca_opt;
	macl_set_cca_mode(&cca);
	macl_set_cca_ed_level(rf->cca_level);
error:
	return status;
}

/********************************************************************/
/*! @brief tx in mac high layer
  @param[in]	*addr	64bit distination address
  @return    STATUS_OK
  @exception none
 ********************************************************************/
int mach_set_dst_ieee_addr(uint8_t *addr)
{
	memcpy(mach.tx.dst.addr.ieee_addr,addr,sizeof(8));
	return STATUS_OK;
}

int mach_set_src_addr(uint8_t addr_mode)
{
	int status=STATUS_OK;
	switch(addr_mode)
	{
		case 0:
			mach.tx.src.panid.enb = true;
			mach.tx.src.panid.data = mach.my_addr.pan_id;
			mach.tx.src.addr_type = IEEE802154_FC_ADDR_NONE;
			break;
		case 1:
			mach.tx.src.panid.enb = true;
			mach.tx.src.panid.data = mach.my_addr.pan_id;
			mach.tx.src.addr_type = IEEE802154_FC_ADDR_LDD;
			mach.tx.src.addr.short_addr = mach.my_addr.lddn_addr;
			break;
		case 2:
			mach.tx.src.panid.enb = true;
			mach.tx.src.panid.data = mach.my_addr.pan_id;
			mach.tx.src.addr_type = IEEE802154_FC_ADDR_SHORT;
			mach.tx.src.addr.short_addr = mach.my_addr.short_addr;
			break;
		case 3:
			mach.tx.src.panid.enb = mach.my_addr.pan_coord;
			mach.tx.src.panid.data = mach.my_addr.pan_id;
			mach.tx.src.addr_type = IEEE802154_FC_ADDR_IEEE;
			memcpy(mach.tx.src.addr.ieee_addr, mach.my_addr.ieee_addr,8);
			break;
		default:
			status = -EINVAL;
			break;
	}
	return status;
}

int mach_set_dst_short_addr(uint16_t panid,uint16_t addr)
{
	mach.tx.dst.panid.enb = true;
	mach.tx.dst.panid.data = panid;
	mach.tx.dst.addr_type = IEEE802154_FC_ADDR_SHORT;
	mach.tx.dst.addr.short_addr = addr;

	return STATUS_OK;
}

/********************************************************************/
/*! @brief set my short address
  panid == 0xffff, 0xfffe	--> pan_coord is false
  panid == others			--> pan_coord is true
  @param[in]	panid	64bit distination address
  @param[in]	addr	start pointer of payload
  @return		status = STATUS_OK
  @exception	EINVAL: panid/short_addr == 0xffff,0xfffe
  my.panid | my.short_addr | pan_coord
  ---    |     ---       | false (init)
  0xffff   |     ---       | false
  0xfffe   |     ---       | false
  ---    |     0xffff    | false
  ---    |     0xfffe    | false
  other  |     other     | true
 ********************************************************************/
int mach_set_my_short_addr(uint16_t panid,uint16_t short_addr)
{
	int status=STATUS_OK;
	mach.my_addr.pan_id = panid;
	mach.my_addr.short_addr = short_addr;
	if((panid == 0xffff) || (panid == 0xfffe) || (short_addr == 0xffff) || (short_addr == 0xfffe))
	{
		mach.my_addr.pan_coord = false;
		status = -EINVAL;
	}
	mach.my_addr.pan_coord = true;

	if(!mach.promiscuous)
	{
		struct ieee802154_hw_addr_filt filt;
		filt.pan_id = mach.my_addr.pan_id;
		filt.pan_coord = mach.my_addr.pan_coord;
		filt.short_addr = mach.my_addr.short_addr;
		memcpy(filt.ieee_addr,mach.my_addr.ieee_addr,8);
		macl_set_hw_addr_filt(&filt,0x0f);			// update all of addr filter
	}
	return status;
}
/********************************************************************/
/*! @brief set coord short address
  @param[in]	panid	panid of coordinator
  @param[in]	addr	address of coordinator
  @param[in]	ieee_addr	64bit address
  @return		status = STATUS_OK
  @exception	EINVAL: panid/short_addr == 0xffff,0xfffe
  coord.panid | coord.short_addr | pan_coord
  ---    |     ---       | false (init)
  0xffff   |     ---       | false
  0xfffe   |     ---       | false
  ---    |     0xffff    | false
  ---    |     0xfffe    | false
  other  |     other     | true
 ********************************************************************/
int mach_set_coord_addr(uint16_t panid,uint16_t short_addr,uint8_t *ieee_addr)
{
	int status=STATUS_OK;

	mach.coord_addr.pan_id = panid;
	mach.coord_addr.short_addr = short_addr;
	if(ieee_addr) memcpy(mach.coord_addr.ieee_addr,ieee_addr,8);
	if((panid == 0xffff) || (panid == 0xfffe) ||
			(short_addr == 0xffff) || (short_addr == 0xfffe)) {
		mach.coord_addr.pan_coord = false;
		status = -EINVAL;
	}
	mach.coord_addr.pan_coord = true;

	return status;
}

int mach_set_promiscuous(bool on)
{
	int status;
	if (macl_set_promiscuous_mode(on)==STATUS_OK)
	{
		mach.promiscuous = true;
		status = STATUS_OK;
	} else {
		mach.promiscuous = false;
		status = -EIO;
	}
	return STATUS_OK;
}

int mach_tx(struct mac_fc_alignment fc,uint8_t addr_type,BUFFER *txbuf)
{
	int status = STATUS_OK;

	// initializing buffer
	mach.tx.raw.data = mach.macl->phy->out.data;
	mach.tx.raw.size = mach.macl->phy->out.size;
	mach.tx.payload.data = txbuf->data;
	mach.tx.payload.size = txbuf->size;
	mach.tx.payload.len = txbuf->len;
	mach.tx.addr_type = addr_type;
	memcpy(&mach.tx.fc.fc_bit,&fc,sizeof(fc)) ;

	if((status = mach_make_header(&mach.tx))!=STATUS_OK) {
		goto error;
	}
	// @issue arib should be implemented later.
	/*
	   if((arib_tx_check(mach.rf->pages,mach.rf->ch,mach.tx.raw.len))==false) {
	   goto error;
	   }
	   */
	status = macl_xmit_sync(mach.tx.raw);
	if(status == STATUS_OK)
	{
		status = mach.rx.rssi;
	}
	// @issue arib should be implemented later.
	/*
	   if(status == STATUS_OK)
	   arib_tx_end(mach.rf->pages,mach.rf->ch,mach.tx.raw.len);
	   */

error:
	return status;
}
int mach_ed(uint8_t *ed)
{
	return macl_ed(ed);
}

int mach_sleep(bool on)
{
	return macl_sleep(on);
}

/********************************************************************/
/*! @brief set coord short address
  @param[in]	rx  pointer of rx buffer<br>
  when rx==NULL, end of sending ack
  @param[out]	ack pointer when ack is return<br>
  when ack is not needed, ack is set to NULL
  @return		STATUS_OK<br>
  1= data is ack
  @exception	
 ********************************************************************/
int macl_rx_irq(BUFFER *rx,BUFFER *ack)
{
	int status=STATUS_OK;
	uint8_t rssi;

	// end of sending ack during rx
	if(!rx) {
		goto update;
	}

	// receiving data during tx
	if(ack) {
		// initialize ack buffer
		ack->data = NULL;
		ack->len = 0;
		ack->size = mach.ack.raw.size;
	}

	// set rx buffer
	mach.rx.input.data = rx->data;
	mach.rx.input.len = rx->len;
	mach.rx.input.size = rx->size;

	// parse raw data
	if((status = mach_parse_data(&mach.rx))!= STATUS_OK) {
		goto end;
	}

	// check frame type
	if ((mach.rx.fc.fc_bit.frame_type == IEEE802154_FC_TYPE_DATA) ||
			(mach.rx.fc.fc_bit.frame_type == IEEE802154_FC_TYPE_CMD)) {
		// check sequence number
		if ((mach.rx.fc.fc_bit.ack_req) &&		// ack is requested
				(ack) &&
				(!mach.promiscuous) ) {
			if(mach_make_ack_header()) {
				ack->data = mach.ack.raw.data;
				ack->len = mach.ack.raw.len;
				ack->size = mach.ack.raw.size;
				goto end;
			}
		}
	} else if (mach.rx.fc.fc_bit.frame_type == IEEE802154_FC_TYPE_ACK) {
		if(mach.rx.seq == mach.tx.seq) status = 1;				// check ack
		goto end;
	} else {									// other data type
	}

update:
	// copy data, if output buffer is available.
	if(mach.rx.raw.size >= mach.rx.input.len)
		memcpy(mach.rx.raw.data,mach.rx.input.data,mach.rx.input.len);
	else
		goto end;

	if(mach_match_seq_num()==false) {		// check sequence number
		// rx data is copy to previous
		memcpy(&mach.rx_prev,&mach.rx,sizeof(mach.rx));

		// get rssi
		mach.rx.rssi = rssi;
		mach_rx_irq(&mach.rx);
	} else {								// match sequence number
#ifdef LAZURITE_IDE
		if(module_test & MODE_MACH_DEBUG) {
			printk(KERN_INFO"Same sequence number!! %s,%s,%d\n",__FILE__,__func__,__LINE__);
		}
#endif
	}

end:
	return status;
}

