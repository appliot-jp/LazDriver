#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include "ieee802154e.h"
uint8_t myaddr[8] ={0x00,0x1d,0x12,0x90,0x00,0x38,0x87,0xa4};
const uint8_t addr_size[]={0,1,2,8};
typedef struct {
	uint16_t len;
	uint8_t data[256];
} TEST_DATA;
TEST_DATA test[] ={{16,{0x01,0x28,0xED,0xCD,0xAB,0xA4,0x87,0x15,0x00,0x1D,0x00,0xE3,0x01,0x10,0x00,0xCA}},
	{49,{	0x21,0xA8,0x1A,0xCD,0xAB,0xA4,0x87,0x35,0x8E,0x53,0x65,0x6E,0x73,0x6F,0x72,0x44,
			0x61,0x74,0x61,0x2C,0x30,0x2E,0x30,0x30,0x30,0x2C,0x32,0x35,0x2E,0x33,0x2C,0x35,
			0x38,0x2E,0x36,0x2C,0x31,0x30,0x30,0x2C,0x32,0x30,0x30,0x2C,0x33,0x30,0x30,0x2C,
			0xD9}},
	{40,{	0x61,0xa8,0xcd,0xa4,0x87,0x35,0x8e,0x53,0x65,0x6e,0x73,0x6f,0x72,0x44,0x61,0x74,
			0x61,0x2c,0x32,0x38,0x2e,0x30,0x2c,0x36,0x32,0x2e,0x38,0x2c,0x31,0x30,0x30,0x2c,
			0x32,0x30,0x30,0x2c,0x33,0x30,0x30,0x2c}},
	{11,{0x21,0xa8,0x17,0xcd,0xab,0xa4,0x87,0x35,0x8e,0x07,0x00}},
	{11,{0x21,0xa8,0x17,0xcd,0xab,0xff,0xff,0x35,0x8e,0x07,0x00}}
};
void print_raw(t_MAC_DATA* pData)
{
	int i;
	printf("len=%04x\n",pData->len);
	for(i=0;i<pData->len;i++)
	{
		printf("%02x",pData->data[i]);
		switch(i%16)
		{
		case 8:
			printf("  ");
			break;
		case 15:
			printf("\r\n");
		default:
			printf(" ");
			break;
		}
	}
	printf("\r\n");
}

void print_mac_header(t_MAC_HEADER *pHdr)
{
	int i;
	printf("frm_typ = %02x\n",pHdr->frame_type);
	printf("sec_enb = %02x\n",pHdr->sec_enb);
	printf("pending = %02x\n",pHdr->pending);
	printf("ack_req = %02x\n",pHdr->ack_req);
	printf("seq_cmp = %02x\n",pHdr->seq_comp);
	printf("frm_ver = %02x\n",pHdr->frame_ver);

	// ielist
	printf("ielist  = %02x\n",pHdr->ielist.len);

	// rx_addr
	printf("rx_adr  = %02x %04x %02x ", pHdr->rx_addr.panid_enb,pHdr->rx_addr.panid, pHdr->rx_addr.addr_type);
	for(i=addr_size[pHdr->rx_addr.addr_type]-1;i>=0;--i)
	{
		printf("%02x",pHdr->rx_addr.addr.addr64[i]);
		//printf("%02x",i);
	}
	printf("\n");
	// tx_addr
	printf("tx_adr  = %02x %04x %02x ", pHdr->tx_addr.panid_enb,pHdr->tx_addr.panid, pHdr->tx_addr.addr_type);
	for(i=addr_size[pHdr->tx_addr.addr_type]-1;i>=0;--i)
	{
		printf("%02x",pHdr->tx_addr.addr.addr64[i]);
		//printf("%02x",i);
	}
	printf("\n");

}

void main(void)
{

	int status;
	uint16_t len;
	uint8_t tx_data[256];

	int i;
	int j;
	t_MAC_PARAM macParam;

	// data copy to mac 
	for(i=0;i<5;i++)
	{
		// dump raw
		printf("len = %d\n",test[i].len);
		for(j=0;j<test[i].len;j++)
		{
			printf("%02x ",test[i].data[j]);
			if(j==7) printf(" ");
			if(j==15) printf("\r\n");
		}
		printf("\r\n");
		// set up parametertest[i].len)
		macParam.myInfo.panid = 0xabcd;
		memcpy(&macParam.myInfo.myAddr.addr64[0],&myaddr[0],8);
		len = test[i].len;
		macParam.rxHdr.raw.data = tx_data;

		memcpy(macParam.rxHdr.raw.data,test[i].data, len);
		macParam.rxHdr.raw.len = len;
	
		// decode raw data to parameter
		dec_ieee802154e_header(&macParam.rxHdr,true);
		print_mac_header(&macParam.rxHdr);
	
	}

}
