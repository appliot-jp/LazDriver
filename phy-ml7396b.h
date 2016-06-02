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



#ifndef	_PHY_ML7396B_H_
#define	_PHY_ML7396B_H_

#ifdef	LAZURITE_IDE
#else	//LAZURITE_IDE
#include <linux/types.h>
#include <linux/string.h>
#endif	//LAZURITE_IDE

typedef struct {
	int (*init)(void);
	int (*remove)(void);
} PHY_LAZURITE;

extern const PHY_LAZURITE phy;

#endif	// _PHY_ML7396B_H_


