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


#ifdef	LAZURITE_IDE
#include "lazurite.h"
#include "bp3596.h"
#include "string.h"
#include "lp_manage.h"
#else
#include <linux/string.h>
#endif
#include "subghz_api.h"
#include "mac-lazurite.h"


#define INIT_SLEEP
//#define TEST_SEND_INTERVAL



// local parameters
static void (*rx_callback)(uint8_t *data,uint8_t rssi,int status);
static void (*tx_callback)(uint8_t rssi,int status);

#define DEBUG

#ifndef DEBUG
static struct {
#else
struct {
#endif
	unsigned long start_time;
	unsigned long last_send_time;
	unsigned long total_send_bytes;
} arib = {0,0x80000000,0};

// local function

static SUBGHZ_MSG subghz_init(void)
{
	int result;
	SUBGHZ_MSG msg;
	result = mac.init();
	if(result!=0) 
	{
		msg = SUBGHZ_RESET_FAIL;
		goto error;
	}
	msg = SUBGHZ_OK;
	rx_callback = NULL;
	tx_callback = NULL;
error:
	return msg;
}

static SUBGHZ_MSG subghz_begin(uint8_t ch, uint16_t panid, SUBGHZ_RATE bps, SUBGHZ_POWER pwr)
{
	int result;
	SUBGHZ_MSG msg;
	result = mac.setup(ch,panid,bps,pwr);
	if(result != 0) 
	{
		msg = SUBGHZ_SETUP_FAIL;
		goto error;
	}
	msg = SUBGHZ_OK;
error:
	return msg;
}

static SUBGHZ_MSG subghz_close(void)
{
	int result;
	SUBGHZ_MSG msg;
	result = mac.close();
	if( result != SUBGHZ_OK)
	{
		msg = SUBGHZ_SLEEP_FAIL;
		goto error;
	}
	msg = SUBGHZ_OK;
error:
	return msg;
}

static SUBGHZ_MSG subghz_send(uint16_t dstPanid, uint16_t dstAddr, uint8_t *payload, uint16_t len, void (*callback)(uint8_t rssi, uint8_t status))
{
	uint8_t addrMode=6;
	SUBGHZ_MSG msg;
	int result;
	
	result = mac.send(dstPanid,dstAddr,addrMode,payload,len,NULL);
	if(result != SUBGHZ_OK)
	{
		msg = SUBGHZ_TX_FAIL;
		goto error_not_send;
	}
	msg = SUBGHZ_OK;
	
error_not_send:
	return msg;
}

static short subghz_readData(uint8_t *data, uint16_t max_size)
{
	short result = 0;
	
	return result;
}

static void subghz_rx_callback(uint8_t *raw,uint8_t rssi, int status)
{
	if(rx_callback != NULL) rx_callback(raw,rssi,status);
	return ;
}
static SUBGHZ_MSG subghz_rxEnable(void (*callback)(uint8_t *raw,uint8_t rssi, int status))
{
	SUBGHZ_MSG msg;
	rx_callback = callback;
	msg = mac.rxEnable(subghz_rx_callback);
	
	return msg;
}

static SUBGHZ_MSG subghz_rxDisable(void)
{
	SUBGHZ_MSG msg;
	int result;
	
	result = mac.rxDisable();
	if(result != SUBGHZ_OK)
	{
		msg = SUBGHZ_RX_DIS_FAIL;
	}
	msg = SUBGHZ_OK;
	return msg;
}

static void subghz_getStatus(SUBGHZ_STATUS *tx, SUBGHZ_STATUS *rx)
{
	return;
}

static SUBGHZ_MSG subghz_getMyAddress64(uint8_t* addr)
{
	SUBGHZ_MSG msg;
	uint8_t addr64[8]; 
	msg = mac.getMyAddr64(addr64);
	memcpy(addr,addr64,8);
	return msg;
}

static uint16_t subghz_getMyAddress(void)
{
	uint16_t addr16;
	mac.getMyAddr(&addr16);
	return addr16;
}

static void subghz_msgOut(SUBGHZ_MSG msg)
{
	char message[32];
	
	switch (msg)
	{
	case SUBGHZ_RESET_FAIL:
		strncpy(message,"RESET FAIL\t",31);
		break;
	case SUBGHZ_SETUP_FAIL:
		strncpy(message,"SETUP FAIL\t",31);
		break;
	case SUBGHZ_SLEEP_FAIL:
		strncpy(message,"SLEEP FAIL\t",31);
		break;
	case SUBGHZ_WAKEUP_FAIL:
		strncpy(message,"WAKEUP FAIL\t",31);
		break;
	case SUBGHZ_MYADDR_FAIL:
		strncpy(message,"get My Address FAIL\t",31);
		break;
	case SUBGHZ_SETFIL_FAIL:
		strncpy(message,"set filter FAIL\t",31);
		break;
	case SUBGHZ_TX_COMP_FAIL:
		strncpy(message,"Send Complete FAIL\t",31);
		break;
	case SUBGHZ_TX_FAIL:
		strncpy(message,"Send FAIL\t",31);
		break;
	case SUBGHZ_TX_ACK_FAIL:
		strncpy(message,"ACK of send FAIL\t",31);
		break;
	case SUBGHZ_RX_ENB_FAIL:
		strncpy(message,"Recv Enable FAIL\t",31);
		break;
	case SUBGHZ_RX_DIS_FAIL:
		strncpy(message,"Recv Disable FAIL\t",31);
		break;
	case SUBGHZ_PANID:
		strncpy(message,"set PANID FAIL\t",31);
		break;
	default:
		goto no_error;
		break;
	}
	//Serial.print(message);

no_error:
	//Serial.print("RSSI=");
	//Serial.print_long((long)subghz_param.tx_stat.rssi,DEC);
	//Serial.print("\tSTATUS=");
	//Serial.println_long((long)subghz_param.tx_stat.status,DEC);
	return;
}

static SUBGHZ_MSG subghz_getSendMode(SUBGHZ_PARAM *param)
{

	return SUBGHZ_OK;
}

static SUBGHZ_MSG subghz_setSendMode(SUBGHZ_PARAM *param)
{
	return SUBGHZ_OK;
}
static SUBGHZ_MSG subghz_remove(void) 
{
	return SUBGHZ_OK;
}

// setting of function
const SubGHz_CTRL SubGHz = {
	subghz_init,
	subghz_remove,
	subghz_begin,
	subghz_close,
	subghz_send,
	subghz_rxEnable,
	subghz_rxDisable,
	subghz_readData,
	subghz_getMyAddress,
	subghz_getMyAddress64,
	subghz_getStatus,
	subghz_msgOut,
	subghz_setSendMode,
	subghz_getSendMode,
};
