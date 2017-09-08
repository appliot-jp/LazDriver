/* FILE NAME: hal_lazurite.c
 *
 * Copyright (c) 2015  Lapis Semiconductor Co.,Ltd.
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */



#include <common.h>
#include <lazurite_system.h>
#include <driver_timer.h>
#include <driver_extirq.h>
#include <driver_irq.h>
#include <driver_gpio.h>
#include <driver_uart.h>
#include <lp_manage.h>
#include <wdt.h>
#include "hal.h"
#include "hal_lazurite.h"
#include "spi0.h"
#include "wire0.h"

//*****************************************************
// Local definition
//*****************************************************

void (*hal_gpio_func)(void);
static unsigned long hal_previous_time;
// 2015.12.14 Eiichi Saito: for preference of SubGHz
//static unsigned char hal_setbit_exi;
volatile unsigned char hal_event_flag = 0;

//*****************************************************
// temporary
//*****************************************************

//*****************************************************
// Function
//*****************************************************

static void HAL_abort_timer_func(void)
{
	hal_event_flag = 1;
	HAL_TIMER_stop();
}

int HAL_wait_event(uint8_t event)
{
	int status = 0;
    if (event == HAL_PHY_EVENT) {
		HAL_TIMER_stop();
		HAL_TIMER_start(1000, HAL_abort_timer_func);
    } else if (event == HAL_MAC_EVENT) {
		hal_event_flag = 0;
		wait_event(&hal_event_flag);
    }
	return status;
}

int HAL_wakeup_event(uint8_t event)
{
    int status = 0;
    HAL_TIMER_stop();
    if (event == HAL_PHY_EVENT) {
		// do nothing
    } else if (event == HAL_MAC_EVENT) {
		hal_event_flag = 1;
    }
    return status;
}


// api_debug add 4
int HAL_init(void){

    uint32_t wait_t, t;

    // SPI init
	SPI0.setDataMode(SPI_MODE0);
	SPI0.setClockDivider(SPI_CLOCK_DIV8);
	SPI0.begin();

    // GPIO init
	drv_digitalWrite(HAL_GPIO_RESETN,HIGH);
	drv_digitalWrite(HAL_GPIO_CSB,HIGH);
	drv_pinMode(HAL_GPIO_SINTN,INPUT);
	drv_pinMode(HAL_GPIO_RESETN,OUTPUT);
	drv_pinMode(HAL_GPIO_CSB,OUTPUT);

    drv_digitalWrite(HAL_GPIO_RESETN, 0);
	HAL_sleep(3);
    //    idle();
    drv_digitalWrite(HAL_GPIO_RESETN, 1);
	HAL_sleep(3);

    // I2C init
	Wire0.begin();
	return 0;
}

int HAL_remove(void){
}

int HAL_SPI_transfer(const unsigned char *wdata, uint16_t wsize,unsigned char *rdata, uint16_t rsize)
{
	unsigned char n;
	
	dis_interrupts(DI_SUBGHZ);	
	
	drv_digitalWrite(HAL_GPIO_CSB, HIGH);
	drv_digitalWrite(HAL_GPIO_CSB, LOW);

    //  api_debug mod
	for(n=0;n<wsize;n++)
	{
		SPI0.transfer(*(wdata + n));
	}
	if(rdata==NULL) return HAL_STATUS_OK;
    for(n=0;n<rsize;n++)
	{
        *(rdata + n) = SPI0.transfer(0);
    }

	drv_digitalWrite(HAL_GPIO_CSB, HIGH);
	
	enb_interrupts(DI_SUBGHZ);	
	
	return HAL_STATUS_OK;
}

int HAL_GPIO_setInterrupt(void (*func)(void))
{
	hal_gpio_func = func;
	drv_attachInterrupt(HAL_GPIO_SINTN,BP3596A_SINTN_IRQNUM,hal_gpio_func,LOW,false,false);
	return HAL_STATUS_OK;
}

int HAL_GPIO_enableInterrupt(void)
{
	//	void drv_attachInterrupt(unsigned char pin,unsigned char irqnum, void (*func)(void), int mode,bool sampling, bool filter)
	drv_attachInterrupt(HAL_GPIO_SINTN,BP3596A_SINTN_IRQNUM,hal_gpio_func,LOW,false,false);
	return HAL_STATUS_OK;
}

int HAL_GPIO_disableInterrupt(void)
{
	drv_detachInterrupt(BP3596A_SINTN_IRQNUM);
	return HAL_STATUS_OK;
}

int HAL_I2C_read(unsigned short addr, unsigned char *data, unsigned char size)
{
	unsigned char n;
	int dtmp;

    //  api_debug mod
	Wire0.beginTransmission(0x50);
#ifdef LAZURITE_MINI
	Wire0.write_byte(0);
#endif
	Wire0.write_byte(addr);
	Wire0.endTransmission(false);
    //  api_debug mod
	Wire0.requestFrom(0x50,size,true);
	
	for(n=0;n<size;n++)
	{
		dtmp = Wire0.read();
		if(dtmp < 0) return HAL_STATUS_ERROR_TIMEOUT;
		*(data + n) = (uint8_t)dtmp;
	}
	
	return HAL_STATUS_OK;
}

int HAL_TIMER_getTick(unsigned long *tick)
{
	unsigned long hal_current_time;
	hal_current_time = millis(); 
	
	*tick = hal_current_time - hal_previous_time;
	
	return HAL_STATUS_OK;
}

int HAL_TIMER_setup(void)
{
	hal_previous_time = millis();
	return HAL_STATUS_OK;
}

int HAL_TIMER_start(unsigned short msec, void (*func)(void))
{
	timer_16bit_set(6,0xE8,(unsigned long)msec,func);
	timer_16bit_start(6);
	return HAL_STATUS_OK;
}

int HAL_TIMER_stop(void)
{
	timer_16bit_stop(6);
	return HAL_STATUS_OK;
}


void HAL_set_timer0_function(void (*func)(uint32_t sys_timer_count)) {
	set_timer0_function(func);
}

// 7.4us is minimum delay
volatile void HAL_delayMicroseconds(unsigned long us)
{
	dis_interrupts(DI_SUBGHZ);	

 	if (us > 7) {
		us = us / 2 - 4;
		while (us > 0) {
			// w/a for avoiding UART communication data lost
			uart_check_irq();
             __asm("nop\n");
             __asm("nop\n");
 			us--;
		}
	}
	enb_interrupts(DI_SUBGHZ);	

	return;
}
