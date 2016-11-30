
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

// local parameters
static MACH_PARAM mach;
static uint8_t ackbuf[32];

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
static bool mach_make_header(uint8_t *data, uint16_t *size, MAC_Header *header) {
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

error:
	return isValid;
}

/******************************************************************************/
/*! @brief parse mac header
  @param[in] *data start pointer of receiving data
  @param[in] size length of data
  @param[in] *header  pointer of mac header
  @return    false= invalid data, true valid data
  @exception  none
  @issue  move to mac
 ******************************************************************************/
static bool parse_data(const uint8_t *data, uint16_t size, ML7396_Header *header) {

	const uint8_t addr_len[] = {0,1,2,8};
	const uint8_t* ptr = data;
	uint16_t offset = 0;
	bool isValid = false;
	uint16_t min_len = 2;
	uint8_t panid_comp;

	const uint8_t payload = NULL;

	// framce control
	if (size < 2)
		goto error;
	header->fc = v2u16(ptr),ptr+=2,offset+=2;

	header->dstaddr.mode = GET_RX_ADDR_TYPE(header->fc);
	header->srcaddr.mode = GET_TX_ADDR_TYPE(header->fc);
	panid_comp = GET_PANID_COMP(header->fc);

	// addr type
	addr_type = panid_comp;
	addr_type + = header->srcaddr.mode ? 2: 0;
	addr_type + = header->dstaddr.mode ? 4: 0;
	header->addr_type = addr_type;

	// panid enb
	switch(addr_type)
	{
		case 0:
		case 3:
		case 5:
		case 7:
			header->dstpanid.enb = 0, header->srcpanid.enb = 0;
			break;
		case 1:
		case 4:
		case 6:
			header->dstpanid.enb = 1, header->srcpanid.enb = 0;
			min_len += 2;
			break;
		case 2:
			header->dstpanid.enb = 0, header->srcpanid.enb = 1;
			min_len += 2;
			break;
	}

	// packet length check
	if(GET_SEQ_ENB(header->seq)) min_len+=1;
}
min_len += addr_len[header->srcaddr.mode];
min_len += addr_len[header->dstaddr.mode];
if(min_len > size) goto error;
else isValid = true;

// sequence number
if (GET_SEC_ENB(header->fc)) {
	header->seq = *ptr,ptr++,offset++;
} else {
	header->seq = -1;
}
// dst panid
if(header->dstpanid.enb)
{
	header->dstpanid.panid = v2u16(ptr), ptr+=2,offset+=2;
}
// dst addr
memset(header->dstaddr.addr.addr64,0,8);
for(i=0;i< addr_len[header->dstaddr.mode];i++)
{
	header->dstaddr.addr.addr64[i] = *(ptr), ptr++,offset++;
}
// src panid
if(header->srcpanid.enb)
{
	header->srcpanid.panid = v2u16(ptr), ptr+=2,offset+=2;
}
// src addr
memset(header->srcaddr.addr.addr64,0,8);
for(i=0;i< addr_len[header->srcaddr.mode];i++)
{
	header->srcaddr.addr.addr64[i] = *(ptr), ptr++,offset++;
}
header->payload.data = ptr;
header->payload.len = size-offset;
error:
return isValid;
}

/******************************************************************************/
/*! @brief mach init 
  mac high layer initialization
  @return    pointer of MACH_PARAM
  @exception  return NULL
 ******************************************************************************/
MACH_PARAM *mach_init(void)
{
	memset(mac,0,sizeof(MACH_PARAM));
	get_mac_addr(&mac.dstaddr.addr.addr64);
	mac.phy = macl_init();
	if(mach.phy == NULL) return NULL;

	// set data buffer for ack
	mac.ack.data = ackbuf;
	mac.ack.size = sizeof(ackbuf);
	macl_sleep(on);

	return &mac;
}

/******************************************************************************/
/*! @brief mach start 
  mac high layer rx on
  @return    pointer of MACH_PARAM
  @exception  return NULL
 ******************************************************************************/
int mach_start() {
	// initialize phy  <== ml7396_reset();
	// l
	return status;
}

int mach_stop() {
}

int mach_setup(uint8_t ch, uint8_t rate, uint8_t txPower, uint8_t senseTime,uint8_t txRetry,uint16_t txInterval, uint8_t ccaWait) {
	uint8_t pages;
	int status;
	// set baudrate
	if (rate==50) pages = 1;
	else if (rate == 100) pages = 2;
	else 
	{
		status = -1;
		goto error;
	}

	// set channel
	if(macl_set_channel(pages,ch) != STATUS_OK){
		status = -1; 
		goto error;
	}

	// @issue txPower
	macl_set_txpower(mbm);

	// set setting CCA
	macl_set_csma_params(min_be,max_be,txRetry);
	macl_frame_retries(txRetry);
	macl_ch_scan(senseTime);				// add 
	// @issue  txInterval, ccaWait, 
	macl_set_cca_mode(const struct wpan_phy_cca *cca);
	macl_set_cca_ed_level(uint32_t mbm);
	macl_set_csma_params(uint8_t min_be, uint8_t max_be, uint8_t retries);
error:

	return status;
}

int mach_tx64(uint8_t *dstAddr, uint8_t @payload, uint16_t size,uint8_t addrType,void txCallback(uint8_t rssi, int16_t status)) {

}
int mach_tx(uint8_t panid, uint16_t dstAddr, uint8_t *payload, uint16_t size, uint8_t addrType,void (*txCallback(uint8_t rssi, int16_t status))) {

}
