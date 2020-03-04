/* FILE NAME: hal-lzpi.c
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
#include	<linux/interrupt.h>
#include	<linux/sched.h>
#include	<linux/gpio.h>
#include	<linux/kthread.h>
#include	<linux/unistd.h>
#include	<linux/wait.h>
#include	"spi-lzpi.h"
#include	"i2c-lzpi.h"
#include	"hal-lzpi.h"
#endif
#include "hal.h"


//*****************************************************
// Local definition
//*****************************************************
#define	LED_FLASH_TIME	1					// LED Flashing time
static struct timer_list g_timer;			// timer handler
//static struct timer_list syslog_timer;		// timer handler
static struct timer_list timer4_timer;		// timer4 handler

static void (*ext_timer_func)(void);
static void (*ext_irq_func)(void);
//static void (*act_irq_func)(void);
//static void (*syslog_timer_ext_func)(uint32_t data);
static void (*timer4_irq_func)(void);
static bool ext_irq_enb;

extern int wait_event_macl;
volatile int que_irq= 0;
volatile int que_tx_led= 1;
volatile int que_rx_led= 1;
volatile int que_th2ex = false;
static wait_queue_head_t rf_irq_q;
static wait_queue_head_t tx_led_q;
static wait_queue_head_t rx_led_q;
wait_queue_head_t ext_q;
static struct task_struct *rf_main_task;
static struct task_struct *tx_led_task;
static struct task_struct *rx_led_task;
bool flag_irq_enable;

extern struct s_CHAR_DEV chrdev;

// main_thread_parameter
struct thread_param m = {0};

//*****************************************************
// temporary
//*****************************************************

//*****************************************************
// Function
//*****************************************************
// millis
// return milli second time from loading driver
static struct timespec load_time;
void millis_init(void)
{
	getnstimeofday(&load_time);
}

void HAL_delayMicroseconds(uint32_t us) {
	udelay((unsigned long)us);
}
uint32_t HAL_millis(void)
{
	unsigned long res;
	struct timespec current_time;
	struct timespec diff_time;
	getnstimeofday(&current_time);

	diff_time.tv_sec = current_time.tv_sec - load_time.tv_sec;
	diff_time.tv_nsec = current_time.tv_nsec - load_time.tv_nsec;

	res = diff_time.tv_sec * 1000 + ((long)diff_time.tv_nsec)/1000000;

	return res;
}

//*  MsTimer4
static uint32_t timer4_interval;
static bool timer4_enb = false;
void timer4_callback(struct timer_list *data) {
	m.trigger |= 0x10;
	mod_timer(&timer4_timer, timer4_timer.expires + timer4_interval);
	//if (que_irq==0)
	//{
		que_irq=1;
		wake_up_interruptible_sync(&rf_irq_q);
		//return IRQ_WAKE_THREAD;
	//}
}
void HAL_timer4_set(uint32_t ms, void (*func)(void)) {
	if(timer4_enb != false) {
		printk(KERN_INFO"timer4 is active\n");
		goto error;
	}
	timer4_irq_func = func;
	timer4_interval = ms*HZ/1000;
error:
	return;
}
void HAL_timer4_start(void) {
	if(timer4_enb == true) {
		printk(KERN_INFO"timer4 is active\n");
		goto error;
	}
	if(timer4_interval <= 0) {
		printk(KERN_INFO"timer4 interval =< 0\n");
		goto error;
	}
	timer4_timer.expires = jiffies + timer4_interval;
	//timer4_timer.data = 0;
	timer4_timer.function = timer4_callback;
	add_timer(&timer4_timer);
	timer4_enb = true;
error:
	return;
}

void HAL_timer4_stop(void) {
	printk(KERN_INFO"timer4.stop()\n");
	if(timer4_enb == true)  del_timer(&timer4_timer);
	timer4_enb = false;
}

const MsTimer4 timer4 = {
	HAL_timer4_set,
	HAL_timer4_start,
	HAL_timer4_stop
};

/*
static void syslog_timer_isr(struct timer_list *t) {
	if(syslog_timer_ext_func) syslog_timer_ext_func(jiffies);
	syslog_timer.expires = jiffies + HZ*2;
	add_timer(&syslog_timer);
}
*/
#include "../macl.h"
extern struct macl_param macl;
int rf_main_thread(void *p)
{
	// system logging start
	//syslog_timer_ext_func = NULL;
	//timer_setup(&syslog_timer,syslog_timer_isr,0);
	//syslog_timer.expires = jiffies + HZ*2;
	//add_timer(&syslog_timer);

	m.trigger=0;
	while(!kthread_should_stop()) {
		// printk(KERN_INFO"%s %s %d %d %d %d\n",__FILE__,__func__,__LINE__,flag_irq_enable,gpio_get_value(GPIO_SINTN),m.trigger);
		if((flag_irq_enable == true) && (gpio_get_value(PHY_SINTN) == 0)) {
			m.trigger |= 0x01;
#if !defined(LAZURITE_IDE) && defined(DEBUG)
			printk(KERN_INFO"%s %s %d %d %d macl.condition=%d\n",__FILE__,__func__,__LINE__,m.trigger, gpio_get_value(PHY_SINTN),macl.condition);
#endif
		}
		if(m.trigger == 0x00) {
			que_irq=0;
			wait_event_interruptible(rf_irq_q, que_irq);
			if(flag_irq_enable == false) {
				printk(KERN_INFO"%s %s %d %d %d macl.condition=%d\n",__FILE__,__func__,__LINE__,m.trigger, gpio_get_value(PHY_SINTN),macl.condition);
				m.trigger &= ~0x01;
				continue;
			}
		}
		if(kthread_should_stop()) break;
		if(m.trigger&0x01){ 				// SINT INTERRUPT
			if(ext_irq_func) {
				ext_irq_func();
			}
			m.trigger&=~0x03;
		}
		if(m.trigger&0x02) {				// ABORT INTERRUPT
			if(ext_timer_func) {
				ext_timer_func();
			}
			m.trigger&=~0x03;
		}
		if(m.trigger&0x04) {					// EXT SPI INTERRUPT
			m.spi.ret=lzpi_spi_transfer(m.spi.wdata,m.spi.wsize,m.spi.rdata,m.spi.rsize);
			m.trigger &= ~0x04;
			que_th2ex=true;
			wake_up_interruptible(&ext_q);
		}
		if(m.trigger&0x08) {					// EXT I2C INTERRUPT
			m.i2c.ret=HAL_I2C_read(m.i2c.addr,m.i2c.data,m.i2c.size);
			m.trigger &= ~0x08;
			que_th2ex=true;
			wake_up_interruptible(&ext_q);
		}
		if(m.trigger&0x10) {					// FREQ HOPPING INTERRUPT
			if(timer4_irq_func) {					// freq hopping timer
				timer4_irq_func();
				m.trigger&=~0x10;
			}
		}
	}
	printk(KERN_INFO"[HAL] %s thread end\n",__func__);
	return 0;
}
int rx_led_thread(void *p)
{
	while(!kthread_should_stop()) {
		que_rx_led = 0;
		wait_event_interruptible(rx_led_q, que_rx_led);
		if(kthread_should_stop()) break;
		gpio_set_value(GPIO_RX_LED,0);
		msleep(1);
		gpio_set_value(GPIO_RX_LED,1);
	}
	printk(KERN_INFO"[HAL] %s thread end\n",__func__);
	return 0;
}
void EXT_set_rx_led(int value)
{
	gpio_set_value(GPIO_RX_LED,value);
	return;
}
void EXT_set_tx_led(int value)
{
	gpio_set_value(GPIO_TX_LED,value);
	return;
}
int tx_led_thread(void *p)
{
	while(!kthread_should_stop()) {
		que_tx_led = 0;
		wait_event_interruptible(tx_led_q, que_tx_led);
		if(kthread_should_stop()) break;
		gpio_set_value(GPIO_TX_LED,0);
		msleep(1);
		gpio_set_value(GPIO_TX_LED,1);
	}
	printk(KERN_INFO"[HAL] %s thread end\n",__func__);
	return 0;
}
// rf hardware interrupt handler
extern uint32_t phy_intsrc(void);
static irqreturn_t rf_irq_handler(int irq,void *dev_id) {
	if(ext_irq_func)
	{
		m.trigger |= 0x01;
		//if (que_irq==0)
		//{
		//			printk(KERN_INFO"%s %s %d %d\n",__FILE__,__func__,__LINE__,que_irq);
		if((macl.rxdone == false) && (macl.txdone == false )) {
			printk(KERN_INFO"%s %d rx & tx\n",__func__,__LINE__);
		}
		if(macl.rxdone && macl.txdone) {
			macl.rxdone = false;
		}
		que_irq=1;
		wake_up_interruptible_sync(&rf_irq_q);
		//return IRQ_WAKE_THREAD;
		//}
	}
	return IRQ_HANDLED;
}

int spi_probe(void){
	int status;
	// millis timer initialization
	millis_init();
	// Hardware Initialization
	// i2c initialization
	status = lzpi_i2c_init();
	if(status != 0) {
		status = HAL_ERROR_I2C;
		goto error;
	}
	status = lzpi_i2c_adapter_init(m.i2c.i2c_addr);
	if(status != 0) {
		status = HAL_ERROR_I2C;
		goto error;
	}

	// init external functions
	ext_timer_func = NULL;
	ext_irq_func = NULL;
	ext_irq_enb = false;
	timer4_irq_func = NULL;

	//timer4.set(1000,NULL);
	//timer4.start();

	// IRQ Initializing
	que_irq = 1;
	que_tx_led = 1;
	que_rx_led = 1;
	init_waitqueue_head( &rf_irq_q );
	init_waitqueue_head( &rx_led_q );
	init_waitqueue_head( &tx_led_q );
	init_waitqueue_head( &ext_q );

	// create GPIO irq
	gpio_direction_input(PHY_SINTN);
	status = request_irq(gpio_to_irq(PHY_SINTN),
			rf_irq_handler,
			IRQF_TRIGGER_FALLING,
			"hal_lazurite", NULL);
	if(status != 0)
	{
		status = HAL_ERROR_IRQ;
		goto error_irq;
	}
	disable_irq(gpio_to_irq(PHY_SINTN));
	flag_irq_enable = false;
	// GPIO Initializing
	gpio_direction_output(PHY_RESETN,0);
	gpio_direction_output(GPIO_TX_LED,1);
	gpio_direction_output(GPIO_RX_LED,1);

	// PHY reset
	gpio_set_value(PHY_RESETN,0);

	// start thread
	rf_main_task = kthread_run(rf_main_thread, NULL,"lzpi_rf_main_thread");
	if (IS_ERR(rf_main_task)) {
		status = HAL_ERROR_THREAD;
		goto error_thread;
	}
	printk(KERN_INFO"[HAL] %s thread start pid=%d\n",rf_main_task->comm,rf_main_task->pid);

	rx_led_task = kthread_run(rx_led_thread, NULL,"lzpi_rx_led_thread");
	if (IS_ERR(rx_led_task)) {
		status = HAL_ERROR_THREAD;
		goto error_thread;
	}
	printk(KERN_INFO"[HAL] %s thread start pid=%d\n",rx_led_task->comm,rx_led_task->pid);
	tx_led_task = kthread_run(tx_led_thread, NULL, "lzpi_tx_led_thread");
	if (IS_ERR(tx_led_task)) {
		status = HAL_ERROR_THREAD;
		goto error_thread;
	}
	printk(KERN_INFO"[HAL] %s thread start pid=%d\n",tx_led_task->comm,tx_led_task->pid);

	return 0;

	// Error process
error_thread:
	if(rf_main_task) kthread_stop(rf_main_task);
	if(tx_led_task) kthread_stop(tx_led_task);
	if(rx_led_task) kthread_stop(rx_led_task);

	HAL_GPIO_disableInterrupt();

	free_irq(gpio_to_irq(PHY_SINTN), NULL);
	gpio_free(PHY_RESETN);
	gpio_free(GPIO_TX_LED);
	gpio_free(GPIO_RX_LED);
	gpio_free(PHY_SINTN);
error_irq:
	lzpi_spi_del_driver();
	lzpi_i2c_del_driver();
error:
	return status;
}


/******************************************************************************
Returns:
wait_event_interruptible_timeout - sleep until a condition gets true or a timeout elapses
0: timeout
n: remaining time
 ******************************************************************************/
/*
int HAL_init_waitqueue_head(wait_queue_head_t *q) {
	init_waitqueue_head(q);
	return 0;
}
uint32_t HAL_wait_event_interruptible_timeout(wait_queue_head_t *q,volatile int *condition,uint32_t ms){
	uint32_t status;
	status = wait_event_interruptible_timeout(*q, *condition,ms*HZ/1000);
	return status;
}

#include "../macl.h"
extern struct macl_param macl;
int HAL_wake_up_interruptible(wait_queue_head_t *q)
{
	int status=0;
	wake_up_interruptible_sync(q);
	return status;
}
*/

uint8_t lastSequenceNum = 0;
void timer4_func(void) {
	printk(KERN_INFO"%s %s %d %d\n",__FILE__,__func__,__LINE__,macl.condition);
	if(macl.sequenceNum == lastSequenceNum) {
		phy_monitor();
		printk(KERN_INFO"%s %s %d %d\n",__FILE__,__func__,__LINE__,mutex_is_locked(&chrdev.lock));
	}
	lastSequenceNum = macl.sequenceNum;
}
int HAL_init(struct hw_mode *mode){
	int status;

	m.i2c.i2c_addr = mode->i2c_addr;
	m.i2c.addr_bits = mode->i2c_addr_bits;
	status = lzpi_spi_init(spi_probe);

	if(status != 0){
		status = HAL_ERROR_SPI;
		lzpi_i2c_del_driver();
	}

	return status;
}

int HAL_remove(void)
{
	//del_timer(&syslog_timer);
	mutex_unlock( &chrdev.lock );
	timer4.stop();
	HAL_GPIO_disableInterrupt();
	ext_irq_func = NULL;
	free_irq(gpio_to_irq(PHY_SINTN), NULL);
	que_irq = 1;
	que_tx_led = 1;
	que_rx_led = 1;
	if(rf_main_task) kthread_stop(rf_main_task);
	if(tx_led_task) kthread_stop(tx_led_task);
	if(rx_led_task) kthread_stop(rx_led_task);
	HAL_GPIO_disableInterrupt();
	mdelay(10);
	gpio_free(PHY_RESETN);
	gpio_free(GPIO_TX_LED);
	gpio_free(GPIO_RX_LED);
	gpio_free(PHY_SINTN);
	lzpi_spi_del_driver();
	lzpi_i2c_del_driver();
	return 0;
}

int HAL_SPI_transfer(const uint8_t *wdata, uint16_t wsize,unsigned char *rdata, uint16_t rsize)
{
	static int access_num = 0;
	int result;
	if(access_num != 0) {
		printk(KERN_INFO"%s %d %d %d %d\n",__func__,__LINE__,access_num,macl.rxdone,macl.txdone);
	}
	access_num++;
	result = lzpi_spi_transfer(wdata,wsize,rdata,rsize);
	access_num--;
	return result;
}

int HAL_GPIO_setInterrupt(void (*func)(void))
{
	ext_irq_func = func;
	//printk(KERN_INFO"%s %s %d %08lx\n",__FILE__,__func__,__LINE__,(unsigned long)ext_irq_func);
	return STATUS_OK;
}

extern uint32_t phy_intsrc(void);
int HAL_GPIO_enableInterrupt(void)
{
	if(gpio_get_value(PHY_SINTN) == 0) {
		printk(KERN_INFO"%s %s %d %08x\n",__FILE__,__func__,__LINE__,phy_intsrc());
	}
	if(!flag_irq_enable) enable_irq(gpio_to_irq(PHY_SINTN));
	flag_irq_enable = true;
	return STATUS_OK;
}

int HAL_GPIO_disableInterrupt(void)
{
	if(flag_irq_enable) disable_irq(gpio_to_irq(PHY_SINTN));
	flag_irq_enable = false;
	m.trigger&=~0x01;
	return STATUS_OK;
}

int HAL_I2C_read(unsigned short addr, unsigned char *data, unsigned char size)
{
	uint8_t wtmp[2];
	if(m.i2c.addr_bits <= 8) {
		wtmp[0] = addr&0x00FF;
		lzpi_i2c_write(&wtmp[0],1);
	} else {
		wtmp[0] = (addr>>8)&0x00FF;
		wtmp[1] = addr&0x00FF;
		lzpi_i2c_write(&wtmp[0],2);
	}
	lzpi_i2c_read(data,size);

	return STATUS_OK;
}


// timer function
static bool timer_flag=false;
void timer_function(struct timer_list *t)
{
	if(ext_timer_func){
		m.trigger|=0x02;
		que_irq=1;
		wake_up_interruptible_sync(&rf_irq_q);
	}
	timer_flag=false;
}

int HAL_TIMER_start(uint16_t msec, void (*func)(void))
{
	uint32_t ms32 = msec;
	if(timer_flag == true) {
		del_timer(&g_timer);
		timer_flag = false;
		printk(KERN_INFO"%s %s %d HAL_TIMER conflict\n",__FILE__,__func__,__LINE__);
	}
	ms32 = ms32*HZ/1000;
	g_timer.expires = jiffies + ms32;
	g_timer.function = timer_function;
	ext_timer_func = func;
	add_timer(&g_timer);
	timer_flag = true;
	return STATUS_OK;
}

int HAL_TIMER_stop(void)
{
	if(timer_flag == true) {
		timer_flag = false;
		del_timer(&g_timer);
		ext_timer_func = NULL;
	}
	return STATUS_OK;
}

void HAL_sleep(uint32_t ms) {
	udelay(ms*1000);
	return;
}

// #include "../phy.h" 
int EXT_SPI_transfer(const uint8_t *wdata, uint16_t wsize,uint8_t *rdata, uint16_t rsize)
{
	int status; 
	m.spi.wdata = wdata;
	m.spi.wsize = wsize;
	m.spi.rdata = rdata;
	m.spi.rsize = rsize;
	m.trigger |= 0x04;
	//if(que_irq == 0)
	//{
	que_irq = 1;
	wake_up_interruptible(&rf_irq_q);
	que_th2ex = false;
	status = wait_event_interruptible_timeout(ext_q,que_th2ex,2);
	//} else {
	//return -EBUSY;
	//}
	return m.spi.ret;
}

int EXT_I2C_read(unsigned short addr, unsigned char *data, unsigned char size)
{
	m.i2c.addr = addr;
	m.i2c.data = data;
	m.i2c.size = size;
	m.trigger |= 0x08;
	que_irq=1;
	wake_up_interruptible(&rf_irq_q);
	que_th2ex = false;
	wait_event_interruptible_timeout(ext_q,que_th2ex,2);
	return m.i2c.ret;
}

void EXT_tx_led_flash(uint32_t time)
{
	if(que_tx_led == 0)
		que_tx_led = 1;
	wake_up_interruptible(&tx_led_q);
}
void EXT_rx_led_flash(uint32_t time)
{
	if(que_rx_led == 0)
		que_rx_led = 1;
	wake_up_interruptible(&rx_led_q);
}

// no need in Raspberry Pi
void HAL_noInterrupts(void) {
}

// no need in Raspberry Pi
void HAL_interrupts(void) {
	que_irq=0;
}

int HAL_GPIO_setValue(uint8_t pin, uint8_t value) {
	gpio_set_value(pin,value);
	return 0;
}
int HAL_GPIO_getValue(uint8_t pin, uint8_t *value) {
	*value = gpio_get_value(pin);
	return 0;
}
void HAL_reset(void) {
}
int32_t map(int32_t x,int32_t in_min,int32_t in_max,int32_t out_min,int32_t out_max){
	return (out_min+(x-in_min)*(out_max - out_min)/(in_max - in_min));
}
