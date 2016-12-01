KERNEL_SRC=/lib/modules/$(shell uname -r)/build
CFILES = app_lazurite.c  drv-lazurite.c  mach_lazurite.c  net_lazurite.c  subghz_api.c hal/SPI0.c  hal/Wire0.c  hal/hal-lzpi.c  hal/random.c  hal/spi-lzpi.c hal/hal_lazurite.c hal/i2c-lzpi.c hal/ml7396_hwif_hal.c 

obj-m += lazdriver.o
lazdriver-objs := $(CFILES:.c=.o)

all:
	make -C $(KERNEL_SRC) SUBDIRS=$(PWD) modules

clean:
	make -C $(KERNEL_SRC) SUBDIRS=$(PWD) clean

clean-files := *.o *.ko *.mod.[co] *~

