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



#ifdef	LAZURITE_IDE
#include "lazurite.h"
#include "spi_lazurite.h"
#include "wire0.h"
#include "common_lazurite.h"
#else	// LAZURITE_IDE
#include	"spi-lzpi.h"
#include	"i2c-lzpi.h"
#include	"hal-lzpi.h"
#endif
#include "hal.h"


//*****************************************************
// Local definition
//*****************************************************
void (*hal_irq_func)(void);				// gpio call back
#define	LED_FLASH_TIME	1					// LED Flashing time
static struct timespec start_time;			// memory of tick timer
static struct timer_list g_timer;			// timer handler
static void (*ext_timer_func)(void);
//*****************************************************
// temporary
//*****************************************************

//*****************************************************
// Function
//*****************************************************
void rf_irq_thread(void *p)
{
}

int lazurite_setup(void) 
{
	int status = 0;

	finish_flag = 0;

	DEBUGONDISPLAY(MODE_PHY_DEBUG, PRINT_LOG());

	
	// init external functions
	ext_timer_func = NULL;
	hal_irq_func = NULL;
	
	// IRQ Initializing
	init_waitqueue_head( &irq_q );
	DEBUGONDISPLAY(MODE_PHY_DEBUG, PRINT_LOG());
	// led queue initializing
#ifdef GPIO_RX_LED
	init_waitqueue_head( &rx_led_q );
#endif
#ifdef GPIO_TX_LED
	init_waitqueue_head( &tx_led_q );
#endif


	// create GPIO irq
	enable_irq(gpio_to_irq(GPIO_SINTN));
	DEBUGONDISPLAY(DEBUG_HAL, PRINT_LOG());

	status = request_irq(gpio_to_irq(GPIO_SINTN),
			bp3596_irq_handler,
			IRQF_TRIGGER_FALLING,
			"bp3596gpio", NULL);
	if(status)
	{
		DEBUGONDISPLAY(DEBUG_HAL, PRINT_LOG());
		goto error_irq_request;
	}
	printk("[PHY-BP3596] finish setup irq_q\n");
	
	hal_gpio_func = NULL;
	
	// start thread
	kthread_tsk = kthread_run(rf_irq_thread, NULL,0);
	if (IS_ERR(kthread_tsk)) {
		printk(KERN_INFO "bp3596_init: kthread_run failed\n");
		goto error_thread;
	}

#ifdef GPIO_RX_LED
	rx_led_tsk = kthread_run(bp_rx_led_thread, NULL,LED_FLASH_TIME);
	if (IS_ERR(rx_led_tsk)) {
		printk(KERN_INFO "bp3596_init: rx_led_kthread_run failed\n");
		goto error_thread;
	}
#endif
#ifdef GPIO_TX_LED
	tx_led_tsk = kthread_run(bp_tx_led_thread, NULL, LED_FLASH_TIME);
	if (IS_ERR(tx_led_tsk)) {
		printk(KERN_INFO "bp3596_init: tx_led_kthread_run failed\n");
		goto error_thread;
	}
#endif

	return 0;
error_thread:
	free_irq(gpio_to_irq(GPIO_SINTN), NULL);
error_irq_request:
	disable_irq(gpio_to_irq(GPIO_SINTN));

	return status;
}


int HAL_SPI_setup(void)
{
	bp_spi_add_driver(lazurite_setup());
	
	return HAL_STATUS_OK;
}

//int HAL_SPI_transfer(unsigned char *wdata, unsigned char *rdata, unsigned char size)
int HAL_SPI_transfer(const unsigned char *wdata, unsigned char wsize,unsigned char *rdata, unsigned char rsize)
{
	bp_spi_transfer(wdata,wsize,rdata,rsize);
	return 0;
}

int HAL_GPIO_setInterrupt(void (*func)(void))
{
	hal_irq_func = func;
	return HAL_STATUS_OK;
}

int HAL_GPIO_enableInterrupt(void)
{
	return HAL_STATUS_OK;
}

int HAL_GPIO_disableInterrupt(void)
{
	return HAL_STATUS_OK;
}

int HAL_I2C_setup(void)
{
	Wire0.begin();
	return HAL_STATUS_OK;
}

int HAL_I2C_read(unsigned char devAddr, unsigned short addr, unsigned char *data, unsigned char size)
{
	unsigned char n;
	int dtmp;

	Wire0.beginTransmission(devAddr);
#ifdef LAZURIE_MINI
	Wire0.write_byte((addr>>8)&0x00FF);
#endif
	Wire0.write_byte(addr&0x00FF);
	Wire0.endTransmission(false);
	Wire0.requestFrom(devAddr,size,true);
	
	for(n=0;n<size;n++)
	{
		dtmp = Wire0.read();
		if(dtmp < 0) return HAL_STATUS_ERROR_TIMEOUT;
		*(data + n) = (uint8_t)dtmp;
	}
	
	return HAL_STATUS_OK;
}

int HAL_remove(void)
{
	// thread�̒�~
	// I2C remove
	bp_i2c_remove();
	// SPI�̒�~
	
}

// timer function
int HAL_TIMER_getTick(unsigned long *tick)
{
	struct timespec current_time;
	struct timespec diff_time;
	unsigned long diff_ms;
	
	getnstimeofday(&current_time);
	
	diff_time.tv_sec = current_time.tv_sec - start_time.tv_sec;
	diff_time.tv_nsec = current_time.tv_nsec - start_time.tv_nsec;
	
	*tick = diff_time.tv_sec * 1000 + diff_time.tv_nsec/1000000;
	
	return HAL_STATUS_OK;
}

int HAL_TIMER_setup(void)
{
	getnstimeofday(&start_time);
	return HAL_STATUS_OK;
}


void timer_function(unsigned long data)
{
	if(ext_timer_func) ext_timer_func();
}

int HAL_TIMER_start(unsigned short msec, void (*func)(void))
{
	init_timer(&g_timer);
	g_timer.data = 0;
	g_timer.expires = jiffies + (HZ*ms)/1000;
	g_timer.function = timer_function;
	add_timer(&g_timer);
	return HAL_STATUS_OK;
}

int HAL_TIMER_stop(void)
{
	del_timer(&g_timer);
	return HAL_STATUS_OK;
}

// no need in Raspberry Pi
void HAL_EX_disableInterrupt(void)
{
}

// no need in Raspberry Pi
void HAL_EX_enableInterrupt(void)
{
}

