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

//extern ssize_t dec_data_to_header(const uint8_t *in,ssize_t size, t_MAC_HEADER *hdr);
//extern ssize_t cmd_phy_reset(const uint8_t *in,size_t size) ;
//extern ssize_t cmd_send_data(const uint8_t *in, size_t size, t_MAC_HEADER* hdr) ;
//extern ssize_t cmd_set_rx_param(const uint8_t *in, size_t size, t_MAC_HEADER* hdr) ;
//extern ssize_t cmd_get_ed_val(const uint8_t *in, size_t size, t_MAC_HEADER* hdr) ;
extern ssize_t gen_tx_stream(const uint8_t *in, ssize_t size) ;
extern uint16_t gen_rx_stream(uint8_t *out, t_MAC_HEADER *phdr) ;


