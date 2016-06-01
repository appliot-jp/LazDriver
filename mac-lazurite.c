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

int mac_init(void)
{
	return 0;
}

int mac_remove(void)
{
	return 0;
}

int mac_setup(uint8_t ch, uint8_t panid, uint8_t bps, uint8_t pwr)
{
	return 0;
}

int mac_close(void)
{
	return 0;
}

MAC_LAZURITE mac = {
	mac_init,
	mac_remove,
	mac_setup,
	mac_close,
};
