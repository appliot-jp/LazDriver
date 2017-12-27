/* arib_lazurite.c - MAC(High level) for lazurite
 *
 * Copyright (c) 2015  Lapis Semiconductor Co.,Ltd
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
 * <http://www.gnu.org/licenses/>
 */

#ifdef SUBGHZ_OTA
	#pragma SEGCODE "OTA_SEGCODE"
	#pragma SEGINIT "OTA_SEGINIT"
	#pragma SEGNOINIT "OTA_SEGNOINIT"
	#pragma SEGCONST "OTA_SEGCONST"
#endif

#include "arib_lazurite.h"
#include "hwif/hal.h"

static struct {
	unsigned long start_time;
	unsigned long last_send_time;
	unsigned long total_send_bytes;
} arib = {0,0x80000000,0};


void arib_init(void)
{
	arib.start_time = HAL_millis();
}

void arib_tx_end(uint8_t pages,uint8_t ch, uint16_t size)
{
}

bool arib_tx_check(uint8_t pages,uint8_t ch,uint16_t size)
{
	bool status;
	uint32_t current_time;
	uint32_t duration;
	uint32_t tmp_ttl_byte;
	// check total send bytes in an hours -- an hours
	current_time = HAL_millis();
	duration = current_time - arib.start_time;
	if(duration > 3600000L)
	{
		arib.total_send_bytes = 0;
		arib.start_time = current_time;
	}
	
	// check total send bytes in an hours -- calcurate total send bytes
	tmp_ttl_byte = arib.total_send_bytes;
	switch(pages)
	{
#define SUBGHZ_HEADER_SIZE	11
	case 1:			// 50kbps
		tmp_ttl_byte += size + SUBGHZ_HEADER_SIZE;
	case 2:			// 100kbps
		tmp_ttl_byte += size + SUBGHZ_HEADER_SIZE;
		if(tmp_ttl_byte>45000000)
		{
			status = false;
		}
		break;
	default:
		status = false;
		break;
	}
	
	// CHECK ARIB condition -- interval --
	duration = current_time - arib.last_send_time;
	
	if((ch >= 24)&&(ch<=32))
	{
		if(duration < 50)
		{
			HAL_sleep(50-duration);
		}
	}
	

	return status;
}
