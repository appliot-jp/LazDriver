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

#include <arduino.h>
#include <spi.h>
#include <wire.h>
#include <mstimer2.h>
#include "hal.h"
#include "hal_arduino.h"


//*****************************************************
// Local definition
//*****************************************************
static SPISettings mySPISettings = SPISettings(8000000, MSBFIRST, SPI_MODE0);
static struct I2C_CONFIG  {
	uint8_t i2c_addr;
	uint8_t addr_bits;
} i2c_config;

void wait_event(volatile uint8_t *flag)
{	
	while(*flag == false) { }
	*flag = false;
}

void (*hal_gpio_func)(void);
static uint32_t hal_previous_time;
// 2015.12.14 Eiichi Saito: for preference of SubGHz
//static unsigned char hal_setbit_exi;
volatile uint8_t hal_event_flag = 0;

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
int HAL_init(uint8_t i2c_addr,uint8_t addr_bits){

	//uint32_t wait_t, t;

	// SPI init
	//SPI.setDataMode(SPI_MODE0);
	//SPI.setClockDivider(SPI_CLOCK_DIV8);
	SPI.begin();

	// GPIO init
	digitalWrite(HAL_GPIO_RESETN,HIGH);
	digitalWrite(HAL_GPIO_CSB,HIGH);
	pinMode(HAL_GPIO_SINTN,INPUT);
	pinMode(HAL_GPIO_RESETN,OUTPUT);
	pinMode(HAL_GPIO_CSB,OUTPUT);

	digitalWrite(HAL_GPIO_RESETN, 0);
	HAL_sleep(3);
	//    idle();
	digitalWrite(HAL_GPIO_RESETN, 1);
	HAL_sleep(3);

	// I2C init
	i2c_config.i2c_addr = i2c_addr;
	i2c_config.addr_bits = addr_bits;
	Wire.begin();
	return 0;
}

int HAL_remove(void){
	return 0;
}

int HAL_SPI_transfer(const unsigned char *wdata, uint16_t wsize,unsigned char *rdata, uint16_t rsize)
{
	unsigned char n;

	SPI.beginTransaction(mySPISettings);
	digitalWrite(HAL_GPIO_CSB, HIGH);
	digitalWrite(HAL_GPIO_CSB, LOW);

	//  api_debug mod
	for(n=0;n<wsize;n++)
	{
		SPI.transfer(*(wdata + n));
	}
	if(rdata==NULL) return HAL_STATUS_OK;
	for(n=0;n<rsize;n++)
	{
		*(rdata + n) = SPI.transfer(0);
	}

	digitalWrite(HAL_GPIO_CSB, HIGH);

	return HAL_STATUS_OK;
}

int HAL_GPIO_setInterrupt(void (*func)(void))
{
	hal_gpio_func = func;
	//attachInterrupt(HAL_GPIO_SINTN,BP3596A_SINTN_IRQNUM,hal_gpio_func,LOW,false,false);
	attachInterrupt(BP3596A_SINTN_IRQNUM,hal_gpio_func,LOW);
	return HAL_STATUS_OK;
}

int HAL_GPIO_enableInterrupt(void)
{
	//	void drv_attachInterrupt(unsigned char pin,unsigned char irqnum, void (*func)(void), int mode,bool sampling, bool filter)
	attachInterrupt(BP3596A_SINTN_IRQNUM,hal_gpio_func,LOW);
	//attachInterrupt(HAL_GPIO_SINTN,BP3596A_SINTN_IRQNUM,hal_gpio_func,LOW,false,false);
	return HAL_STATUS_OK;
}

int HAL_GPIO_disableInterrupt(void)
{
	detachInterrupt(BP3596A_SINTN_IRQNUM);
	return HAL_STATUS_OK;
}

int HAL_I2C_read(unsigned short addr, unsigned char *data, unsigned char size)
{
	unsigned char n;
	int dtmp;

	//  api_debug mod
	Wire.beginTransmission(i2c_config.i2c_addr);
	if(i2c_config.i2c_addr> 8) {
		Wire.write(0);
	}
	Wire.write(addr);
	Wire.endTransmission(false);
	//  api_debug mod
	Wire.requestFrom((uint8_t)i2c_config.i2c_addr,(uint8_t)size,(uint8_t)true);

	for(n=0;n<size;n++)
	{
		dtmp = Wire.read();
		if(dtmp < 0) return HAL_ERROR_TIMEOUT;
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
	/*
		 timer_16bit_set(6,0xE8,(unsigned long)msec,func);
		 timer_16bit_start(6);
		 */
	MsTimer2::set(msec,func);
	MsTimer2::start();
	return HAL_STATUS_OK;
}

int HAL_TIMER_stop(void)
{
	MsTimer2::stop();
	//timer_16bit_stop(6);
	return HAL_STATUS_OK;
}


/*
	 volatile void HAL_delayMicroseconds(unsigned long us)
	 {
	 if (us > 2) {
	 us /= 2;
	 while (us > 0) {
// w/a for avoiding UART communication data lost
uart_check_irq();
__asm("nop\n");
__asm("nop\n");
us--;
}
}
return;
}
*/

