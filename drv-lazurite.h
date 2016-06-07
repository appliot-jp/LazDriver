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

#define	DRV_OK					0


// ioctl command list
#define	IOCTL_PARAM				(0x1000 >> 12)
#define	IOCTL_GET_CH			2
#define	IOCTL_SET_CH			3
#define	IOCTL_GET_PWR			4
#define	IOCTL_SET_PWR			5
#define	IOCTL_GET_BPS			6
#define	IOCTL_SET_BPS			7
#define	IOCTL_GET_MY_ADDR0		8
#define	IOCTL_GET_MY_ADDR1		10
#define	IOCTL_GET_MY_ADDR2		12
#define	IOCTL_GET_MY_ADDR3		14
#define	IOCTL_GET_MY_PANID		16
#define	IOCTL_SET_MY_PANID		17
#define	IOCTL_GET_TX_PANID		18
#define	IOCTL_SET_TX_PANID		19
#define	IOCTL_GET_TX_ADDR0		20
#define	IOCTL_SET_TX_ADDR0		21
#define	IOCTL_GET_TX_ADDR1		22
#define	IOCTL_SET_TX_ADDR1		23
#define	IOCTL_GET_TX_ADDR2		24
#define	IOCTL_SET_TX_ADDR2		25
#define	IOCTL_GET_TX_ADDR3		26
#define	IOCTL_SET_TX_ADDR3		27
#define	IOCTL_GET_ADDR_TYPE		28
#define	IOCTL_SET_ADDR_TYPE		29
#define	IOCTL_GET_ADDR_SIZE		30
#define	IOCTL_SET_ADDR_SIZE		31
#define	IOCTL_GET_DRV_MODE		32
#define	IOCTL_SET_DRV_MODE		33
#define	IOCTL_RF				(0x2000 >> 12)
#define	IOCTL_EEPROM			(0x3000 >> 12)
#define	IOCTL_LED				(0x4000 >> 12)

#endif // _DRV_802154E_H_

