
/* mac_lazurite.c - MAC for lazurite
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

static MAC_PARAM mac;
MAC_PARAM *mac_init(LAZURITE_APP *app)
{
	app.mac = mac;
	memset(mac,0,sizeof(MAC_PARAM));
	get_mac_addr(&mac.dstaddr.addr.addr64);
	mac.phy = phy_init();
	if(mac.phy == NULL) return NULL;
	return &mac;
}
int mac_start() {
	// initialize mac
	memset(mac,0,sizeof(mac));

	// initialize phy  <== ml7396_reset();
	return status;
}
int mac_stop() {
}

int mac_setup(uint8_t ch, uint8_t rate, uint8_t txPower, uint8_t senseTime,uint8_t txRetry,uint16_t txInterval, uint8_t ccaWait) {
	uint8_t pages;
	int status;
	// set baudrate
	if (rate==50) pages = 1;
	else if (rate == 100) pages = 2;
	else 
	{
		status = -1;
		goto error;
	}

	// set channel
	if(phy_set_channel(pages,ch) != STATUS_OK){
		status = -1; 
		goto error;
	}

	// @issue check relation between parameters and setting
	// set setting CCA
	phy_set_txpower(pwr);

	// set setting CCA
	phy_set_csma_params(min_be,max_be,txRetry);
	phy_frame_retries(txRetry);
	phy_ch_scan(uint32_t duration);				// add 
	phy_set_cca_mode(const struct wpan_phy_cca *cca);
	phy_set_cca_ed_level(uint32_t mbm);
	phy_set_csma_params(uint8_t min_be, uint8_t max_be, uint8_t retries);


	// @issue check conversion fron pwr to mbm
	int	phy_set_cca_mode(const struct wpan_phy_cca *cca);
	int	phy_set_cca_ed_level(uint32_t mbm);
	int	phy_set_csma_params(uint8_t min_be, uint8_t max_be, uint8_t retries);
error:

	return status;
}


int mac_tx() {
}
