/*
 * IEEE802.15.4e command interface
 * 
 * File:  cmdif.c
 * 
 * Copyright 2016 Lapis Semiconductor Co.,Ltd.
 * Author: Naotaka Saito
 * 
 * The program is based on BP3596 driver by Communication Technology
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/input.h>
#include <linux/kernel.h>

#define		CMD_READ			0xFFFE
#define		CMD_NOP				0x0000
#define		CMD_PHY_RESET		0x0101
#define		CMD_TX				0x0201
#define		CMD_RX				0x0303
#define		CMD_GET_CH			0x0401
#define		CMD_SET_CH			0x0403
#define		CMD_GET_RATE		0x0405
#define		CMD_SET_RATE		0x0407
#define		CMD_GET_PWR			0x0409
#define		CMD_SET_PWR			0x040B
#define		CMD_SET_RXON		0x040D
#define		CMD_SET_RXOFF		0x040F
#define		CMD_GET_PANID		0x0411
#define		CMD_SET_PANID		0x0413
#define		CMD_GET_EDVAL		0x0415
#define		CMD_GET_CCA_CYCLE	0x0417
#define		CMD_SET_CCA_CYCLE	0x0419
#define		CMD_GET_TX_RETRY	0x041B
#define		CMD_SET_TX_RETRY	0x041D
//extern ssize_t dec_data_to_header(const uint8_t *in,ssize_t size, t_MAC_HEADER *hdr);
//extern ssize_t cmd_phy_reset(const uint8_t *in,size_t size) ;
//extern ssize_t cmd_send_data(const uint8_t *in, size_t size, t_MAC_HEADER* hdr) ;
//extern ssize_t cmd_set_rx_param(const uint8_t *in, size_t size, t_MAC_HEADER* hdr) ;
//extern ssize_t cmd_get_ed_val(const uint8_t *in, size_t size, t_MAC_HEADER* hdr) ;
extern ssize_t gen_tx_stream(const uint8_t *in, ssize_t size) ;
extern uint16_t gen_rx_stream(uint8_t *out, t_MAC_HEADER *phdr,uint16_t command) ;


