/* FILE NAME: ota.c
 *
 * Copyright (c) 2017  Lapis Semiconductor Co.,Ltd.
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

#pragma SEGCODE "OTA_SEGCODE"
#pragma SEGINIT "OTA_SEGINIT"
#pragma SEGNOINIT "OTA_SEGNOINIT"
#pragma SEGCONST "OTA_SEGCONST"

#include "wdt.h"
#include "driver_irq.h"
#include "hwif/wire0.h"
#include "hwif/hal.h"

#define OTA_REQUEST					( 0xA5 )	// ota flag stored in EEPROM
#define OTA_NO_REQUEST				( 0xFF ) 

#define OTA_SIGNATURE_SIZE			( 3 )
#define OTA_SUBGHZ_BUF_SIZE			( 150 )
#define OTA_PROGRAM_DATA_SIZE		( 128 )		// program data size of 1 packet

#define OTA_CALLED_AT_BOOT			( 0x55 )
#define OTA_CALLED_BY_API			( 0xAA )

// eeprom offset
#define OTA_EEPROM_SIZE				( 13 )		// eeprom size
#define OTA_EEPROM_BASE				( 0x90 )	// base address
#define OTA_EEPROM_FLAG_OFFSET		( 0x0 )		// OTA flag
#define OTA_EEPROM_END_PRGM_OFFSET	( 0x1 )		// end address of program memory
#define OTA_EEPROM_SECT_NUM_OFFSET	( 0x3 )		// sector number during update
#define OTA_EEPROM_CH_OFFSET		( 0x4 )		// SubGHz ch

// user program memory address
#define OTA_PRGM_SECTOR_SIZE		( 0x400 )	// sector size
#define OTA_PRGM_START_SECTOR		( 1 )		// start sector of user program memory
#define OTA_PRGM_STOP_SECTOR		( 0x7000 / OTA_PRGM_SECTOR_SIZE )		// last sector of user program memory

/* --------------------------------------------------------------------------------
 * Please note that this OTA library uses SubGHz AES encrypted communication.
 * The below AES key must be changed apporpriately. For more infomation, please
 * refer to the document on Lazurite HP. ( http://www.lapis-semi.com/lazurite-jp/ )
 * -------------------------------------------------------------------------------- */
static const unsigned char key[] = {
	0xb6,0x4b,0x72,0x9a,0x3c,0x36,0x2a,0x2a,0xee,0x00,0x63,0x21,0x2f,0x9b,0xd3,0x17
};

// signature of request command and reply
static const char OTA_SIG_START_REQ[]	= "$R0";
static const char OTA_SIG_ACTIVE_OK[]	= "$A0";
static const char OTA_SIG_PASSIVE_OK[]	= "$A1";
static const char OTA_SIG_DATA_REQ[]	= "$R1";
static const char OTA_SIG_PRGM_DATA[] 	= "$A2";
#define OTA_REQ_TYPE_START		( 0 )
#define OTA_REQ_TYPE_DATA		( 1 )
#define OTA_START_REQ_SIZE		( 3 )
#define OTA_DATA_REQ_SIZE		( 6 )
#define OTA_RES_ACTIVE_OK		( 1 )
#define OTA_RES_PASSIVE_OK		( 2 )
#define OTA_RES_TIMEOUT			( 3 )
#define OTA_RES_DATA_RECEIVED	( 4 )

#define OTA_RESP_INTERVAL_1	( 0xffff )
#define OTA_RESP_INTERVAL_2	( 0xffff )
#define OTA_WAIT_INTERVAL_1	( 3000 )
#define OTA_WAIT_INTERVAL_2	( 3000 )
#define OTA_WAIT_INTERVAL_3	( 3000 )
#define OTA_WAIT_INTERVAL_4	( 3000 )
#define OTA_WAIT_INTERVAL_5	( 3000 )

//
// local typedef
//

__packed typedef struct {
	uint8_t flag;
	uint16_t end_addr;
	uint8_t upd_sector_num;
	uint8_t ch;
	uint16_t panid;
	SUBGHZ_RATE rate;
	SUBGHZ_POWER txPower;
	uint16_t hostAddr;
} OTA_PARAM;

__packed typedef struct {
	uint8_t sig[OTA_SIGNATURE_SIZE];
	uint8_t ver;
	uint16_t addr;
	uint8_t bin[OTA_PROGRAM_DATA_SIZE];
} OTA_SUBGHZ_TRX_DATA;

typedef enum {
	OTA_STATE_NEGO = 0,
	OTA_STATE_ACTIVE,
	OTA_STATE_PASSIVE,
	OTA_STATE_END,
	OTA_STATE_EXIT
} OTA_STATE;

typedef struct {
	OTA_STATE func_mode;
	uint8_t called;
	uint32_t wait_response_start;
	uint16_t wait_response_interval;
	uint32_t current_time;
} OTA_STATE_PARAM;

OTA_STATE ota_func_nego(void);
OTA_STATE ota_func_active(void);
OTA_STATE ota_func_passive(void);
OTA_STATE ota_func_end(void);

OTA_STATE (*ota_funcs[])(void) = {
	ota_func_nego,
	ota_func_active,
	ota_func_passive,
	ota_func_end
};

//
// global variable
//

uint8_t version = 0x00;
uint8_t raw[OTA_SUBGHZ_BUF_SIZE];
uint16_t upd_prgm_addr;
OTA_PARAM ota_param;
OTA_SUBGHZ_TRX_DATA trx_data;
OTA_STATE_PARAM ota_state_param;

//
// local function
//

#ifdef LAZURITE_MINI
static void ota_eeprom_wpb(uint8_t wpb)
{
	if (wpb == 0) {
		pinMode(33,OUTPUT);
		digitalWrite(33,LOW);
	} else if (wpb == 1) {
		pinMode(33,OUTPUT);
		digitalWrite(33,HIGH);
	}
}
#endif

static void ota_eeprom_write_byte(uint8_t addr, uint8_t data)
{
	if ((addr >= OTA_EEPROM_BASE) && (addr < OTA_EEPROM_BASE+OTA_EEPROM_SIZE)) {
#ifdef LAZURITE_MINI
		ota_eeprom_wpb(0);
#endif
		Wire0.beginTransmission(0x50);
#ifdef LAZURITE_MINI
		Wire0.write_byte(0);
#endif
		Wire0.write_byte(addr);
		Wire0.write_byte(data);
		Wire0.endTransmission(true);
#ifdef LAZURITE_MINI
		ota_eeprom_wpb(1);
#endif
	}
}

static void ota_eeprom_write(uint8_t offset, uint8_t *wdata, uint8_t size)
{
	int i;

	for (i=0;i<size;i++) {
		ota_eeprom_write_byte((uint8_t)(offset+i), *(wdata+i));
	}
}

#define	ota_eeprom_read(a,b,c)	HAL_I2C_read(a,b,c)

static void ota_eeprom_clear(void)
{
	uint8_t clr[13] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
	ota_eeprom_write(OTA_EEPROM_BASE, clr, sizeof(clr));
}

static void ota_flash_erase(uint8_t sector)
{
	if ((sector >= OTA_PRGM_START_SECTOR) && (sector < OTA_PRGM_STOP_SECTOR)) {
		wdt_clear();
		dis_interrupts(DI_DFLASH);

		set_bit(FSELF);
		write_reg8( FLASHACP, 0xFA );
		write_reg8( FLASHACP, 0xF5 );
		write_reg8( FLASHSEG, 0);
		write_reg8( FLASHAH, sector << 2);
		set_bit( FSERS );
		__asm("nop");
		__asm("nop");
		clear_bit(FSELF);
		
		enb_interrupts(DI_DFLASH);
	}
}

static void ota_flash_write(uint16_t addr, uint16_t word)
{
	uint8_t sector = (uint8_t)(upd_prgm_addr/OTA_PRGM_SECTOR_SIZE);

	if ((sector >= OTA_PRGM_START_SECTOR) && (sector < OTA_PRGM_STOP_SECTOR)) {
		wdt_clear();
		dis_interrupts(DI_DFLASH);
		
		set_bit(FSELF);
		write_reg8( FLASHACP, 0xFA );
		write_reg8( FLASHACP, 0xF5 );
		write_reg8( FLASHSEG, 0 );
		write_reg16( FLASHA, addr );
		write_reg16( FLASHD, word );
		__asm("nop");
		__asm("nop");
		clear_bit(FSELF);
		
		enb_interrupts(DI_DFLASH);
	}
}

static uint16_t ota_flash_read(uint16_t addr)
{
	uint16_t __far *far_addr;
	uint32_t laddr;

	laddr = 0x0l+addr;
	far_addr = (uint16_t __far *)laddr;

	return *far_addr;
}

static void ota_prgm_write(void)
{
	int i;

	for (i=0;i<OTA_PROGRAM_DATA_SIZE;i++,i++) {
		ota_flash_write(upd_prgm_addr+i,*((uint16_t*)((uint8_t*)(trx_data.bin+i))));
	}
}

static bool ota_prgm_read_verify(void)
{
	int i;

	for (i=0;i<OTA_PROGRAM_DATA_SIZE;i++,i++) {
		if (*((uint16_t*)&trx_data.bin[i]) != ota_flash_read(upd_prgm_addr+i)) break;
	}

	return i == OTA_PROGRAM_DATA_SIZE ? true : false;
}

static SUBGHZ_MSG ota_send_request(uint8_t type)
{
	SUBGHZ_MSG msg;
	uint8_t *sig, size;

	if (type == OTA_REQ_TYPE_START) {
		sig = OTA_SIG_START_REQ;
		size = OTA_START_REQ_SIZE;
	} else {
		sig = OTA_SIG_DATA_REQ;
		size = OTA_DATA_REQ_SIZE;
		trx_data.ver = version;
		trx_data.addr = upd_prgm_addr;
	}
	memcpy(trx_data.sig, sig, OTA_SIGNATURE_SIZE);
	SubGHz.begin(ota_param.ch, ota_param.panid, ota_param.rate, ota_param.txPower);
	msg = SubGHz.send(ota_param.panid, ota_param.hostAddr, (uint8_t*)&trx_data, size, NULL);
	SubGHz.close();
	return msg;
}

static void ota_wait_interval(uint16_t interval, bool rdm)
{
	uint16_t tmp = interval;

	if (rdm) {
//		tmp = interval + (signed short)((float)((rand()-32768)/32768)*(interval>>3));
	}
	sleep(tmp);
}

static uint8_t ota_wait_response(void)
{
	short rx_len;
	SUBGHZ_MAC_PARAM mac;
	uint8_t result;

int i;
	SubGHz.begin(ota_param.ch, ota_param.panid, ota_param.rate, ota_param.txPower);
	SubGHz.rxEnable(NULL);
	for (;;) {
		wdt_clear();
/* 		if ((ota_state_param.wait_response_start != 0) && \
			(ota_state_param.current_time - ota_state_param.wait_response_start > ota_state_param.wait_response_interval)) {
			ota_state_param.wait_response_start = 0;
			result = OTA_RES_TIMEOUT;
			break;
		}
 */		rx_len = SubGHz.readData(raw,OTA_SUBGHZ_BUF_SIZE);
		if (rx_len) {
			SubGHz.decMac(&mac,raw,rx_len);
			memcpy((uint8_t *)&trx_data, mac.payload, mac.payload_len+1);
			// '$A0'
			if ((strncmp(trx_data.sig, OTA_SIG_ACTIVE_OK, OTA_SIGNATURE_SIZE)==0) && \
				(ota_state_param.func_mode == OTA_STATE_NEGO)) {
				version = trx_data.ver;
				ota_param.end_addr = trx_data.addr;
				result = OTA_RES_ACTIVE_OK;
				break;
			// '$A1'
			} else if ((strncmp(trx_data.sig, OTA_SIG_PASSIVE_OK, OTA_SIGNATURE_SIZE)==0) && \
				(ota_state_param.func_mode == OTA_STATE_NEGO)) {
				version = trx_data.ver;
				result = OTA_RES_PASSIVE_OK;
				break;
			// '$A2'
			} else if (strncmp(trx_data.sig, OTA_SIG_PRGM_DATA, OTA_SIGNATURE_SIZE)==0) {
				if (((ota_state_param.func_mode == OTA_STATE_ACTIVE)|| \
					(ota_state_param.func_mode == OTA_STATE_PASSIVE)) && \
					(version == trx_data.ver)) {
					result = OTA_RES_DATA_RECEIVED;
					break;
				}
			} else {
				// do nothing
			}
		}
	}
	SubGHz.close();
	return result;
}

void ota_watch_dog_isr(void)
{
	// dummy func
}

static void ota_setup(void)
{
	// SubGHz
	SubGHz.close();					// just in case
	SubGHz.setKey(key);
	SubGHz.setAckReq(true);
	// Watch dog timer
//	irq_sethandler(IRQ_NO_WDTINT,ota_watch_dog_isr);	// override
//	wdt_init( WDTMOD_WDT1 );							// 2s
}

static OTA_STATE ota_func_nego(void)
{
	SUBGHZ_MSG msg;
	uint8_t result;
	OTA_STATE mode = OTA_STATE_NEGO;

	msg = ota_send_request(OTA_REQ_TYPE_START);
	if (msg == SUBGHZ_OK) {
		ota_state_param.wait_response_interval = OTA_RESP_INTERVAL_1;
		result = ota_wait_response();
		switch (result) {
		case OTA_RES_ACTIVE_OK:
			mode = OTA_STATE_ACTIVE;
			ota_wait_interval(OTA_WAIT_INTERVAL_3,false);
			break;
		case OTA_RES_PASSIVE_OK:
			mode = OTA_STATE_PASSIVE;
			break;
		case OTA_RES_TIMEOUT:
			ota_wait_interval(OTA_WAIT_INTERVAL_2,false);
			break;
		default:
			break;
		}
	} else {
		ota_wait_interval(OTA_WAIT_INTERVAL_1,true);
	}
	return mode;
}

static OTA_STATE ota_func_active(void)
{
	SUBGHZ_MSG msg;
	uint8_t result, sector;
	OTA_STATE mode = OTA_STATE_ACTIVE;

	if (upd_prgm_addr % OTA_PRGM_SECTOR_SIZE == 0) {	// head of sector
		sector = (uint8_t)(upd_prgm_addr/OTA_PRGM_SECTOR_SIZE);
//		ota_eeprom_write_byte(OTA_EEPROM_SECT_NUM_OFFSET,sector);
		ota_flash_erase(sector);
	}

	msg = ota_send_request(OTA_REQ_TYPE_DATA);
	if (msg == SUBGHZ_OK) {
		ota_state_param.wait_response_interval = OTA_RESP_INTERVAL_2;
		result = ota_wait_response();
		switch (result) {
		case OTA_RES_DATA_RECEIVED:
			ota_prgm_write();
			if (ota_prgm_read_verify()) {
				if (upd_prgm_addr < ota_param.end_addr) {
					upd_prgm_addr += OTA_PROGRAM_DATA_SIZE;
				} else {
					mode = OTA_STATE_END;
				}
			}
			break;
		case OTA_RES_TIMEOUT:
			ota_wait_interval(OTA_WAIT_INTERVAL_5,false);
			break;
		default:
			break;
		}
	} else {
		ota_wait_interval(OTA_WAIT_INTERVAL_4,true);
	}
	return mode;
}

static OTA_STATE ota_func_passive(void)
{
	OTA_STATE mode = OTA_STATE_PASSIVE;

	return mode;
}

static OTA_STATE ota_func_end(void)
{
//	ota_eeprom_clear();
	irq_sethandler(IRQ_NO_WDTINT,ota_watch_dog_isr);	// override
	for (;;) __asm("nop");								// wait for WDT reset
	return OTA_STATE_EXIT;
}

static void ota_main(void)
{
	ota_state_param.func_mode = OTA_STATE_EXIT;
	if (ota_state_param.called == OTA_CALLED_BY_API) {	// called by API
		// it assumes that SubGHz.init() has already done
		ota_setup();
		upd_prgm_addr = OTA_PRGM_START_SECTOR * OTA_PRGM_SECTOR_SIZE;
		ota_state_param.func_mode = OTA_STATE_NEGO;
//		ota_eeprom_write(OTA_EEPROM_BASE+OTA_EEPROM_CH_OFFSET, (uint8_t*)&ota_param.ch, 9);
//		ota_eeprom_write_byte(OTA_EEPROM_BASE, ota_param.flag);
	} else if (ota_state_param.called == OTA_CALLED_AT_BOOT) {		// called at boot up
		Wire0.begin();
//		ota_eeprom_clear();
//		ota_eeprom_read(OTA_EEPROM_BASE, (uint8_t*)&ota_param, sizeof(ota_param));
		if ((ota_param.flag == OTA_REQUEST) && (ota_param.hostAddr != 0xFFFF)) {
			SubGHz.init();	// configure subghz
			ota_setup();
			upd_prgm_addr = ota_param.upd_sector_num * OTA_PRGM_SECTOR_SIZE;
			ota_state_param.func_mode = OTA_STATE_NEGO;
		}
	} else {											// irregular case
		// do nothing
	}

	for (;;) {
		wdt_clear();
		if (ota_state_param.func_mode == OTA_STATE_EXIT) break;
		ota_state_param.current_time = millis();		// update current time
		ota_state_param.func_mode = ota_funcs[ota_state_param.func_mode]();		// main routine
	}
}

//
// API function
//

void ota_boot(void)
{
	ota_state_param.called = OTA_CALLED_AT_BOOT;
	ota_main();
}

void ota_start(uint8_t ch, uint16_t panid, SUBGHZ_RATE rate, SUBGHZ_POWER txPower, uint16_t hostAddr)
{
	ota_param.flag = OTA_REQUEST;
	ota_param.ch = ch;
	ota_param.panid = panid;
	ota_param.rate = rate;
	ota_param.txPower = txPower;
	ota_param.hostAddr = hostAddr;

	ota_state_param.called = OTA_CALLED_BY_API;
	ota_main();
}

const st_OTA_f OTA = {
	ota_boot,
	ota_start
};
