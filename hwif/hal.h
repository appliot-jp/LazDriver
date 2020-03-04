/* hal.h - HALヘッダファイル
 *
 * Copyright (c) 2015  Communication Technology Inc.,
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


#ifndef _HAL_H_
#define _HAL_H_


#if	defined LAZURITE_IDE
	//#include <lazurite_system.h>
#else	
#include <linux/delay.h>
#include <linux/wait.h>
#endif	// LAZURITE_IDE

#define HAL_ERROR_PARAM		-1	//
#define HAL_ERROR_STATE		-2	// 
#define HAL_ERROR_TIMEOUT	-3	// 
#define HAL_ERROR_SPI		-4 		 // SPI error
#define HAL_ERROR_I2C		-5 		 // I2C errror
#define HAL_ERROR_IRQ		-5 		 // IRQ error
#define HAL_ERROR_THREAD	-6 		 // thread error

#ifdef LAZURITE_IDE
	#include "hwif/hal_lazurite.h"
typedef struct {
	uint8_t que;
} wait_queue_head_t;
#else
	#include "hal-lzpi.h"
#endif

struct hw_mode {
	uint8_t i2c_addr;
	uint8_t i2c_addr_bits;
};

#ifdef LAZURITE_IDE
#pragma INLINE HAL_init_waitqueue_head HAL_wait_event_interruptible_timeout HAL_wake_up_interruptible
int HAL_init_waitqueue_head(wait_queue_head_t *q) {
	return 0;
}
uint32_t HAL_wait_event_interruptible_timeout(wait_queue_head_t q,volatile int condition,uint32_t ms){
	volatile uint32_t __st_time = millis();
	volatile uint32_t __ret;
	do {\
		__ret = __st_time - millis() +ms;
		if(__ret > ms) {
			__ret = 0;
		}
		lp_setHaltMode();
	} while((condition == false) && (__ret > 0));
	return __ret;
}
int HAL_wake_up_interruptible(wait_queue_head_t *q) {
	return 0;
}
#else
#define HAL_init_waitqueue_head(que)	init_waitqueue_head(que)
#define HAL_wait_event_interruptible_timeout(a,b,c) wait_event_interruptible_timeout(a,b,c)
#define HAL_wake_up_interruptible(que) wake_up_interruptible(que)
#endif
extern int HAL_init(struct hw_mode *mode);
extern int HAL_remove(void);
extern int HAL_GPIO_setValue(uint8_t pin, uint8_t value);
extern int HAL_GPIO_getValue(uint8_t pin, uint8_t *value);
extern int HAL_GPIO_setInterrupt(void (*func)(void));
extern int HAL_GPIO_enableInterrupt(void);
extern int HAL_GPIO_disableInterrupt(void);
extern int HAL_TIMER_setup(void);
extern int HAL_TIMER_start(uint16_t msec, void (*func)(void));
extern int HAL_TIMER_stop(void);
//extern int HAL_TIMER_getTick(uint32_t *tick);
extern int HAL_SPI_transfer(const uint8_t *wdata, uint16_t wsize,uint8_t *rdata, uint16_t rsize);
extern int HAL_I2C_read(uint16_t addr, uint8_t *data, uint8_t size);
extern void HAL_reset(void);

extern void HAL_delayMicroseconds(uint32_t us);
extern uint32_t HAL_millis(void);
extern void HAL_sleep(uint32_t ms);

extern int EXT_SPI_transfer(const uint8_t *wdata, uint16_t wsize,uint8_t *rdata, uint16_t rsize);
extern int EXT_I2C_read(uint16_t addr, uint8_t *data, uint8_t size);
extern void EXT_tx_led_flash(uint32_t time);
extern void EXT_rx_led_flash(uint32_t time);
extern void EXT_set_tx_led(int value);
extern void EXT_set_rx_led(int value);

typedef struct {
	void (*set)(uint32_t ms, void (*f)(void));
	void (*start)(void);
	void (*stop)(void);
} MsTimer4;
extern const MsTimer4 timer4;

// debug monitor function

#endif  /* #ifndef _INCLUDE_HAL_H */
