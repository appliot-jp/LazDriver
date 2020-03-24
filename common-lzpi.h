/*
 * LazDriver common for Linux
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

#ifndef _COMMON_802154E_H_
#define _COMMON_802154E_H_


#define	MODE_NORMAL			0x0000
#define MODE_DRV_DEBUG		0x8000
#define MODE_MACH_DEBUG		0x4000
#define MODE_MACL_DEBUG		0x2000
#define MODE_PHY_DEBUG		0x1000
#define MODE_PA_TEST		0x0800

// for linux driver test mode
//#ifndef LAZURITE_IDE
extern int module_test;
//#endif
#ifndef alert
#define alert(a) printk(KERN_INFO"%s  %s\n",__func__,a)
#endif

#ifndef PAYLOADDUMP
#define PAYLOADDUMP( data, size ) {\
	int d;\
	int p;\
	uint8_t tmp;\
	char str[64] ;	\
	if (size > 0){\
		printk(KERN_INFO" [PAYLOAD] 00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\r\n");\
		printk(KERN_INFO"-----------------------------------------------------------\r\n");\
		memset(str,0,sizeof(str));\
		for (d = 0,p=0; d < size; d++){\
			tmp = data[d]  >> 4;\
			if(tmp >= 10) {\
				tmp -= 10;\
				str[p] = 'A'+tmp;p++;\
			} else {\
				str[p] = '0'+tmp;p++;\
			}\
			tmp = data[d] & 0x0F;\
			if(tmp >= 10) {\
				tmp -= 10;\
				str[p] = 'A'+tmp;p++;\
			} else {\
				str[p] = '0'+tmp;p++;\
			}\
			str[p] = ' ';p++;\
			if((d+1)%16 == 0) {\
				printk(KERN_INFO"%08X %s", d/16, str);\
				memset(str,0,sizeof(str));\
				p = 0; \
			} else if( (d+1) % 8 == 0 ) {\
				str[p] = ' ';p++;\
			}\
		}\
		printk(KERN_INFO"%08X %s\n", d/16, str);\
	}\
}
#endif
extern int task[4];
extern int access_num;
#ifndef ACCESS_PUSH
#define ACCESS_PUSH(a) {\
	task[access_num] = a;	\
}
#endif
#ifndef ACCESS_POP
#define ACCESS_POP() {\
	task[access_num] = 0;	\
}
#endif

#define LOW 0
#define HIGH 1

#endif // _COMMON_802154E_H_
