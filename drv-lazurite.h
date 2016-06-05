/*
 * IEEE802.15.4e driver IO
 * 
 * File:  drv-802154e.c
 * 
 * Copyright 2015 Lapis Semiconductor Co.,Ltd.
 * Author: Naotaka Saito
 * 
 * The program is based on BP3596 driver by Communication Technology
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#ifndef _DRV_802154E_H_
#define _DRV_802154E_H_

#define	DRV_OK				0


// ioctl command list
#define	IOCTL_PARAM		(0x1000 >> 12)
#define	IOCTL_GET_CH	2
#define	IOCTL_SET_CH	3
#define	IOCTL_GET_PWR	4
#define	IOCTL_SET_PWR	5
#define	IOCTL_GET_BPS	6
#define	IOCTL_SET_BPS	7
#define	IOCTL_GET_PANID	8
#define	IOCTL_SET_PANID	9
#define	IOCTL_RF		(0x2000 >> 12)
#define	IOCTL_EEPROM	(0x3000 >> 12)
#define	IOCTL_LED		(0x4000 >> 12)

#endif // _DRV_802154E_H_

