/* FILE NAME: ota.h
 *
 * Copyright (c) 2019  Lapis Semiconductor Co.,Ltd.
 * All rights reserved.
 *
 */

#ifndef _OTA_H_
#define _OTA_H_

#define OTA_AES_KEY_SIZE		( 16 )
#define OTA_PRGM_NAME_SIZE		( 16 )		// max 15 bytes + null termination '\0'

__packed typedef struct {
	uint8_t hw_type;
	uint8_t ver;
	uint8_t name[OTA_PRGM_NAME_SIZE];
	uint8_t ch;
	uint16_t panid;
	SUBGHZ_RATE rate;
	SUBGHZ_POWER txPower;
	uint16_t hostAddr;
} OTA_PARAM;

typedef struct {
    void	(*boot)(void);		// Do not call this function. It shall be called only from main.c
	void	(*start)(OTA_PARAM *param);
    uint8_t	(*getHwType)(void);
    uint8_t	(*getVersion)(void);
} st_OTA_f;

extern const st_OTA_f OTA;
extern const uint8_t ota_aes_key[];

#endif // _OTA_H_
