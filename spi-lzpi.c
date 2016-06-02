/*
 * BP3596 SPI Driver
 * 
 * File:  spi-bp3596.c
 * 
 * Copyright 2015 Lapis Semiconductor Co.,Ltd.
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
#include <linux/ctype.h>
#include <linux/kernel.h>
#include <linux/spi/spi.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include "spi-lzpi.h"
#include "common-lzpi.h"
#include "hal.h"
#include "hal-lzpi.h"

// call back PHY when spi_probe
int (*callback_func)(void);

//	SPI API
struct bp_spi_dev {
	struct spi_device *spi;
	char name[SPI_NAME_SIZE];
	u16 irq;
	struct mutex		lock;
};

struct bp_spi_dev *m_bp_spi;

// SPI probe
static int bp_spi_probe(struct spi_device *spi)
{
	int err;
	struct bp_spi_dev *bp_spi;

//	finish_flag = 0;
	DEBUGONDISPLAY(MODE_PHY_DEBUG,printk("[SPI] probe\n"));

	// initializing SPI
	bp_spi = kzalloc(sizeof(*bp_spi), GFP_KERNEL);
	if (!bp_spi) {
	        return -ENOMEM;
	}

	spi->bits_per_word = 8;
	spi->max_speed_hz = 5000000;
	err = spi_setup(spi);
	if (err < 0) {
		printk(KERN_ERR"spi_setup error %d\n", err);
		goto error_spi_setup;
	}

	mutex_init(&bp_spi->lock);

	bp_spi->spi = spi;
	strcpy(bp_spi->name, spi->modalias);
	bp_spi->irq = (u16)spi->irq;

	m_bp_spi = bp_spi;
	printk(KERN_INFO "bp_spi_probe name[%s]]\n", bp_spi->name);

	spi_set_drvdata(spi, bp_spi);

	DEBUGONDISPLAY(MODE_PHY_DEBUG,printk("[SPI] set drvdata\n"));

	return 0;

//error_mac_callback:
//	spi_set_drvdata(bp_spi->spi, NULL);
error_spi_setup:
	kfree(bp_spi);
	return err;
}

static int bp_spi_remove(struct spi_device *dev)
{
	struct bp_spi_dev *bp_spi = spi_get_drvdata(dev);

//	finish_flag = 1;
	// irq disable
	disable_irq(gpio_to_irq(GPIO_SINTN));
	free_irq(gpio_to_irq(GPIO_SINTN), NULL);

	spi_set_drvdata(bp_spi->spi, NULL);
	if (!bp_spi)
		return 0;
	kfree(bp_spi);
	
	/* gpio uninit */
	//gpio_free(GPIO_SINTN);

	printk(KERN_INFO "bp_spi_remove\n");
	return 0;
}

static struct spi_driver bp_spi_driver = {
	.driver = {
		.name   = "bp3596_spi",
		.owner  = THIS_MODULE,
	},
	.probe          = bp_spi_probe,
	.remove         = bp_spi_remove,
};

int bp_spi_add_driver(int (*callback)(void))
{
	int status = 0;
	callback_func = callback;
	status = spi_register_driver(&bp_spi_driver);
	if(status == SPI_OK)
	{	
		DEBUGONDISPLAY(MODE_PHY_DEBUG,printk("[SPI] init success\n"));
	}
	else
	{
		printk("[SPI] init fail\n");
	}

	return status;
}


int bp_spi_del_driver(void)
{
	int status = 0;
	spi_unregister_driver(&bp_spi_driver);
	DEBUGONDISPLAY(MODE_PHY_DEBUG,printk("[SPI] delete driver\n"));

	return status;
}

int bp_spi_transfer(const uint8_t* wdata, uint16_t wsize, uint8_t* rdata, uint16_t rsize) {
    int status;
	status = spi_write_then_read(m_bp_spi->spi,wdata, wsize, rdata, rsize);
	if(!status) printk("[BP-SPI] Unknow Error\r\n");
    return status;
}

