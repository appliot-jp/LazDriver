/*
 * random function
 * 
 * File:  random.h
 * 
 * Copyright 2015 Lapis Semiconductor Co.,Ltd.
 * Author: Naotaka Saito
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef LAZURITE_IDE
#ifndef _RANDOM_H_
#define _RANDOM_H_
#endif	// LAZURITE_IDE

#include <linux/kernel.h>

extern uint16_t rand(void);
extern void srand(uint16_t data);

#endif
