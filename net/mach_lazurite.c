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
#include "mach_lazurite.h"
#include "macl_lazurite.h"
#include "errno.h"
#include "endian.h"
#include "arib_lazurite.h"

static MACH_PARAM mach;
/*! @uint8_t ackbuf[32]
  @brief  data buffer to make ack data
  */
static uint8_t ackbuf[32];

/******************************************************************************/
/*! @brief enb_dst_panid
  enb/dis of dst_panid/src_panid at each addrType
  0bit : addrType=0
  1bit : addrType=1
  ...
 */
const uint8_t enb_dst_panid = 0x04;
const uint8_t enb_src_panid = 0x52;
const uint8_t addr_len[] = {0x00,0x01,0x02,0x08};

// local functions
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


static int mach_make_header(uint8_t *data, uint16_t size, MACH_Header *header) {
	uint16_t offset;
	bool status=false;
	bool dst_ffff = true;
	int i;

	// set panid comp
	// panidcomp is as same as 0 bit of addrType
	header->fc.fc_bit.panid_comp = (header->addr_type&BIT(0)) ? 1:0;

	offset = 2;			// temporary skip frame control
	// sequence number
	if(!header->fc.fc_bit.seq_comp) {
		data[offset] = header->seq,offset++;
	}

	// dst panid
	if(enb_dst_panid&BIT(header->addr_type))
	{
		if(!header->dst.panid.enb)
		{
			status = -EINVAL;
			goto error;
		} else {
			H2LBS(data[offset],header->dst.panid.data), offset+=2;
		}
	}

	// dst addr
	// 2bit of addr type shows dst addr
	if(header->addr_type&BIT(2))
	{
		int i;
		switch(header->dst.addr_mode)
		{
			case 0:
				status = -EINVAL;
				goto error;
				break;
			case 1:
				if((header->dst.panid.data == 0xffff) ||(header->dst.panid.enb == false))
				{
					status = -EINVAL;
					goto error;
				}
				data[offset] = header->dst.addr.ldd_addr,offset++;
				if(header->dst.addr.ldd_addr != 0xff) dst_ffff = false;
				break;
			case 2:
				if((header->dst.panid.data == 0xffff) ||(header->dst.panid.enb == false))
				{
					status = -EINVAL;
					goto error;
				}
				H2LBS(data[offset],header->dst.addr.short_addr), offset+=2;
				if(header->dst.addr.short_addr != 0xffff) dst_ffff = false;
				break;
			case 3:
				break;
				for(i = 0;i<addr_len[header->dst.addr_mode];i++)
				{
					data[offset] = header->dst.addr.ieee_addr[i],offset++;
					if(header->dst.addr.ieee_addr[i] != 0xff) dst_ffff = false;
				}
		}
		if(dst_ffff) header->fc.fc_bit.ack_req=0;
	}

	// src panid
	if(enb_src_panid&BIT(header->addr_type))
	{
		if(header->src.panid.enb == 0)
		{
			status = -EINVAL;
			goto error;
		} else {
			H2LBS(data[offset],header->src.panid.data), offset+=2;
		}
	}
	// src addr
	if(header->addr_type & BIT(3))
	{
		switch(header->src.addr_mode)
		{
			case 0:
				status = false;
				goto error;
				break;
			case 1:
				data[offset] = header->src.addr.ldd_addr,offset++;
				break;
			case 2:
				H2LBS(data[offset],header->src.addr.short_addr), offset+=2;
				break;
			case 3:
				for(i = 0;i<addr_len[header->dst.addr_mode];i++)
				{
					data[offset] = header->dst.addr.ieee_addr[i],offset++;
				}
				break;
		}
	}
	status = STATUS_OK;

error:
	return status;
}

/******************************************************************************/
/*! @brief parse mac header
  @param[in] *data start pointer of receiving data
  @param[in] size length of data
  @param[in] *header  pointer of mac header
  @return    STATUS_OK, error num
  @exception ENOMEM = data size error
  @issue  move to mac
 ******************************************************************************/
int mach_parse_data(uint8_t *data, uint16_t size, MACH_Header *header) {

	const uint8_t addr_len[] = {0,1,2,8};
	uint16_t offset = 0;
	int status;
	int i;
	uint16_t min_len = 2;

	// framce control
	if (size < 2)
		status = -ENOMEM;
		goto error;
	LB2HS(header->fc,data[offset]),offset+=2;

	// addr type
	header->addr_type = header->fc.fc_bit.panid_comp;
	header->addr_type += (header->src.addr_mode ? 2: 0);
	header->addr_type += (header->dst.addr_mode ? 4: 0);

	// panid enb
	header->dst.panid.enb = (enb_dst_panid & BIT(header->addr_type)) ? 1: 0;
	header->src.panid.enb = (enb_src_panid & BIT(header->addr_type)) ? 1: 0;

	// packet length check
	if(header->dst.panid.enb) min_len+=2;
	if(header->src.panid.enb) min_len+=2;
	if(!header->fc.fc_bit.seq_comp) min_len+=1;
	min_len += addr_len[header->fc.fc_bit.src_addr_type];
	min_len += addr_len[header->fc.fc_bit.dst_addr_type];
	if(min_len > size)
	{
		status = -ENOMEM;
		goto error;
	}

	// sequence number
	if (header->fc.fc_bit.seq_comp) {
		header->seq = data[offset],offset++;
	}
	// dst panid
	if(header->dst.panid.enb)
	{
		LB2HS(header->dst.panid.data,header->dst.panid.data),offset+=2;
	}
	// dst addr
	memset(header->dst.addr.ieee_addr,0,8);
	for(i=0;i< addr_len[header->fc.fc_bit.dst_addr_type];i++)
	{
		header->dst.addr.ieee_addr[i] = data[offset],offset++;
	}
	// src panid
	if(header->src.panid.enb)
	{
		LB2HS(header->src.panid.data,data[offset]),offset+=2;
	}
	// src addr
	memset(header->src.addr.ieee_addr,0,8);
	for(i=0;i< addr_len[header->fc.fc_bit.src_addr_type];i++)
	{
		header->src.addr.ieee_addr[i] = data[offset],offset++;
	}
	header->payload.data = &data[offset];
	header->payload.len = size-offset;
	status = STATUS_OK;
error:
	return status;
}

/*********************************************************************/
/*! @brief mach init 
  mac high layer initialization
  @return    pointer of MACH_PARAM
  @exception  return NULL
 *********************************************************************/
MACH_PARAM *mach_init(void)
{
	memset(&mach,0,sizeof(MACH_PARAM));
	get_mac_addr(mach.myAddr.ieee_addr);
	mach.macl = macl_init();
	if(mach.macl == NULL) return NULL;

	// set data buffer for ack
	mach.ack.raw.data = ackbuf;
	mach.ack.raw.size = sizeof(ackbuf);
	mach.ack.raw.len = 0;
	macl_sleep(true);

	return &mach;
}

/********************************************************************/
/*! @brief mach start 
  mac high layer rx on
  @return     0=STATUS_OK, other = error
  @exception  return NULL
 ********************************************************************/
int mach_start(BUFFER *rxbuf) {
	int status = STATUS_OK;
	// initialize phy  <== ml7396_reset();
	mach.rx.raw.data = rxbuf->data;
	mach.rx.raw.size = rxbuf->size;
	mach.rx.raw.len = 0;
	return status;
}

/********************************************************************/
/*! @brief mach stop 
  mac high layer rx off
  @return    0=STATUS_OK
  @exception  EINVAL	invalid parameter
 ********************************************************************/
int mach_stop(void) {
	return macl_stop();
}

int mach_setup(RF_PARAM *rf) {
	int status;
	struct wpan_phy_cca cca;

	// set channel
	if(macl_set_channel(rf->pages,rf->ch) != STATUS_OK){
		status = -EINVAL; 
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
	macl_set_csma_params(rf->cca_min_be, rf->cca_max_be, rf->cca_retry);
error:
	return status;
}

/********************************************************************/
/*! @brief tx in mac high layer
  @param[in]	*dstAddr	64bit distination address
  @param[in]	*payload	start pointer of payload
  @param[in]	size		size of payload
  @param[in]	addrType	address type
  @param[in]	txCallback	callback at end of tx
  @return    0=STATUS_OK, other = error
  @exception  return NULL
 ********************************************************************/
void mach_set_dst_ieee_addr(uint8_t *addr)
{
	memcpy(mach.tx.dst.addr.ieee_addr,addr,sizeof(8));
}

void mach_set_dst_short_addr(uint16_t panid,uint16_t addr)
{
	mach.tx.dst.panid.data = panid;
	mach.tx.dst.addr.short_addr = addr;
}

/********************************************************************/
/*! @brief set my short address
  panid == 0xffff, 0xfffe	--> pan_coord is false
  panid == others			--> pan_coord is true
  @param[in]	panid	64bit distination address
  @param[in]	addr	start pointer of payload
  @return		status = STATUS_OK
  @exception	EINVAL: panid == 0xffff
 ********************************************************************/
int mach_set_my_short_addr(uint16_t panid,uint16_t short_addr)
{
	int status=STATUS_OK;
	if(panid == 0xffff) 
	{
		status = -EINVAL;
		goto error;
	}
	mach.myAddr.pan_id= panid;
	mach.myAddr.short_addr = short_addr;
	if( (short_addr == 0xffff) ||					// global address
			(short_addr == 0xfffe)) {				// address none
		mach.myAddr.pan_coord = false;
	} else {
		mach.myAddr.pan_coord = true;
	}
	if(!mach.promiscuous)
	{
		struct ieee802154_hw_addr_filt filt;
		filt.pan_id = mach.myAddr.pan_id;
		filt.pan_coord = mach.myAddr.pan_coord;
		filt.short_addr = mach.myAddr.short_addr;
		memcpy(filt.ieee_addr,mach.myAddr.ieee_addr,8);
		macl_set_hw_addr_filt(&filt,0x0f);			// update all of addr filter
	}
error:
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

int mach_send(BUFFER *txbuf)
{
	int status = STATUS_OK;

	mach.tx.raw.data = mach.macl->phy->out;
	mach.tx.raw.size = mach.macl->phy->buf_size;
	if((status = mach_make_header(txbuf->data,txbuf->len,&mach.tx))==STATUS_OK) {
		goto error;
	}
	if((arib_tx_check(mach.rf.pages,mach.rf.ch,mach.tx.raw.len))==false) {
		goto error;
	}
	status = macl_xmit_sync(mach.tx.raw);
	if(status == STATUS_OK)
		arib_tx_end(mach.rf.pages,mach.rf.ch,mach.tx.raw.len);

error:
	return status;
}
