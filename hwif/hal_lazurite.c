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

#ifdef SUBGHZ_OTA
	#pragma SEGCODE "OTA_SEGCODE"
	#pragma SEGINIT "OTA_SEGINIT"
	#pragma SEGNOINIT "OTA_SEGNOINIT"
#endif
#ifdef LAZURITE_IDE
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
	#include "mcu.h"
#endif

//*****************************************************
// Local definition
//*****************************************************
static struct I2C_CONFIG  {
	uint8_t i2c_addr;
	uint8_t addr_bits;
} i2c_config;

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

int HAL_init_waitqueue_head(wait_queue_head_t *q) {
	return 0;
}
extern unsigned short di_flag;
uint32_t HAL_wait_event_interruptible_timeout(wait_queue_head_t *q,volatile int *condition,uint32_t ms){
	volatile uint32_t st_time = millis();
	volatile uint32_t status;
	do {
		status = st_time+ms-millis();
		if(status > ms) {
			status = 0;
		}
	} while((*condition == false) && (status > 0));

	return status;
}

int HAL_wake_up_interruptible(wait_queue_head_t *q)
{
	return 0;
}


void HAL_write_lock(bool on) {
}

// api_debug add 4
int HAL_init(void) {

	//uint32_t wait_t, t;

	// SPI init
	SPI0.setDataMode(SPI_MODE0);
	SPI0.setClockDivider(SPI_CLOCK_DIV8);
	SPI0.begin();

	// GPIO init
	drv_digitalWrite(HAL_GPIO_REGPDIN,HIGH);
	drv_digitalWrite(HAL_GPIO_RESETN,HIGH);
	drv_digitalWrite(HAL_GPIO_CSB,HIGH);
	drv_pinMode(HAL_GPIO_SINTN,INPUT);
	drv_pinMode(HAL_GPIO_REGPDIN,OUTPUT);
	drv_pinMode(HAL_GPIO_RESETN,OUTPUT);
	drv_pinMode(HAL_GPIO_CSB,OUTPUT);

	drv_digitalWrite(HAL_GPIO_REGPDIN, LOW);
	drv_digitalWrite(HAL_GPIO_RESETN, LOW);

	HAL_sleep(3L);

#ifdef MK74040
	drv_pinMode(HAL_GPIO_REGPDIN,OUTPUT);
	digitalWrite(HAL_GPIO_REGPDIN,HIGH);	
	delay(1);
	digitalWrite(HAL_GPIO_REGPDIN,LOW);
	delay(1);
#endif

	//    idle();
	drv_digitalWrite(HAL_GPIO_RESETN, HIGH);

	HAL_sleep(3L);

	// I2C init
	i2c_config.i2c_addr = 0x50;
#if defined(LAZURITE_MINI) || defined(MK74040)
	i2c_config.addr_bits = 16;
#else
	i2c_config.addr_bits = 8;
#endif
	Wire0.begin();
	//HAL_GPIO_enableInterrupt();

	return 0;
}

int HAL_remove(void){
	return 0;
}

#include "macl.h"
int HAL_SPI_transfer(const unsigned char *wdata, uint16_t wsize,unsigned char *rdata, uint16_t rsize)
{
	uint16_t n;

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

	return HAL_STATUS_OK;
}

int HAL_GPIO_setInterrupt(bool (*func)(void))
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

int HAL_I2C_read(uint16_t addr, uint8_t *data, uint8_t size)
{
	unsigned char n;
	int dtmp;

	//  api_debug mod
	Wire0.beginTransmission(i2c_config.i2c_addr);
	if(i2c_config.addr_bits > 8) {
		Wire0.write_byte((uint8_t)((addr >> 8)&0xFF));
	}
	Wire0.write_byte((uint8_t)addr);
	Wire0.endTransmission(false);

	//  api_debug mod
	Wire0.requestFrom(i2c_config.i2c_addr,size,true);

	for(n=0;n<size;n++)
	{
		dtmp = Wire0.read();
		if(dtmp < 0) return HAL_ERROR_TIMEOUT;
		*(data + n) = (uint8_t)dtmp;
	}

	return HAL_STATUS_OK;
}

/*
int HAL_TIMER_getTick(unsigned long *tick)
{
	unsigned long hal_current_time;
	hal_current_time = millis(); 

	*tick = hal_current_time - hal_previous_time;

	return HAL_STATUS_OK;
}
*/

int HAL_TIMER_setup(void)
{
	hal_previous_time = millis();
	return HAL_STATUS_OK;
}

int HAL_TIMER_start(uint16_t msec, void (*func)(void))
{

	timer_16bit_set(6,0xE8,(uint16_t)msec,func);
	timer_16bit_start(6);

	return HAL_STATUS_OK;
}

int HAL_TIMER_stop(void)
{
	timer_16bit_stop(6);

	return HAL_STATUS_OK;
}

void HAL_delayMicroseconds(uint32_t us)
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
uint32_t HAL_millis(void) {
	return millis();
}
void HAL_sleep(uint32_t ms){
	sleep(ms);
}
static unsigned long  current_time_h = 0;
static unsigned long  target_time_h = 0;
static unsigned short target_time_l = 0;
static bool (*callback)(void) = NULL;

void ms_timer4_init(void)
{
	current_time_h = 0;
	TM45D = (target_time_h ? 0xFFFF : target_time_l);
	return;
}

void ms_timer4_isr()
{
	unsigned short tm_count;
	if(current_time_h >= target_time_h)
	{
		callback();
		ms_timer4_init();
	}
	else
	{
		current_time_h++;
		TM45D = ((current_time_h != target_time_h) ?0xFFFF : target_time_l);
		QTM5 = 0;
		tm_count = TM45C;
		if(target_time_l < tm_count)
		{
			QTM4 = 1;
		}
	}
}

void ms_timer4_set(unsigned long ms, void (*f)())
{
	// calcurate count number of target time
	//	double ms_float;
	unsigned long tmp_target_time_l;
	unsigned short tm_data;

	if(ms == 0) return;

	target_time_h = ms / 64000;
	tmp_target_time_l = ((ms % 64000) <<8) / 250;
	target_time_l = (unsigned short)tmp_target_time_l;
	if(tmp_target_time_l==0)
	{
		target_time_l=0xFFFF;
		target_time_h--;
	}
	else
	{
		target_time_l--;								// decrease 1 to set register
	}

	tm_data = target_time_h ? 0xFFFF:target_time_l;

	ms_timer4_init();
	callback = f;

	// setting timer
	timer_16bit_set(4,0x68, tm_data, ms_timer4_isr);

	return;
}

void ms_timer4_start(void)
{
	timer_16bit_start(4);
}

void ms_timer4_stop(void)
{
	timer_16bit_stop(4);
}

extern char uart_tx_sending;
extern char uartf_tx_sending;

const MsTimer4 timer4 ={
	ms_timer4_set,		// void (*set)(unsigned long ms, void (*f)());
	ms_timer4_start,	// void (*start)(void);
	ms_timer4_stop,		// void (*stop)(void);
};
void HAL_noInterrupts() {
	dis_interrupts(DI_SUBGHZ);
}

void HAL_interrupts() {
	enb_interrupts(DI_SUBGHZ);
}

extern void phy_monitor(void);
extern void uart_check_irq(void);
extern struct macl_param macl;
void HAL_reset(){
	int i;
	dis_interrupts(DI_SUBGHZ);
	alert("************** PHY MONITOR ***************");
	Serial.print("macl.condition::");
	Serial.println_long(macl.condition,DEC);
	phy_monitor();

	pinMode(25,OUTPUT);
	pinMode(26,OUTPUT);
	digitalWrite(25,LOW);
	digitalWrite(26,LOW);

	alert("********* HW RESET after 5sec  ***********");
	for(i = 0; i < 10 ; i++) {
		delay(500);
		digitalWrite(25,!digitalRead(25));
		digitalWrite(26,!digitalRead(26));
	}
	// Set ELEVEL 2
	__asm("mov r0,psw\n or r0,#2\n mov psw,r0\n");
	// Software Reset
	__asm("brk");
	// endless loop
	while(1){}
}

