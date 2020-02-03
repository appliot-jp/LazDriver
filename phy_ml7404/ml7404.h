/****************************************************************************************/
/**
   @file     ml7404.h

   @brief    RF LSI register information header file
   @version  V1.00
   @date     26. Feb. 2018

   @copyright    Copyright (C) 2018 LAPIS Semiconductor Co., Ltd. All rights reserved.

   @par  
        This software is provided "as is" and any expressed or implied
         warranties, including, but not limited to, the implied warranties of
         merchantability and fitness for a particular purpose are disclaimed.
         LAPIS Semiconductor shall not be liable for any direct, indirect, consequential or 
         incidental damages arising from using or modifying this software.
         You (customer) can modify and use this software in whole or part on
         your own responsibility, only for the purpose of developing the software
         for use with microcontroller manufactured by LAPIS Semiconductor.
    
*******************************************************************************************/
#ifndef _ML7404_H
#define _ML7404_H

#include "bank0.h"
#include "bank1.h"
#include "bank2.h"
#include "bank3.h"
#include "bank4.h"
#include "bank6.h"
#include "bank6.h"
#include "bank7.h"
#include "bank10.h"

typedef struct {
	uint8_t addr;
	uint8_t val;
} RADIO_PHY_SET_T;

#endif
