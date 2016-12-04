/* macl_lazurite.h - 
 *
 * Copyright (c) 2015  LAPIS Semiconductor Co.,Ltd.
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


#include "common_lazurite.h"
#include "phy_lazurite.h"
#include "macl_lazurite.h"
#include "errno.h"
#include "endian.h"

MACL_PARAM macl;
MACL_PARAM* macl_init(void)
{
	memset(&macl,0,sizeof(MACL_PARAM));
	return &macl;
}
int	macl_start(void)
{
	int status=STATUS_OK;
	return status;
}
int	macl_stop(void)
{
	int status=STATUS_OK;
	return status;
}
int	macl_xmit_sync(BUFFER buff)
{
	int status=STATUS_OK;
	return status;
}
//extern int	macl_xmit_async(BUFFER buff);								// for linux. does not support
int	macl_ed(uint8_t *level)
{
	int status=STATUS_OK;
	return status;
}
int	macl_set_channel(uint8_t page,uint8_t ch)
{
	int status=STATUS_OK;
	return status;
}
int	macl_set_hw_addr_filt(struct ieee802154_hw_addr_filt *filt,unsigned long changed)
{
	int status=STATUS_OK;
	return status;
}
int	macl_set_txpower(uint32_t mbm)
{
	int status=STATUS_OK;
	return status;
}
//extern int	macl_set_lbt(struct ieee802154_hw *hw, bool on);				// does not support
int	macl_ch_scan(uint32_t duration)
{
	int status=STATUS_OK;
	return status;
}
int	macl_set_cca_mode(const struct wpan_phy_cca *cca)
{
	int status=STATUS_OK;
	return status;
}
int	macl_set_cca_ed_level(uint32_t mbm)
{
	int status=STATUS_OK;
	return status;
}
int	macl_set_csma_params(uint8_t min_be, uint8_t max_be, uint8_t retries)
{
	int status=STATUS_OK;
	return status;
}
int	macl_set_frame_retries(int8_t retries)
{
	int status=STATUS_OK;
	return status;
}
int	macl_set_promiscuous_mode(const bool on)
{
	int status=STATUS_OK;
	return status;
}
int	macl_rx_irq(BUFFER *rx)
{
	int status=STATUS_OK;
	return status;
}

int	macl_sleep(bool on)
{
	int status=STATUS_OK;
	return status;
}

int	get_mac_addr(uint8_t *macaddr)
{
	int status=STATUS_OK;
	return status;
}


