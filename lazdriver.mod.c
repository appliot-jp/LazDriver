#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xa8d562a, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x6bc3fbc0, __VMLINUX_SYMBOL_STR(__unregister_chrdev) },
	{ 0x3ce4ca6f, __VMLINUX_SYMBOL_STR(disable_irq) },
	{ 0xb0017c55, __VMLINUX_SYMBOL_STR(i2c_master_send) },
	{ 0x58d9fff0, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x6c09c2a4, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0x39c188d0, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0xe738a885, __VMLINUX_SYMBOL_STR(__wake_up_sync) },
	{ 0xb1e00ad4, __VMLINUX_SYMBOL_STR(gpio_to_desc) },
	{ 0x65e14d2d, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0xaece8396, __VMLINUX_SYMBOL_STR(__register_chrdev) },
	{ 0xd50a1c97, __VMLINUX_SYMBOL_STR(__spi_register_driver) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
	{ 0x9580deb, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x28cc25db, __VMLINUX_SYMBOL_STR(arm_copy_from_user) },
	{ 0x62b72b0d, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x973b21cf, __VMLINUX_SYMBOL_STR(i2c_put_adapter) },
	{ 0xc2e130cc, __VMLINUX_SYMBOL_STR(spi_setup) },
	{ 0x38d33505, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xf4fa543b, __VMLINUX_SYMBOL_STR(arm_copy_to_user) },
	{ 0x63b87fc5, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xdc798d37, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x1c7dfaf9, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0x619f08d2, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0xe16b893b, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x24f0071c, __VMLINUX_SYMBOL_STR(gpiod_direction_input) },
	{ 0x1757ab0d, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x1bb31047, __VMLINUX_SYMBOL_STR(add_timer) },
	{ 0xc1f68d9f, __VMLINUX_SYMBOL_STR(gpiod_direction_output_raw) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x77fd9bde, __VMLINUX_SYMBOL_STR(i2c_unregister_device) },
	{ 0xd9ce8457, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x94eea794, __VMLINUX_SYMBOL_STR(getnstimeofday64) },
	{ 0x60aaa1c, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0x28490be5, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xb0d9654a, __VMLINUX_SYMBOL_STR(i2c_master_recv) },
	{ 0xb9e52429, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x158f2f00, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0xfe990052, __VMLINUX_SYMBOL_STR(gpio_free) },
	{ 0xfcec0987, __VMLINUX_SYMBOL_STR(enable_irq) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x654f471b, __VMLINUX_SYMBOL_STR(spi_write_then_read) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x9073e5cd, __VMLINUX_SYMBOL_STR(gpiod_to_irq) },
	{ 0x5734e3ef, __VMLINUX_SYMBOL_STR(gpiod_set_raw_value) },
	{ 0x264586be, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x8893fa5d, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x2c94b12f, __VMLINUX_SYMBOL_STR(gpiod_get_raw_value) },
	{ 0xdf4fc966, __VMLINUX_SYMBOL_STR(i2c_get_adapter) },
	{ 0x32f82cba, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0xf837b13e, __VMLINUX_SYMBOL_STR(i2c_new_device) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("i2c:lzpi_i2c");

MODULE_INFO(srcversion, "3042BF4C56EC2DED8F0EBFA");
