/* mach.c - MAC(High level) for lazurite
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

#ifdef SUBGHZ_OTA
	#pragma SEGCODE "OTA_SEGCODE"
	#pragma SEGINIT "OTA_SEGINIT"
	#pragma SEGNOINIT "OTA_SEGNOINIT"
	#pragma SEGCONST "OTA_SEGCONST"
#endif

#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	#include "common-lzpi.h"
#endif

#ifdef LAZURITE_IDE
	#include "driver_uart.h"
#endif

#include "mach.h"
#include "aes/aes.h"
#include "errno.h"
#include "endian.h"

static struct mach_param mach;
/*! @uint8_t ackbuf[32]
  @brief  data buffer to make ack data
 */
static uint8_t rx_enhance_ack_buffer[16];
static BUFFER tx_enhance_ack;
static BUFFER rx_enhance_ack;
/******************************************************************************/
/*! @brief enb_dst_panid
	enb/dis of dst_panid/src_panid at each addrType
0bit : addrType=0
1bit : addrType=1
...
 */
static const uint8_t enb_dst_panid = 0x52;
static const uint8_t enb_src_panid = 0x04;
static const uint8_t addr_len[] = {0x00,0x01,0x02,0x08};
static const uint8_t ieee_addr_ffff[] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

/******************************************************************************/
/*! @brief get 64bit address
  @param[in] *macaddr	pointer of 64bit mac address
  @return    STATUS_OK	ok
  @exception	EIO hardware error
 ******************************************************************************/
int	get_mac_addr(uint8_t *macaddr)
{
	int status=STATUS_OK;
	int i;
	uint8_t rdata[8];

	HAL_I2C_read((uint8_t)0x20,(uint8_t*)rdata,(uint8_t)8);

	for (i=0;i<8;i++)
	{
		macaddr[i] = rdata[7-i];
	}
	if(status != STATUS_OK)
	{
		status = -EIO;
	}

	return status;
}

// local functions
/******************************************************************************/
/*! @brief make raw data
  @param[in] *header  pointer of mac header<br>
  ack_reg (1: auto, 0: no ack)<br>
  panid_comp,dst_addr_type,src_addr_type are generated from addr_type<br>
  payload	buffer of payload<br>
  raw		output buffer<br>
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
	uint8_t pad;
	uint16_t offset = 2;
	int status;
	bool dst_ffff = true;
	int i;

	// sequence number
	if(!header->fc.fc_bit.seq_comp) {
		if(header->raw.size >= (offset + 1)){
			header->seq++;
			header->raw.data[offset]=header->seq,offset++;
		} else {
			status = -ENOMEM;
			goto error;
		}
	}

	// dst panid
	if(enb_dst_panid&BIT(header->addr_type))
	{
		if((!header->dst.panid.enb) || (header->dst.panid.data == 0xFFFE))
		{
			status = -EINVAL;
			goto error;
		} else {
			if(header->raw.size >= (offset + 2)){
				H2LBS(header->raw.data[offset],header->dst.panid.data), offset+=2;
			} else {
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
				printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
#endif
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
			case 1:
				if((header->dst.panid.data == 0xffff) ||
						(header->dst.panid.data == 0xfffe)||
						(header->dst.panid.enb == false))
				{
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
					printk(KERN_ERR"invalid panid for short address.%s,%s,%d\n", __FILE__, __func__, __LINE__);
#endif
					status = -EINVAL;
					goto error;
				}
				if(header->raw.size >= (offset + addr_len[1])){
					header->fc.fc_bit.dst_addr_type = IEEE802154_FC_ADDR_LDD;
					header->raw.data[offset] = header->dst.addr.lddn_addr,offset++;
					if(header->dst.addr.lddn_addr != 0xff) dst_ffff = false;
				} else {
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
					printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
#endif
					status = -ENOMEM;
					goto error;
				}
				break;
			case 2:
				if(((header->dst.panid.data == 0xffff)&&(header->dst.addr.short_addr!=0xffff)) ||
						(header->dst.panid.data == 0xfffe) ||
						(header->dst.panid.enb == false))
				{
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
					printk(KERN_ERR"invalid panid for short address.%s,%s,%d\n", __FILE__, __func__, __LINE__);
#endif
					status = -EINVAL;
					goto error;
				}
				if(header->raw.size >= (offset + addr_len[2])){
					header->fc.fc_bit.dst_addr_type = IEEE802154_FC_ADDR_SHORT;
					H2LBS(header->raw.data[offset],header->dst.addr.short_addr), offset+=2;
				} else {
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
					printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
#endif
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
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
					printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
#endif
					status = -ENOMEM;
					goto error;
				}
				break;
			default:				// addr_type = 0
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
				printk(KERN_ERR"dst address is not set in %s,%s,%d\n", __FILE__, __func__, __LINE__);
#endif
				status = -EINVAL;
				goto error;
				break;
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
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
			printk(KERN_ERR"src panid is invalid in %s,%s,%d\n", __FILE__, __func__, __LINE__);
#endif
			status = -EINVAL;
			goto error;
		} else {
			if(header->raw.size >= (uint16_t)(offset + sizeof(uint16_t))){
				H2LBS(header->raw.data[offset],header->src.panid.data), offset+=2;
			} else {
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
				printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
#endif
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
			case 1:
				if(header->raw.size < (offset + addr_len[1])){
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
					printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
#endif
					status = -ENOMEM;
					goto error;
				}
				if(header->src.addr.lddn_addr==0xff){
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
					printk(KERN_ERR"invalid src LDD address. %s,%s,%d\n", __FILE__, __func__, __LINE__);
#endif
					status = -EINVAL;
					goto error;
				}
				header->raw.data[offset] = header->src.addr.lddn_addr,offset++;
				header->fc.fc_bit.src_addr_type = IEEE802154_FC_ADDR_LDD;
				break;
			case 2:
				if(header->raw.size < (offset + addr_len[2])){
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
					printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
#endif
					status = -ENOMEM;
					goto error;
				}
				if(header->src.addr.short_addr==0xffff)
				{
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
					printk(KERN_ERR"invalid src short address. %s,%s,%d\n", __FILE__, __func__, __LINE__);
#endif
					status = -EINVAL;
					goto error;
				}
				H2LBS(header->raw.data[offset],header->src.addr.short_addr), offset+=2;
				header->fc.fc_bit.src_addr_type = IEEE802154_FC_ADDR_SHORT;
				break;
			case 3:
				if(header->raw.size < (offset + addr_len[3])){
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
					printk(KERN_ERR"memory error in %s,%s,%d\n", __FILE__, __func__, __LINE__);
#endif
					status = -ENOMEM;
					goto error;
				}
				for(i = 0;i<addr_len[header->src.addr_type];i++)
				{
					header->raw.data[offset] = header->src.addr.ieee_addr[i],offset++;
				}
				header->fc.fc_bit.src_addr_type = IEEE802154_FC_ADDR_IEEE;
				break;
			default:					// addr_type = 0
				status = -EINVAL;
				goto error;
				break;
		}
	} else {
		header->fc.fc_bit.dst_addr_type = IEEE802154_FC_ADDR_NONE;
	}

	// copy payload to raw buffer
	header->fc.fc_bit.panid_comp = header->addr_type & 0x01;
	header->fc.fc_bit.nop = 0;
	if(header->payload.len != 0) {
		uint8_t keyStatus = AES128_getStatus();
		if (keyStatus){
			header->fc.fc_bit.sec_enb = 1;
			if(header->raw.size >= ((header->payload.len&0xFFF0)+16+offset)) {
				if (mach.rx.fc.fc_bit.seq_comp){
					pad = AES128_CBC_encrypt(&header->raw.data[offset], header->payload.data, (uint32_t)header->payload.len,0) ;
				}else{
					pad = AES128_CBC_encrypt(&header->raw.data[offset], header->payload.data, (uint32_t)header->payload.len,header->seq) ;
				}
				offset += pad;
			} else {
				status = -ENOMEM;
				goto error;
			}
		} else {
			if(header->raw.size >= (offset + header->payload.len)) {
				memcpy(&header->raw.data[offset], header->payload.data, header->payload.len);
			} else {
				status = -ENOMEM;
				goto error;
			}
		}
	}
	offset+=header->payload.len;
	header->raw.len = offset;

	// write mac header
	H2LBS(header->raw.data[0],header->fc.fc16);

#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s %s %d\n",__FILE__,__func__,__LINE__);
#endif

	status = STATUS_OK;

error:
	return status;
}

/******************************************************************************/
/*! @brief prawarse mac header
	@param[in] header pointer of mac header<br>
	input = input buffer<br>
	raw   = output buffer<br>
	payload = pointer/length of payload<br>
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
	header->dst.panid.enb = (uint8_t)((enb_dst_panid & BIT(header->addr_type)) ? 1: 0);
	header->src.panid.enb = (uint8_t)((enb_src_panid & BIT(header->addr_type)) ? 1: 0);

	// sequence number
	if (!header->fc.fc_bit.seq_comp) {
		header->seq = header->input.data[offset],offset++;
	}
	// dst panid
	if(header->dst.panid.enb)
	{
		LB2HS(header->dst.panid.data,header->input.data[offset]),offset+=2;
	} else {
		header->dst.panid.data = 0xFFFF;
	}
	// dst addr
	if(header->fc.fc_bit.dst_addr_type != 0) {
		memset(header->dst.addr.ieee_addr,0,8);
		for(i=0;i< addr_len[header->fc.fc_bit.dst_addr_type];i++)
		{
			header->dst.addr.ieee_addr[i] = header->input.data[offset],offset++;
		}
	} else {
		memset(header->dst.addr.ieee_addr,0xff,8);
	}
	// src panid
	if(header->src.panid.enb)
	{
		LB2HS(header->src.panid.data,header->input.data[offset]),offset+=2;
	} else {
		header->src.panid.data = 0xFFFF;
	}
	// src addr
	if(header->fc.fc_bit.src_addr_type != 0) {
		memset(header->src.addr.ieee_addr,0,8);
		for(i=0;i< addr_len[header->fc.fc_bit.src_addr_type];i++)
		{
			header->src.addr.ieee_addr[i] = header->input.data[offset],offset++;
		}
	} else {
		memset(header->src.addr.ieee_addr,0xff,8);
	}

	header->raw.len = header->input.len; // last byte is rss
	header->payload.data = (uint8_t *)(header->raw.data+offset);
	header->payload_offset = offset;
	header->payload.len = header->input.len - offset;

	status = STATUS_OK;

	return status;
}

/******************************************************************************/
/*! @brief compare sequence number and address<br>
	when seqnence number and address of current rx is as same as the previous, rx data is sent as retry.

	@return    true=match false=unmatch
 ******************************************************************************/
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

#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACH_DEBUG) {
		printk(KERN_INFO"%s %s %d\n",__FILE__,__func__,__LINE__);
	}
#endif
	if( ((mach.rx.addr_type == 6) || (mach.rx.addr_type == 7)) &&
			(mach.rx.fc.fc_bit.ack_req) &&
			(((mach.rx.dst.addr_type == IEEE802154_FC_ADDR_SHORT) && (mach.rx.dst.addr.short_addr != 0xFFFF)) ||
			 ((mach.rx.dst.addr_type == IEEE802154_FC_ADDR_IEEE) &&
				((mach.rx.dst.addr.ieee_addr[0] != 0xFF) ||(mach.rx.dst.addr.ieee_addr[1] != 0xFF) ||
				 (mach.rx.dst.addr.ieee_addr[2] != 0xFF) ||
				 (mach.rx.dst.addr.ieee_addr[3] != 0xFF) ||
				 (mach.rx.dst.addr.ieee_addr[4] != 0xFF) ||
				 (mach.rx.dst.addr.ieee_addr[5] != 0xFF) ||
				 (mach.rx.dst.addr.ieee_addr[6] != 0xFF) ||
				 (mach.rx.dst.addr.ieee_addr[7] != 0xFF))
			 ))) {
		// genenrate ack data
		mach.ack.fc.fc16 = 0;
		mach.ack.fc.fc_bit.frame_type = IEEE802154_FC_TYPE_ACK;
		//	mach.ack.fc.fc_bit.panid_comp = 1;
		mach.ack.fc.fc_bit.panid_comp = 0;
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
		if(tx_enhance_ack.len>0) {
			int16_t enhance_ack_rx_num = *((int16_t *)(tx_enhance_ack.data+0));
			int16_t enhance_ack_size = *((int16_t *)(tx_enhance_ack.data+2));
			uint16_t src_target;
			int16_t enhance_ack_offset = 4;
			do {
				src_target = *(tx_enhance_ack.data+enhance_ack_offset+1);
				src_target = src_target + *(tx_enhance_ack.data+enhance_ack_offset);
				if ((src_target == 0xffff ) || (src_target == mach.rx.src.addr.short_addr)) {
					memcpy(&mach.ack.raw.data[offset],&tx_enhance_ack.data[enhance_ack_offset+2],enhance_ack_size);
					offset += enhance_ack_size;
					break;
				} else {
					enhance_ack_offset += (enhance_ack_size+2);
				}
				enhance_ack_rx_num--;
			} while(enhance_ack_rx_num>0);
		}
		mach.ack.raw.len = offset;
		mach.macl->phy->out.len = offset;
	}

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
	mach.macl = macl_init(&mach);
	if(mach.macl == NULL) {
		goto error;
	}

	// initialize buffer
	mach.rx.input.data = mach.macl->phy->in.data;
	mach.rx.input.size = mach.macl->phy->in.size;
	mach.tx.raw.data = mach.macl->phy->out.data;
	mach.tx.raw.size = mach.macl->phy->out.size;
	mach.ack.raw.data = mach.macl->phy->out.data;
	mach.ack.raw.size = mach.macl->phy->out.size;
	tx_enhance_ack.data = NULL;
	tx_enhance_ack.size = 0;
	tx_enhance_ack.len = 0;
	rx_enhance_ack.data = rx_enhance_ack_buffer;
	rx_enhance_ack.size = sizeof(rx_enhance_ack_buffer);
	rx_enhance_ack.len = 0;
	macl_sleep();
	get_mac_addr(mach.my_addr.ieee_addr);

	return &mach;
error:
	return NULL;
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

#if !defined(LAZURITE_IDE) && defined(DEBUG)
	printk(KERN_INFO"%s %s %d macl_start\n",__FILE__,__func__,__LINE__);
#endif
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

/********************************************************************/
/*! @brief setup rx parameters
	@return    STATUS_OK
	@exception  depends on macl_stop
 ********************************************************************/
int mach_setup(struct rf_param *rf) {
	int status;

	// link parameter
	mach.rf = rf;

	// set modulation
	status = macl_set_modulation(rf->modulation,rf->dsssSF);
	if(status != STATUS_OK) goto error;

	// set channel & txpow
	status = macl_set_channel(rf->pages,rf->ch,rf->tx_power,rf->antsw);
	if(status != STATUS_OK){
		goto error;
	}

	// set setting CCA
	status = macl_set_frame_retries(rf->tx_retry,(uint32_t)rf->ack_timeout);
	if(status != STATUS_OK) goto error;

	// set CSMA PARAM
	//if((status = macl_cca_ed_level(rf->cca_level)) != STATUS_OK) goto error;
	// set CSMA PARAM
	status = macl_set_csma_params(rf->cca_min_be,rf->cca_max_be, rf->cca_retry);
	if(status != STATUS_OK) goto error;
error:
	return status;
}

/********************************************************************/
/*! @brief set 64bit address for distination
	@param[in]	panid	panid
	@param[in]	*addr	64bit distination address
	@return    STATUS_OK
	@exception none
 ********************************************************************/
int mach_set_dst_ieee_addr(uint16_t panid,uint8_t *addr)
{
	mach.tx.dst.panid.enb = true;
	mach.tx.dst.panid.data = panid;
	mach.tx.dst.addr_type = IEEE802154_FC_ADDR_IEEE;
	memcpy(mach.tx.dst.addr.ieee_addr,addr,8);
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACH_DEBUG) {
		printk(KERN_INFO"%s %s %d\n",__FILE__,__func__,__LINE__);
		printk(KERN_INFO"dst: %04x %02x%02x%02x%02x%02x%02x%02x%02x\n",
				mach.tx.dst.panid.data,
				mach.tx.dst.addr.ieee_addr[7],
				mach.tx.dst.addr.ieee_addr[6],
				mach.tx.dst.addr.ieee_addr[5],
				mach.tx.dst.addr.ieee_addr[4],
				mach.tx.dst.addr.ieee_addr[3],
				mach.tx.dst.addr.ieee_addr[2],
				mach.tx.dst.addr.ieee_addr[1],
				mach.tx.dst.addr.ieee_addr[0]
				);
	}
#endif
	return STATUS_OK;
}

/********************************************************************/
/*! @brief set src address according to addr_type
	@param[in]	addr_type	address type(0: omit, 1:8bit ldd, 2: 16bit, 3: 64bit
	@return    STATUS_OK
 ********************************************************************/
int mach_set_src_addr(uint8_t addr_type)
{
	int status=STATUS_OK;
	switch(addr_type)
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

/********************************************************************/
/*! @brief set dst short address
	@param[in]	addr_type	address type(0: omit, 1:8bit ldd, 2: 16bit, 3: 64bit
	@return    STATUS_OK
 ********************************************************************/
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
	if((panid == 0xffff) || (panid == 0xfffe) || (short_addr == 0xffff))
	{
		mach.my_addr.pan_coord = false;
		//status = -EINVAL;
	} else {
		mach.my_addr.pan_coord = true;
	}

	if(!mach.macl->bit_params.promiscuousMode)
	{
		struct ieee802154_my_addr filt;
		filt.pan_id = mach.my_addr.pan_id;
		filt.pan_coord = mach.my_addr.pan_coord;
		filt.short_addr = mach.my_addr.short_addr;
		memcpy(filt.ieee_addr,mach.my_addr.ieee_addr,8);
		macl_set_hw_addr_filt(&filt,0x0fL);			// update all of addr filter
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
int mach_set_coord_addr(uint16_t panid,uint16_t short_addr,uint8_t *ieee_addr) {
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

int mach_set_promiscuous(bool on) {
	int status;
	if (macl_set_promiscuous_mode(on)==STATUS_OK) {
		status = STATUS_OK;
	} else {
		status = -EIO;
	}
	return status;
}

int mach_tx(struct mac_fc_alignment fc,uint8_t addr_type,BUFFER *txbuf) {

	int status = STATUS_OK;
	// initializing buffer
	mach.tx.payload.data = txbuf->data;
	mach.tx.payload.size = txbuf->size;
	mach.tx.payload.len = txbuf->len;
	mach.tx.addr_type = addr_type;
	memcpy(&mach.tx.fc.fc_bit,&fc,sizeof(fc)) ;

	status = mach_make_header(&mach.tx);
	if(status != STATUS_OK) {
		return status;
	}

#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACH_DEBUG) printk(KERN_INFO"%s %s %d\n",__FILE__,__func__,__LINE__);
#endif
	//printk(KERN_INFO"PAYLOAD\n");
	//PAYLOADDUMP(mach.tx.payload.data,mach.tx.payload.len);
	mach.sending = true;
	status = macl_xmit_sync(mach.tx.raw);

	return status;
}

int mach_sleep(void)
{
	return macl_sleep();
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
int macl_rx_irq(bool *isAck)
{
	int status;
	// end of sending ack during rx
	//Serial.println("macl_rx_irq");
	if(isAck) {
		// receiving data during tx
		// set rx buffer
		mach.rx.input.len = mach.macl->phy->in.len-1;					// erase rssi
		mach.rx.rssi = mach.rx.input.data[mach.rx.input.len];

		if(mach.macl->bit_params.promiscuousMode) {
			status = mach_parse_data(&mach.rx);
			if(status != STATUS_OK) {
				return status;
			}
			if(mach.rx.raw.size >= mach.rx.input.len) {
				mach.rx.raw.len = mach.rx.input.len;
				mach.macl->status = STATUS_OK;
				memcpy(mach.rx.raw.data,mach.rx.input.data,mach.rx.raw.len);
			} else {
				mach.rx.raw.len = mach.rx.raw.size;
				status = -ENOMEM;
			}
			*isAck = false;
		} else {
			status = mach_parse_data(&mach.rx);
			if(status != STATUS_OK) {
				return status;
			}
			if(
					(mach.rx.dst.addr_type == 0)||
					((mach.rx.dst.addr_type == 2) && 
					 ((mach.rx.dst.panid.enb == false) || (mach.rx.dst.panid.data == mach.my_addr.pan_id) || (mach.rx.dst.panid.data == 0xffff)) && 
					 ((mach.rx.dst.addr.short_addr == mach.my_addr.short_addr) || (mach.rx.dst.addr.short_addr==0xffff))) ||
					((mach.rx.dst.addr_type == 3) && 
					 ((memcmp(mach.rx.dst.addr.ieee_addr,mach.my_addr.ieee_addr,8)==0)||(memcmp(mach.rx.dst.addr.ieee_addr,ieee_addr_ffff,8)==0)))
				) {
				// data frame and cmd frame
				switch(mach.rx.fc.fc_bit.frame_type){
					case IEEE802154_FC_TYPE_DATA:
					case IEEE802154_FC_TYPE_CMD:
						// check sequence number
						if(mach.rx.raw.size >= mach.rx.input.len) {
							mach.rx.raw.len = mach.rx.input.len;
							mach.macl->status = STATUS_OK;
							memcpy(mach.rx.raw.data,mach.rx.input.data,mach.rx.raw.len);
							if((mach.rx.fc.fc_bit.ack_req) && (mach_make_ack_header())) {
								*isAck = true;
							} else {
								*isAck = false;
							}
						} else {
							mach.rx.raw.len = 0;
							status = -ENOMEM;
							*isAck = false;
						}
						break;
					case IEEE802154_FC_TYPE_ACK:
						// ack process
						mach.tx.rssi = mach.rx.rssi;
						rx_enhance_ack.len = (rx_enhance_ack.size < mach.rx.payload.len) ? rx_enhance_ack.size : mach.rx.payload.len;
						memcpy(rx_enhance_ack.data,&mach.rx.input.data[mach.rx.payload_offset],rx_enhance_ack.len);
						return STATUS_OK;
					default:
						break;
				}
			} else {
				status = -EADDRNOTAVAIL;
				return status;
			}
		}
	} else {
		// reporting data to upper layer
		if(mach.macl->status == STATUS_OK) {
			// copy phy buffer to application buffer
			if((mach.macl->bit_params.promiscuousMode)||
					(mach_match_seq_num()==false)) {
				memcpy(&mach.rx_prev,&mach.rx,sizeof(mach.rx));
				switch(mach.rx.fc.fc_bit.frame_type) {
				case IEEE802154_FC_TYPE_DATA:
					mach_rx_irq(mach.macl->status,NULL);				// report data to upper layer
					break;
				case IEEE802154_FC_TYPE_CMD:
					mach.macl->rxcmd = true;
					break;
				default:
					break;
				}
			}
		} else {
			mach_rx_irq(mach.macl->status,NULL); // report error to upper layer
		}
	}
	return STATUS_OK;
}

void mach_get_enhance_ack(uint8_t **data,int *size){
	*data = rx_enhance_ack.data;
	*size = rx_enhance_ack.len;
	return;
}
bool mach_set_enhance_ack(uint8_t* data, int size) {
	bool result=false;
	if((data == NULL) || (size == 0)) {
		tx_enhance_ack.data = NULL;
		tx_enhance_ack.len = 0;
		tx_enhance_ack.size = 0;
	}
	else if(size >= 0) {
		result = true;
		tx_enhance_ack.data=data;
		tx_enhance_ack.len = size;
		tx_enhance_ack.size = size;
	} else {
		result = false;
	}
	return result;
}
void mach_set_ack_tx_interval(uint16_t interval){
	macl_set_ack_tx_interval(interval);
}
void mach_set_antsw(uint8_t antsw) {
	macl_set_antsw(antsw);
}
