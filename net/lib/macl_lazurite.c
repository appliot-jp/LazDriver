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


#include <linux/module.h>
#include "common_lazurite.h"
#include "phy_lazurite.h"
#include "macl_lazurite.h"
#include "errno.h"
#include "endian.h"
#include "common-lzpi.h"

MACL_PARAM macl;
MACL_PARAM* macl_init(void)
{
	memset(&macl,0,sizeof(MACL_PARAM));
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) {
		printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
	}
#endif
	macl.phy = phy_init();
	return &macl;
}

/********************************************************************/
/*! @brief macl start 
  mac low layer rx on
  @return     0=STATUS_OK, other = error
  @exception  return NULL
 ********************************************************************/
int	macl_start(void)
{
	int status=STATUS_OK;
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) {
		const uint8_t test1[]={
			0x21,0xA8,0x01,0xCD, 0xAB,0x34,0x12,0x34,
			0x12,0x68,0x65,0x6C, 0x6C,0x6F};
		const uint8_t test2[]={
			0x21,0xAC,0x01,0xCD, 0xAB,0x34,0x12,0x0C,
			0x60,0x63,0x00,0x90, 0x12,0x1D,0x00,0x68,
			0x65,0x6C,0x6C,0x6F};
		printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
		memcpy(macl.phy->in.data,test1,sizeof(test1));
		macl.phy->in.len=sizeof(test1);
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) {
		printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
	}
#endif
		macl_rx_irq(&macl.phy->in);
		memcpy(macl.phy->in.data,test2,sizeof(test2));
		macl.phy->in.len=sizeof(test2);
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) {
		printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
	}
#endif
		macl_rx_irq(&macl.phy->in);
	}
#endif
	return status;
}
int	macl_stop(void)
{
	int status=STATUS_OK;
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) {
		printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
	}
#endif
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
	*level = 0xa5;
	return status;
}
int	macl_set_channel(uint8_t page,uint8_t ch)
{
	int status=STATUS_OK;
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) {
		printk(KERN_INFO"%s,%s,%d,%d\n",__FILE__,__func__,page,ch);
	}
#endif
	return status;
}
int	macl_set_hw_addr_filt(struct ieee802154_hw_addr_filt *filt,unsigned long changed)
{
	int status=STATUS_OK;
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) {
		printk(KERN_INFO"%s,%s, %02x%02x%02x%02x%02x%02x%02x%02x,%04x,%04x,%d\n",
				__FILE__,
				__func__,
				filt->ieee_addr[7],
				filt->ieee_addr[6],
				filt->ieee_addr[5],
				filt->ieee_addr[4],
				filt->ieee_addr[3],
				filt->ieee_addr[2],
				filt->ieee_addr[1],
				filt->ieee_addr[0],
				filt->pan_id,
				filt->short_addr,
				filt->pan_coord
			  );
	}
#endif
	return status;
}
int	macl_set_txpower(uint32_t mbm)
{
	int status=STATUS_OK;
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) {
		printk(KERN_INFO"%s,%s,%d\n",__FILE__,__func__,mbm);
	}
#endif
	return status;
}
//extern int	macl_set_lbt(struct ieee802154_hw *hw, bool on);				// does not support
int	macl_ch_scan(uint32_t duration)
{
	int status=STATUS_OK;
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) {
		printk(KERN_INFO"%s,%s,%d\n",__FILE__,__func__,duration);
	}
#endif
	return status;
}
int	macl_set_cca_mode(const struct wpan_phy_cca *cca)
{
	int status=STATUS_OK;
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) {
		printk(KERN_INFO"%s,%s,%d,%d\n",__FILE__,__func__,
				cca->mode,
				cca->opt
			  );
	}
#endif
	return status;
}
int	macl_set_cca_ed_level(uint32_t mbm)
{
	int status=STATUS_OK;
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) {
		printk(KERN_INFO"%s,%s,%d\n",__FILE__,__func__,mbm);
	}
#endif
	return status;
}
int	macl_set_csma_params(uint8_t min_be, uint8_t max_be, uint8_t retries)
{
	int status=STATUS_OK;
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) {
		printk(KERN_INFO"%s,%s,%d,%d\n",__FILE__,__func__,min_be,max_be);
	}
#endif
	return status;
}
int	macl_set_frame_retries(int8_t retries)
{
	int status=STATUS_OK;
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) {
		printk(KERN_INFO"%s,%s,%d\n",__FILE__,__func__,retries);
	}
#endif
	return status;
}
int	macl_set_promiscuous_mode(const bool on)
{
	int status=STATUS_OK;
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) {
		printk(KERN_INFO"%s,%s,%d\n",__FILE__,__func__,on);
	}
#endif
	return status;
}

int	macl_sleep(bool on)
{
	int status=STATUS_OK;
#ifndef LAZURITE_IDE
	if(module_test & MODE_MACL_DEBUG) {
		printk(KERN_INFO"%s,%s,%d\n",__FILE__,__func__,on);
	}
#endif
	return status;
}

