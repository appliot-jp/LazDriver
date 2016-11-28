/* phy7396.h - 
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

#ifndef _PHY_H_
#define _PHY_H_

typedef struct {
	uint8_t id;
	uint16_t size;
	uint8_t *in;
	uint8_t *out;
} PHY_PARAM;

extern int phy_start(void);
extern int phy_stop(void);
extern int phy_xmit_sync(BUFFER buff);
extern int phy_xmit_async(BUFFER buff);
extern int phy_ed(uint8_t level);
extern int phy_set_channel(uint8_t page);
extern int phy_set_hw_addr_filt(struct ieee802154_hw_addr_filt *filt,unsigned long changed);
extern int phy_set_txpower(uint32_t mbm);
extern int	phy_set_lbt(struct ieee802154_hw *hw, bool on);
extern int	phy_set_cca_mode(const struct wpan_phy_cca *cca);
extern int	phy_set_cca_ed_level(uint32_t mbm);
extern int	phy_set_csma_params(uint8_t min_be, uint8_t max_be, uint8_t retries);
extern int	phy_set_frame_retries(s8 retries);
extern int phy_set_promiscuous_mode(const bool on);

enum ieee802154_hw_addr_filt_flags {
	IEEE802154_AFILT_SADDR_CHANGED		= BIT(0),
	IEEE802154_AFILT_IEEEADDR_CHANGED	= BIT(1),
	IEEE802154_AFILT_PANID_CHANGED		= BIT(2),
	IEEE802154_AFILT_PANC_CHANGED		= BIT(3),
};
#endif
