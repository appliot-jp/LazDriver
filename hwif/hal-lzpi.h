/* hal-lzpi.h  header file for Raspberry Pi
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


#ifndef _HAL_LZPI_H_
#define _HAL_LZPI_H_

#include <linux/wait.h>
#include <linux/sched.h>

#define PHY_RESETN			27
#define PHY_REGPDIN			17
#define PHY_SINTN				18
#define GPIO_TX_LED 		6
#define GPIO_RX_LED			13

struct s_CHAR_DEV {
	char name[32];
	struct class *dev_class;		// device class
	int major;						// device major number
	int access_num;					// open count
	struct mutex	lock;				// chrdev spin lock
	wait_queue_head_t	read_q;		// polling wait for char dev
};
struct thread_param {
	volatile uint16_t trigger;
	struct {
		const uint8_t* wdata;
		uint16_t wsize;
		uint8_t* rdata;
		uint16_t rsize;
		int ret;
	} spi;
	struct {
		uint16_t addr;
		uint8_t* data;
		uint8_t size;
		int ret;
		uint8_t addr_bits;
		uint8_t i2c_addr;
	} i2c;
	struct {
		uint32_t time;
	} led;
};

extern int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max);

#endif  /* #ifndef _HAL_LZPI_H_ */
