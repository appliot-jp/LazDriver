/*
 * IEEE802.15.4e MAC Layer
 * 
 * File:  mac-802154e.c
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

#include "mac-lazurite.h"
#include "phy-ml7396b.h"
#include "hal.h"

int phy7396b_init(void)
{
	HAL_init(0x50,8);
	return 0;
}

int phy7396b_remove(void)
{
	HAL_remove();
	return 0;
}

const PHY_LAZURITE phy = {
	phy7396b_init,
	phy7396b_remove,
};

