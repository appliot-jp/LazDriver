/* FILE NAME: ota.c
 *
 * Copyright (c) 2019  Lapis Semiconductor Co.,Ltd.
 * All rights reserved.
 *
 */

#include "wdt.h"
#include "driver_irq.h"
#include "hwif/wire0.h"
#include "hwif/hal.h"
#include "ota.h"
//#define OTA_DEBUG
#ifdef OTA_DEBUG
#include "serial.h"
#endif

#define OTA_LED_INFO	// uncomment if using LED status 
#define ORANGE_LED					( 25 )
#define BLUE_LED					( 26 )

// #########################   DON'T EDIT BELOW CODE   ######################### 

#asm
	CSEG at 0h
	DS	400h		; reserved area for sytem code
	CSEG at 0Ah		; OTA_KEYWORD_OFFSET
	DB	"$OTA"		; built-in keyword
#endasm

// hw type and keyword
#pragma ROMWIN 0 0xd7ff
#pragma SEGCONST 0xE		// OTA_HW_TYPE_OFFSET
#define OTA_HW_TYPE_MINI			( 1 )

static const uint8_t hw_type = OTA_HW_TYPE_MINI;

#pragma SEGCODE "OTA_SEGCODE"
#pragma SEGNOINIT "OTA_SEGNOINIT"
#pragma SEGCONST "OTA_SEGCONST"

//
// API function
//

void ota_boot(void)
{
	return;
}

void ota_start(OTA_PARAM *param)
{
	return;
}

uint8_t ota_get_hw_type(void)
{
	return hw_type;
}

uint8_t ota_get_version(void)
{
	return 0;
}

const st_OTA_f OTA = {
	ota_boot,
	ota_start,
	ota_get_hw_type,
	ota_get_version
};
