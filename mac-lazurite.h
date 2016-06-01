/*
 * IEEE802.15.4e driver IO
 * 
 * File:  drv-802154e.c
 * 
 * Copyright 2015 Lapis Semiconductor Co.,Ltd.
 * Author: Naotaka Saito
 * 
 * The program is developed refered to BP3596 driver by Communication Technology
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/



#ifndef _MAC_802154E_H_
#define _MAC_802154E_H_

#ifdef	LAZURITE_IDE
#else	//LAZURITE_IDE
#include <linux/types.h>
#include <linux/string.h>
#endif	//LAZURITE_IDE

typedef struct {
	int (*init)(void);
	int (*remove)(void);
	int (*setup)(uint8_t ch, uint8_t panid, uint8_t bps, uint8_t pwr);
	int (*send)(uint16_t dstPanid,uint16_t dstAddr,uint8_t addrMode,uint8_t *payload,uint16_t len, void (*callback)(uint8_t rssi,int status));
	int (*rxEnable)(void (*callback)(uint8_t *data,uint8_t rssi, int status));
	int (*close)(void);
} MAC_LAZURITE;

extern MAC_LAZURITE mac;

#endif // _MAC_802154E_H_


