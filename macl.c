/* macl.c - 
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

#ifdef SUBGHZ_OTA
	#pragma SEGCODE "OTA_SEGCODE"
	#pragma SEGINIT "OTA_SEGINIT"
	#pragma SEGNOINIT "OTA_SEGNOINIT"
	#pragma SEGCONST "OTA_SEGCONST"
#endif
#if defined LAZURITE_IDE
	#include <driver_irq.h>
	#include "serial.h"
#elif defined ARDUINO
	#include "arduino.h"
#else
	#include <linux/module.h>
	#include "common-lzpi.h"
	#include "hwif/random-lzpi.h"
#endif

#include "mach.h"
#include "macl.h"
#include "errno.h"
#include "endian.h"
#ifndef ARDUINO
	#include "hwif/hal.h"
#else
	#include "hal.h"
#endif

MACL_PARAM macl;

/*
 ******************************************************
							 Private handler section
 ******************************************************
 */
static void macl_dummy_handler(void);
static void macl_rxdone_handler(void);
static void macl_ack_txdone_handler(void);
static void macl_tx_ack_abort_handler(void);
static void macl_fifodone_handler(void);
static void macl_ccadone_handler(void);
static void macl_cca_abort_handler(void);
static void macl_txdone_handler(void);
static void macl_tx_data_abort_handler(void);
static void macl_ack_rxdone_handler(void);
static void macl_ack_timeout_handler(void);

#if 0
static void	macl_system_monitor(uint32_t data)
{
		phy_monitor();
#ifndef LAZURITE_IDE
	printk(KERN_INFO"lazurite syslog: %d, sending retry counter: %d\n", macl.condition,macl.resendingNum);
#else
	Serial.print("lazurite syslog: ");
	Serial.println_long(macl.condition,DEC);
#endif
	return;
}
#endif


//unsigned long limit_time=0;
static int macl_total_transmission_time(uint8_t len)
{
	unsigned long current_time;
	unsigned long duration;
	int status=STATUS_OK;
		uint8_t mdelay=0;

	current_time = HAL_millis();
	
	if((macl.ch >= 24)&&(macl.ch<=32)) {
		// CHECK ARIB condition -- interval --
		if (current_time > macl.last_send_time) {
				duration = current_time - macl.last_send_time;
		}else{
				duration = current_time + ~macl.last_send_time;
		}

		if(duration < 50)
		{
						mdelay=50-duration;
						while(mdelay > 10)
						{
				HAL_sleep(10);
								mdelay -= 10;
						}
			HAL_sleep(mdelay);
		}
		// restore time
		macl.last_send_time = HAL_millis();

	}else{
			// check total send bytes in an hours -- an hours
			if (current_time > macl.start_send_time) {
					duration = current_time - macl.start_send_time;
			}else{
					duration = current_time + ~macl.start_send_time;
			}

			if(duration > 3600000L) {
					macl.total_send_bytes = 0;
				macl.start_send_time = current_time;
			}
			
			// check total send bytes in an hours -- calcurate total send bytes
			switch(macl.pages)
			{
			case 1:  /*  50kbps */
					if(macl.total_send_bytes+len>2250000L) status = -EAGAIN;
					break;
			case 2:  /* 100kbps */
					if(macl.total_send_bytes+len>4500000L) status = -EAGAIN;
					break;
			default:
					status = -EAGAIN;
					break;
			}
			if (status == STATUS_OK) macl.total_send_bytes+=len;
	}
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
		if(module_test & MODE_MACL_DEBUG) {
//		if(current_time > limit_time) {
				if(duration > 3600000L) printk(KERN_INFO"send over\n");
				if (status == -EAGAIN) {
						printk(KERN_INFO"%s,%s,duration:%ld,LEN:%d,status:%d\n",__FILE__,__func__,duration,len,status);
				}else{
						printk(KERN_INFO"start:%lx,last:%lx,duration:%ld,total_byte:%ld,delay:%d,LEN:%d\n",macl.start_send_time,macl.last_send_time,duration,macl.total_send_bytes,mdelay,len);
				}
//			limit_time = current_time + 6000;
		}
#endif
	return status;
}


static void macl_dummy_handler(void)
{
		phy_stop();
}

static void macl_rxdone_handler(void)
{
		int status;

		macl.condition=SUBGHZ_ST_RX_DONE;
	phy_timer_di();
		status = phy_rxdone(&macl.phy->in);
	if(status == STATUS_OK) {
			status = macl_rx_irq(&macl.phy->in,&macl.ack);
	}

	if ((status == STATUS_OK) && !macl.promiscuousMode && (macl_total_transmission_time(macl.phy->out.len) == STATUS_OK) && macl.ack.data){
			HAL_delayMicroseconds(macl.tx_ack_interval);
			phy_timer_handler(macl_tx_ack_abort_handler);
			phy_timer_start(20);
			phy_sint_handler(macl_ack_txdone_handler);
			phy_txStart(&macl.ack,2);
	} else {
		if(status == STATUS_OK)	macl_rx_irq(NULL,NULL);
		if(macl.rxOnEnable){
				macl.condition=SUBGHZ_ST_RX_START;
				phy_sint_handler(macl_rxdone_handler);
			phy_rxStart();
			phy_wait_phy_event();
		}else{
			phy_stop();
				macl.condition=SUBGHZ_ST_NONE;
		}
		phy_wakeup_mac_event();
	}
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG){
		if(!macl.promiscuousMode && status == STATUS_OK && macl.ack.data) {
			printk(KERN_INFO"%s,%s,%d,%08lx,%d\n",__FILE__,__func__,__LINE__,
					(unsigned long)macl.ack.data,macl.ack.len);
			PAYLOADDUMP(macl.ack.data,macl.ack.len);
		}else{
			printk(KERN_INFO"%s,%s,%lx,%d,NO ACK\n",__FILE__,__func__,
					(unsigned long)macl.phy->in.data,macl.phy->in.len);
			PAYLOADDUMP(macl.phy->in.data,macl.phy->in.len);
		}
	}
#endif
	phy_timer_ei();
}


static void macl_ack_txdone_handler(void)
{
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s,%d,%lx\n",
			__FILE__,__func__,macl.ack_timeout,(unsigned long)macl.ack.data);
#endif
	phy_timer_di();
	phy_timer_stop();
	macl.condition=SUBGHZ_ST_RX_ACK_DONE;
	macl.ack.data = NULL;
	macl.ack.len = 0;
	macl_rx_irq(NULL,NULL);
	if(macl.rxOnEnable){
			macl.condition=SUBGHZ_ST_RX_START;
			phy_sint_handler(macl_rxdone_handler);
		phy_rxStart();
		phy_wait_phy_event();
	}else{
		phy_stop();
			macl.condition=SUBGHZ_ST_NONE;
	}
	phy_wakeup_mac_event();
	phy_timer_ei();
}

static void macl_tx_ack_abort_handler(void)
{
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s,%lx,Retry:%d\n",
			__FILE__,__func__,(unsigned long)macl.phy->out.data,macl.txRetry);
#endif
	phy_sint_di();
	phy_timer_stop();
	macl.condition=SUBGHZ_ST_RX_ACK_DONE;
	macl.ack.data = NULL;
	macl.ack.len = 0;
	macl_rx_irq(NULL,NULL);
	if(macl.rxOnEnable){
			macl.condition=SUBGHZ_ST_RX_START;
			phy_sint_handler(macl_rxdone_handler);
		phy_rxStart();
		phy_wait_phy_event();
	}else{
		phy_stop();
			macl.condition=SUBGHZ_ST_NONE;
	}
	phy_wakeup_mac_event();
	phy_sint_ei();
}

static void macl_fifodone_handler(void)
{
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
	phy_timer_di();
	phy_sint_handler(macl_ccadone_handler);
	phy_ccaCtrl(CCA_FAST);
	phy_wait_phy_event();
	phy_timer_ei();
}


static void macl_ccadone_handler(void)
{
	CCA_STATE cca_state;
		int state = STATUS_OK;

	phy_timer_di();
	phy_timer_stop();
	cca_state = phy_ccadone(macl.ccaBe,macl.ccaCount,macl.ccaRetry);
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s CCA STATE:%d\n",__FILE__,__func__,cca_state);
#endif
	if(cca_state == IDLE_DETECT){
		macl.condition=SUBGHZ_ST_CCA_IDLE_DETECT;
		macl.ccaCount++;
		phy_timer_handler(macl_cca_abort_handler);
		phy_timer_start(50);
		phy_sint_handler(macl_ccadone_handler);
		state = phy_ccaCtrl(cca_state);
		// phy_wait_phy_event();
	}else if(cca_state == CCA_RETRY){
		macl.condition=SUBGHZ_ST_CCA_RETRY;
		macl.ccaCount++;
		phy_timer_handler(macl_cca_abort_handler);
		phy_timer_start(50);
		phy_sint_handler(macl_ccadone_handler);
		state = phy_ccaCtrl(cca_state);
		phy_wait_phy_event();
	}else if(cca_state == CCA_FAILURE){
		macl.condition=SUBGHZ_ST_CCA_FAILURE;
		state = phy_ccaCtrl(cca_state);
		if(macl.rxOnEnable){
			macl.condition=SUBGHZ_ST_RX_START;
			phy_sint_handler(macl_rxdone_handler);
			phy_rxStart();
			phy_wait_phy_event();
		}else{
			macl.condition=SUBGHZ_ST_NONE;
			phy_stop();
		}
		macl.status = -EBUSY;
		phy_wakeup_mac_event();
	}else if(cca_state == CCA_IDLE){
		macl.condition=SUBGHZ_ST_CCA_DONE;
				phy_timer_handler(macl_tx_data_abort_handler);
				phy_timer_start(160);
				phy_sint_handler(macl_txdone_handler);
		state = phy_ccaCtrl(cca_state);
	}
	phy_timer_ei();
}


static void macl_cca_abort_handler(void)
{
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
	phy_sint_di();
	phy_timer_stop();
	macl.condition=SUBGHZ_ST_CCA_ABORT;
	phy_ccaCtrl(CCA_FAILURE);
	if(macl.rxOnEnable){
		macl.condition=SUBGHZ_ST_RX_START;
		phy_sint_handler(macl_rxdone_handler);
		phy_rxStart();
		phy_wait_phy_event();
	}else{
		macl.condition=SUBGHZ_ST_NONE;
		phy_stop();
	}
	macl.status = -EBUSY;
	phy_wakeup_mac_event();
	phy_sint_ei();
}

static void macl_tx_data_abort_handler(void)
{
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
	phy_sint_di();
	phy_timer_stop();
	phy_txdone();
	if(macl.rxOnEnable){
		macl.condition=SUBGHZ_ST_RX_START;
		phy_sint_handler(macl_rxdone_handler);
		phy_rxStart();
		phy_wait_phy_event();
	}else{
		phy_stop();
		macl.condition=SUBGHZ_ST_NONE;
	}
	macl.status = -EFBIG;
	phy_wakeup_mac_event();
	phy_sint_ei();
}

static void macl_txdone_handler(void)
{
	uint8_t ack_req;
	uint16_t timeout;
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s,%d,%lx,%d\n",
			__FILE__,__func__,macl.ack_timeout,(unsigned long)macl.ack.data,macl.phy->out.data[0]);
#endif
	phy_timer_di();
	phy_timer_stop();
	macl.condition=SUBGHZ_ST_TX_DONE;
	phy_txdone();
	ack_req = macl.phy->out.data[0]&0x20;
	if(ack_req){
		phy_timer_handler(macl_ack_timeout_handler);
		if(macl.ack_timeout == 0) {
						// JJ300 spec: more than 5
			timeout = 5 + (rand() % 15);
//		printk(KERN_INFO"ACK_TIMEOUT1:%s,%s,%d,%d,%d\n",__FILE__,__func__,timeout,rand(),rand()%15);
		} else {
			timeout = macl.ack_timeout;
//		printk(KERN_INFO"ACK_TIMEOUT2:%s,%s,%d\n",__FILE__,__func__,timeout);
		}
		phy_timer_start(timeout);
		phy_sint_handler(macl_ack_rxdone_handler);
		phy_rxStart();
	}else{
		if(macl.rxOnEnable){
			macl.condition=SUBGHZ_ST_RX_START;
			phy_sint_handler(macl_rxdone_handler);
			phy_rxStart();
			phy_wait_phy_event();
		}else{
			phy_stop();
			macl.condition=SUBGHZ_ST_NONE;
		}
		phy_wakeup_mac_event();
	}
	phy_timer_ei();
}


static void macl_ack_rxdone_handler(void)
{
	int status;

	phy_timer_di();
	macl.condition=SUBGHZ_ST_TX_ACK_DONE;
	status = phy_rxdone(&macl.phy->in);
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG){
		printk(KERN_INFO"%s,%s,%d,%d,%d\n",__FILE__,__func__,macl.phy->in.data[2],macl.sequnceNum,macl.phy->in.len);
		PAYLOADDUMP(macl.phy->in.data,macl.phy->in.len);
	}
#endif
	if(status == STATUS_OK && ((macl.phy->in.data[0]&0x07) == IEEE802154_FC_TYPE_ACK) && (macl.phy->in.data[2] == macl.sequnceNum)){
		phy_timer_stop();
		if(macl.rxOnEnable){
			macl.condition=SUBGHZ_ST_RX_START;
			phy_sint_handler(macl_rxdone_handler);
			phy_rxStart();
			phy_wait_phy_event();
		}else{
			macl.condition=SUBGHZ_ST_NONE;
			phy_stop();
		}
		macl_rx_irq(&macl.phy->in,NULL);
		phy_wakeup_mac_event();
	}else{
		phy_rxStart();
		//phy_wait_phy_event();
	}
	phy_timer_ei();
}


static void macl_ack_timeout_handler(void)
{
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s,%lx,Retry:%d\n",
			__FILE__,__func__,(unsigned long)macl.phy->out.data,macl.txRetry);
#endif
	phy_sint_di();
	macl.condition=SUBGHZ_ST_TX_ACK_TIMEOUT;
	phy_timer_stop();
	phy_stop();
	if((macl.resendingNum < macl.txRetry) &&
			(macl_total_transmission_time(macl.phy->out.len) == STATUS_OK)){

		macl.resendingNum++;
		if (macl.txMode == 0) {
			macl.ccaCount=0;
			phy_txStart(&macl.phy->out,macl.txMode);
			phy_timer_handler(macl_cca_abort_handler);
			phy_timer_start(50);
			phy_sint_handler(macl_ccadone_handler);
			phy_ccaCtrl(CCA_FAST);
		}else
			if (macl.txMode == 1) {
				phy_sint_handler(macl_fifodone_handler);
				phy_txStart(&macl.phy->out,macl.txMode);
			}else
				if (macl.txMode == 2) {
					phy_sint_handler(macl_txdone_handler);
					phy_txStart(&macl.phy->out,macl.txMode);
				}
		phy_wait_phy_event();
	}else{
		if(macl.rxOnEnable){
			macl.condition=SUBGHZ_ST_RX_START;
			phy_sint_handler(macl_rxdone_handler);
			phy_rxStart();
			phy_wait_phy_event();
		}else{
			phy_stop();
			macl.condition=SUBGHZ_ST_NONE;
		}
		macl.status = -ETIMEDOUT;
		phy_wakeup_mac_event();
	}
	phy_sint_ei();
}


/*
 ******************************************************
 Public function section
 ******************************************************
 */
MACL_PARAM* macl_init(void)
{
	phy_sint_di(); phy_timer_di();

	memset(&macl,0,sizeof(MACL_PARAM));
	macl.phy = phy_init();
	// 0:normal, 1:wait at fifodone, 2:no cca
	macl.txMode = 0;
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s,in.data:%lx,out.data:%lx\n",
			__FILE__,__func__,(unsigned long)macl.phy->in.data,(unsigned long)macl.phy->out.data);
#endif
	phy_sint_handler(macl_dummy_handler);
	phy_sint_ei(); phy_timer_ei();

	macl.tx_ack_interval = 1000;

	return &macl;
}


/********************************************************************/
/*! @brief macl start 
	mac low layer rx on
	@return			0=STATUS_OK, other = error
	@exception	return NULL
 ********************************************************************/
int	macl_start(void)
{
	int status=STATUS_OK;

	macl.condition=SUBGHZ_ST_RX_START;
	macl.rxOnEnable = 1;
	phy_sint_handler(macl_rxdone_handler);
	phy_rxStart();
	phy_wait_phy_event();

	return status;
}


int	macl_stop(void)
{
	int status=STATUS_OK;
	macl.rxOnEnable = 0;
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif
	if((macl.condition == SUBGHZ_ST_NONE) && (macl.condition == SUBGHZ_ST_RX_START)){
		phy_stop();
	}
	return status;
}


int	macl_xmit_sync(BUFFER buff)
{
	int status=STATUS_OK;
	macl.condition=SUBGHZ_ST_TX_START;
	macl.status=STATUS_OK;
	macl.phy->out = buff;
	macl.resendingNum = 0;
	macl.ccaCount=0;
	macl.sequnceNum= buff.data[2];

	if(macl.condition == SUBGHZ_ST_RX_DONE){
		phy_wait_mac_event();
	}

	phy_stop();
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s\n",__FILE__,__func__);
#endif

	macl.status = macl_total_transmission_time(macl.phy->out.len);

	if (macl.status == STATUS_OK){

#ifdef LAZURITE_IDE
		dis_interrupts(DI_SUBGHZ);
#endif
#ifdef ARDUINO
		noInterrupts();
#endif
		if (macl.txMode == 0) {
			phy_txStart(&macl.phy->out,macl.txMode);
			phy_timer_handler(macl_cca_abort_handler);
			phy_timer_start(50);
			phy_sint_handler(macl_ccadone_handler);
			phy_ccaCtrl(CCA_FAST);
			macl.condition=SUBGHZ_ST_CCA_FAST;
		}else
			if (macl.txMode == 1) {
				phy_sint_handler(macl_fifodone_handler);
				phy_txStart(&macl.phy->out,macl.txMode);
			}else
				if (macl.txMode == 2) {
					phy_sint_handler(macl_txdone_handler);
					phy_txStart(&macl.phy->out,macl.txMode);
				}
#ifdef LAZURITE_IDE
		enb_interrupts(DI_SUBGHZ);
#endif
#ifdef ARDUINO
		interrupts();
#endif
		phy_wait_phy_event();
		status = phy_wait_mac_event();
	}
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
/*
		#include "phy/phy_ml7396.h"
		if(status != STATUS_OK) {
				uint8_t reg_data[4];
				phy_regread(REG_ADR_RF_STATUS,&(reg_data[0]),1);
				phy_regread(REG_ADR_INT_SOURCE_GRP2, &(reg_data[1]), 1);
				phy_regread(REG_ADR_INT_SOURCE_GRP3, &(reg_data[2]), 1);
				phy_regread(REG_ADR_INT_SOURCE_GRP4, &(reg_data[3]), 1);

				printk(KERN_INFO"%s,%s,return_wait_event:%d,%x,%x,%x,%x\n",__FILE__,__func__,status,reg_data[0],reg_data[1],
								reg_data[2],reg_data[3]);
		}
*/
	if(module_test & MODE_MACL_DEBUG) {
		printk(KERN_INFO"%s,%s,%lx,%d\n",__FILE__,__func__,(unsigned long)macl.phy->out.data,macl.status);
		PAYLOADDUMP(macl.phy->out.data,macl.phy->out.len);
	}
#endif
		if(status != STATUS_OK) {
				phy_stop();
				if(macl.rxOnEnable){
						macl.condition=SUBGHZ_ST_RX_START;
						phy_sint_handler(macl_rxdone_handler);
						phy_rxStart();
						phy_wait_phy_event();
				}else{
						macl.condition=SUBGHZ_ST_NONE;
				}
				macl.status = status;
				phy_wakeup_mac_event();
		}
	return macl.status;
}
//extern int	macl_xmit_async(BUFFER buff);								// for linux. does not support
int	macl_ed(uint8_t *level)
{
	int status=STATUS_OK;
	phy_ed(level, macl.rxOnEnable | macl.promiscuousMode);
	return status;
}
int	macl_set_channel(uint8_t page,uint8_t ch, uint32_t mbm, uint8_t antsw)
{
	int status=STATUS_OK;
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s,%d,%d\n",__FILE__,__func__,page,ch);
#endif
	macl.pages = page;
	macl.ch = ch;

	if (mbm == 100){ 
		macl.txPower = 1;
	}else {
		macl.txPower = 20;
	}

	phy_setup(page,ch,macl.txPower,antsw);
	return status;
}
int	macl_set_hw_addr_filt(struct ieee802154_my_addr *filt,unsigned long changed)
{
	int status=STATUS_OK;
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
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
	phy_addrFilt(filt->pan_id, filt->ieee_addr, filt->short_addr,0xffff);
	return status;
}

int	macl_set_csma_params(uint8_t min_be, uint8_t max_be, uint8_t retries)
{
	int status=STATUS_OK;
	macl.ccaRetry = retries;
	macl.ccaBe = max_be;
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s,%d,%d\n",__FILE__,__func__,min_be,max_be);
#endif
	return status;
}
int	macl_set_frame_retries(uint8_t retries,uint16_t timeout)
{
	int status=STATUS_OK;
	macl.txRetry = retries;
	macl.ack_timeout = timeout;
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s,%d\n",__FILE__,__func__,retries);
#endif
	return status;
}
int	macl_set_promiscuous_mode(bool on)
{
	int status=STATUS_OK;

	macl.promiscuousMode = on;

	if (macl.promiscuousMode){
		phy_clrAddrFilt();
	}else{
		phy_stop();
	}

	return status;
}

int	macl_sleep(bool on)
{
	int status=STATUS_OK;
#if !defined(LAZURITE_IDE) && !defined(ARDUINO)
	if(module_test & MODE_MACL_DEBUG) printk(KERN_INFO"%s,%s,%d\n",__FILE__,__func__,on);
#endif
	phy_sleep();
	return status;
}


uint8_t	macl_getCondition(void)
{
	return macl.condition;
}

void macl_set_ack_tx_interval(uint16_t interval) {
	macl.tx_ack_interval = interval;
}

void macl_phy_cleanup(void)
{
	phy_cleanup();
}
