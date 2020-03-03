/* subghz_api.h
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


#ifndef	_SUBGHZ_API_H_
#define _SUBGHZ_API_H_

#if !defined(JP)
	#error Missing area code macro definie.
#endif
//#include "common_lazurite.h"
#include "mach.h"

// subghz api_status
#define SUBGHZ_API_NONE				( 0x00 )
#define SUBGHZ_API_INIT				( 0x01 )
#define SUBGHZ_API_BEGIN			( 0x02 )
#define SUBGHZ_API_SEND				( 0x04 )
#define SUBGHZ_API_RXENABLE		( 0x08 )
#define SUBGHZ_API_CLOSE		( 0x10 )
#define SUBGHZ_API_HOPPING_SYNC_SLAVE_ISR		( 0x20 )
#define SUBGHZ_API_HOPPING_SYNC_HOST_ISR		( 0x40 )
#define SUBGHZ_HOPPING				( 0xF0 )
#define SUBGHZ_HOPPING_TS_H		( SUBGHZ_HOPPING + 0 )
#define SUBGHZ_HOPPING_TS_S		( SUBGHZ_HOPPING + 1 )
#define SUBGHZ_HOPPING_PB_H		( SUBGHZ_HOPPING + 2 )
#define SUBGHZ_HOPPING_PB_S		( SUBGHZ_HOPPING + 3 )

#define SUBGHZ_HOPPING_SEARCH_CYCLE				2
#define SUBGHZ_HOPPING_SEARCH_INTERVAL		200
#define SUBGHZ_HOPPING_CH_DURATION				1000

#define SUBGHZ_HOPPING_SYNC_FRAME_SIZE 16
struct subghz_hopping_sync_frame {
	uint8_t cmd;
	uint8_t index;
	uint8_t size;
	uint8_t reserve;
	uint32_t sync_interval;
	uint32_t sync_from;
	uint32_t base;
	uint8_t data[32];
};
extern uint8_t subghz_api_status;

typedef enum {
	SUBGHZ_OK = 0,
	SUBGHZ_RESET_FAIL,			// 1
	SUBGHZ_SETUP_FAIL,			// 2
	SUBGHZ_SLEEP_FAIL,			// 3
	SUBGHZ_WAKEUP_FAIL,			// 4
	SUBGHZ_MYADDR_FAIL,			// 5
	SUBGHZ_SETFIL_FAIL,			// 6
	SUBGHZ_TX_COMP_FAIL,		// 7
	SUBGHZ_TX_FAIL,				// 8
	SUBGHZ_TX_CCA_FAIL,			// 9
	SUBGHZ_TX_ACK_FAIL,			// 10
	SUBGHZ_RX_ENB_FAIL,			// 11
	SUBGHZ_RX_DIS_FAIL,			// 12
	SUBGHZ_RX_COMP_FAIL,		// 13
	SUBGHZ_ERR_ADDRTYPE,		// 14
	SUBGHZ_TTL_SEND_OVR,		// 15
	SUBGHZ_DEAD_LOCK,				// 16
	SUBGHZ_SYNC_FAIL,				// 17
	SUBGHZ_RATE_FAIL,
	SUBGHZ_DUMMY						// --
} SUBGHZ_MSG;

// rate parameters
typedef enum {
	SUBGHZ_50KBPS  = 50,
	SUBGHZ_50KCPS = 51,
	SUBGHZ_100KBPS = 100,
	SUBGHZ_100KCPS = 101,
	SUBGHZ_200KCPS = 201
} SUBGHZ_RATE;

// txPower parameters
typedef enum {
	SUBGHZ_PWR_20MW = 20,
	SUBGHZ_PWR_1MW = 1
} SUBGHZ_POWER;

typedef struct {
	uint8_t rssi;
	int status;
} SUBGHZ_STATUS;

typedef struct{
	uint8_t addrType;
	uint8_t senseTime;
	uint8_t txRetry;
	uint16_t txInterval;
	uint16_t myAddress;
	uint16_t ccaWait;
} SUBGHZ_PARAM;

typedef struct{
	union mac_frame_control mac_header;
	uint8_t seq_num;
	uint8_t addr_type;
	uint16_t dst_panid;
	uint8_t  dst_addr[8];
	uint16_t src_panid;
	uint8_t  src_addr[8];
	uint8_t *raw;
	int16_t raw_len;
	uint8_t *payload;
	int16_t payload_len;
} SUBGHZ_MAC_PARAM;

typedef struct
{
	SUBGHZ_MSG (*init)(void);
	SUBGHZ_MSG (*remove)(void);
	SUBGHZ_MSG (*begin)(uint8_t ch, uint16_t panid, SUBGHZ_RATE rate, SUBGHZ_POWER txPower);
	SUBGHZ_MSG (*close)(void);
	SUBGHZ_MSG (*send)(uint16_t panid, uint16_t dstAddr, uint8_t *data, uint16_t len, void (*callback)(uint8_t rssi, int status));
	SUBGHZ_MSG (*send64le)(uint8_t *dstAddr_le, uint8_t *data, uint16_t len, void (*callback)(uint8_t rssi, int status));
	SUBGHZ_MSG (*send64be)(uint8_t *dstAddr_be, uint8_t *data, uint16_t len, void (*callback)(uint8_t rssi, int status));
	SUBGHZ_MSG (*rxEnable)(void (*callback)(const uint8_t *data, uint8_t rssi, int status));
	SUBGHZ_MSG (*setPromiscuous)(bool on);
	int (*getEd)(int mode,uint8_t **data,int *size);
	SUBGHZ_MSG (*setAckReq)(bool on);
	SUBGHZ_MSG (*setBroadcastEnb)(bool on);
	SUBGHZ_MSG (*rxDisable)(void);
	short (*readData)(uint8_t *data, uint16_t max_size);
	uint16_t (*getMyAddress)(void);
	void (*getMyAddr64)(uint8_t *addr);
	SUBGHZ_MSG (*setMyAddress)(uint16_t my_address);
	void (*getStatus)(SUBGHZ_STATUS *tx, SUBGHZ_STATUS *rx);
	void (*msgOut)(SUBGHZ_MSG msg);
	SUBGHZ_MSG (*setSendMode)(SUBGHZ_PARAM *param);
	SUBGHZ_MSG (*getSendMode)(SUBGHZ_PARAM *param);
	void (*decMac)(SUBGHZ_MAC_PARAM *mac,uint8_t *raw,uint16_t raw_len);
	SUBGHZ_MSG (*setKey)(uint8_t *key);
	bool (*setEnhanceAck)(uint8_t *data, int size);
	void (*getEnhanceAck)(uint8_t **data, int *size);
	void (*setAckTxInterval)(uint16_t interval);
	void (*antSwitch)(uint8_t ant_sw);
	void (*setDsssSpreadFactor)(int8_t sf);
} SubGHz_CTRL;

extern const SubGHz_CTRL SubGHz;

#endif	//_SUBGHZ_API_H_
