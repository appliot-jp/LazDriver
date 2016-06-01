/*
 * BP3596 PHY layer
 * 
 * File:  phy-bp3596.h
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


#ifndef _PHY_BP3596A_H_
#define _PHY_BP3596A_H_

typedef struct {
	int	(*init)(int (*rx_callback)(uint8_t* data, uint16_t len));
	int	(*setup)(uint8_t ch, uint8_t pwr, uint8_t bps);
	int	(*cca)(uint32_t msec);
	int	(*fifo_write)(uint8_t* data, uint32_t size);
	int	(*fifo_read)(uint8_t* data, uint32_t size);
	int	(*csma)(uint32_t msec);
	int	(*remove)(void);
}PHY;


extern const PHY phy;

#endif // _PHY_BP3596A_H_


