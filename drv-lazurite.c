/*
 * IEEE802.15.4e driver IO
 * 
 * File:  drv-802154e.c
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
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/ioctl.h>
#include <linux/parport.h>
#include <linux/ctype.h>
#include <linux/poll.h>
#include <linux/slab.h>
#include <linux/major.h>
#include <linux/errno.h>
#include <linux/input.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/time.h>

#include "common_802154e.h"
#include "subghz_api.h"

#define DATA_SIZE		256
#define DRV_NAME		"lzgw"
//static wait_queue_head_t read_q;	//poll wait

uint8_t rxbuf[DATA_SIZE];

struct list_data {				
	uint8_t	data[DATA_SIZE];
	int		len;
	struct list_head list;
};
struct list_data head;				// char dev list head
static struct s_CHAR_DEV {
	char name[32];
	struct class *dev_class;		// device class
	int major;						// device major number
	int access_num;					// open count
	spinlock_t	lock;				// chardev spin lock
	wait_queue_head_t	read_q;		// polling wait for char dev
} chrdev =
{
	.name = DRV_NAME,
	.access_num = 0
};
int listed_packet = 0;
// *****************************************************************
//			transfer process (input from chrdev)
// *****************************************************************
int write_list_data(uint8_t* raw,uint16_t len){
	struct list_data *new_data;
	uint8_t *in,*out;

	new_data = kmalloc(sizeof(struct list_data), GFP_KERNEL);
	if (new_data == NULL) {
		printk(KERN_ERR "[DRV-802154E] kmalloc (list_data) GFP_KERNEL no memory\n");
		return -ENOMEM;
	}
	DEBUGONDISPLAY(MODE_STREAM_DEBUG,printk(KERN_INFO "[DRV-802154E] %s 2\n", __func__));

	// copy data to list
	if(len < DATA_SIZE)
	{
		in = raw;
		out = new_data->data;
		memcpy(out,in,len);
		new_data->len = len;
		DEBUGONDISPLAY(MODE_DRV_DEBUG,PAYLOADDUMP(out, len));
		// list add 
		list_add_tail(&new_data->list, &head.list);
		listed_packet++;

		//check list length. And delete data, if list length is over maximum length.
		while(listed_packet >4) {
			struct list_data *data;
			data = list_entry(head.list.next, struct list_data, list);
			list_del(head.list.next);
			listed_packet--;
			kfree(data);
		}
		// poll wait cancell 
		wake_up_interruptible(&chrdev.read_q);	
	}
	else
	{
		printk(KERN_ERR "[DRV-802154E] add_list PHY Size error\n");
		kfree(new_data);
		return -1;
	}

	return 0;
}
int rx_callback(uint8_t *raw, uint16_t len)
{
	return write_list_data(raw,len);

}

// poll wait cancell 

// *****************************************************************
//			char dev function
// *****************************************************************
static long chardev_ioctl(struct file *file, unsigned int cmd, unsigned long arg) {
	long ret = 0;
	return ret;
}

static int chardev_open(struct inode* inode, struct file* filp) {
	spin_lock( &chrdev.lock );
	if (chrdev.access_num >= 2) {
		spin_unlock(&chrdev.lock );
		return -EBUSY;
	}
	chrdev.access_num ++;
	spin_unlock( &chrdev.lock );
	return 0;
}

static int chardev_release(struct inode* inode, struct file* filp)
{
	spin_lock( &chrdev.lock );
	chrdev.access_num --;
	spin_unlock( &chrdev.lock );
	return 0;
}

static ssize_t chardev_read (struct file * file, char __user * buf, size_t count, loff_t * ppos) {
	ssize_t bytes_read = 0;
	struct list_data *ptr = NULL;

	spin_lock( &chrdev.lock );

	// list empty
	if (list_empty(&head.list) != 0) {
		//		DEBUGONDISPLAY(MODE_DRV_DEBUG,printk("list empty\n"));   
		goto end;
	}
	// error
	ptr = list_entry(head.list.next, struct list_data, list);
	if (ptr == NULL) {
		printk( KERN_ERR "%s : list_entry failed\n", chrdev.name);
		bytes_read = 0;
		goto end;
	}
	// 2byte read,then return size
	if (count == sizeof(unsigned short)) {
		DEBUGONDISPLAY(MODE_DRV_DEBUG,printk("list_data %d[bytes]\n", ptr->len));
		bytes_read = count;
		if (bytes_read > 0 && copy_to_user (buf, &(ptr->len), count)) {
			printk( KERN_ERR "%s : copy_to_user failed\n", chrdev.name);
			bytes_read = 0;
			goto end;
		}
	} else {
		// return data
		bytes_read = count;
		if (bytes_read > 0 && copy_to_user (buf, &(ptr->data), bytes_read)) {
			printk( KERN_ERR "%s : copy_to_user failed\n", chrdev.name);
			bytes_read = 0;
			goto end;
		}
		list_del(head.list.next);
		listed_packet--;


		kfree(ptr);
	}
end:
	spin_unlock( &chrdev.lock );
	return bytes_read;
}

static ssize_t chardev_write (struct file * file, const char __user * buf,
		size_t count, loff_t * ppos) {
	int status = 0;
	spin_lock( &chrdev.lock );

	DEBUGONDISPLAY(MODE_DRV_DEBUG,PAYLOADDUMP(buf,count));		// for debug
	if(count<DATA_SIZE)
	{
	} else {
		status = -E2BIG;
		goto error;
	}

error:
	spin_unlock( &chrdev.lock );
	return status;
}

static unsigned int chardev_poll(struct file* filp, poll_table* wait) {
	unsigned int retmask = 0;
	poll_wait( filp, &chrdev.read_q,  wait );
	if (list_empty(&head.list) == 0) {
		retmask |= ( POLLIN  | POLLRDNORM );
	}
	return retmask;
}

static const struct file_operations chardev_fops = {
	.owner		= THIS_MODULE,
	.read		= chardev_read,
	.write		= chardev_write,
	.open		= chardev_open,
	.poll		= chardev_poll,
	.unlocked_ioctl	= chardev_ioctl,
	.release    = chardev_release,
};

// *****************************************************************
//			driver initialization
// *****************************************************************
static int __init drv_param_init(void) {
	//int drv_param_init(void) {
	int status = 0;
	int err;
	struct device *dev;

	// create char device
	if((chrdev.major = register_chrdev(0, DRV_NAME, &chardev_fops)) < 0)
	{
		printk(KERN_ERR "[DRV-802154E] unable to get major =%d\n",
				chrdev.major);
		goto error;
	}
	chrdev.dev_class = class_create(THIS_MODULE, chrdev.name);
	if(IS_ERR(chrdev.dev_class))
	{
		err = PTR_ERR(chrdev.dev_class);
		printk(KERN_ERR"[DRV-802154E] class_create error %d\n", err);
		goto error_class_create;
	}
	dev = device_create(chrdev.dev_class, NULL, MKDEV(chrdev.major, 0), NULL, chrdev.name);
	if (IS_ERR(dev)) {
		err = PTR_ERR(dev);
		printk(KERN_ERR"[DRV-802154E]device_create error %d\n", err);
		goto error_device_create;
	}
	DEBUGONDISPLAY(MODE_DRV_DEBUG,printk(KERN_INFO "[DRV-802154E] char dev create = %s\n",chrdev.name));

	//initializing list head
	INIT_LIST_HEAD(&head.list);

	// initializing wait queue
	init_waitqueue_head( &chrdev.read_q );

	status = SubGHz.init();
	if(status != SUBGHZ_OK) goto error_device_create;


	printk(KERN_INFO "[DRV-802154E] End of init\n");

	return status;

error_device_create:
	class_destroy(chrdev.dev_class);
error_class_create:
	unregister_chrdev(chrdev.major, chrdev.name);
error:
	printk(KERN_INFO "[DRV-802154E] Init Error\n");
	return status;
}

// *****************************************************************
//			unload driver 
// *****************************************************************
static void __exit drv_param_exit(void) {
	//void drv_param_exit(void) {
	//	mac_802154e_exit();
	//list delete 
	printk(KERN_INFO "[DRV-802154E] remove\n");
	while (!list_empty(&head.list)) {
		struct list_data *data;
		data = list_entry(head.list.next, struct list_data, list);
		list_del(head.list.next);
		listed_packet--;
		kfree(data);
	}

	// char dev destroy
	device_destroy(chrdev.dev_class, MKDEV(chrdev.major, 0));
	class_destroy(chrdev.dev_class);
	unregister_chrdev(chrdev.major, chrdev.name);
	DEBUGONDISPLAY(MODE_DRV_DEBUG,printk(KERN_INFO "[DRV-802154E] char dev delete\n"));
	// mac remove
	SubGHz.remove();
	printk(KERN_INFO "[DRV-802154E] exit remove\n");
	return;
}


module_init(drv_param_init);
module_exit(drv_param_exit);

MODULE_AUTHOR("Lapis Semiconductor.");
MODULE_DESCRIPTION("Lazurite Kernel Driver");
MODULE_LICENSE("Dual BSD/GPL");

