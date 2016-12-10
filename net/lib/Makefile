KERNEL_SRC=/lib/modules/$(shell uname -r)/build
CFILES = drv-lazurite.c subghz_api.c aes/aes.c mach_lazurite.c  arib_lazurite.c macl_lazurite.c phy_ml7396.c hwif/hal-lzpi.c  hwif/random.c  hwif/spi-lzpi.c hwif/i2c-lzpi.c 

obj-m += lazdriver.o
lazdriver-objs := $(CFILES:.c=.o)

all:
	make -C $(KERNEL_SRC) SUBDIRS=$(PWD) modules

clean:
	make -C $(KERNEL_SRC) SUBDIRS=$(PWD) clean

clean-files := *.o *.ko *.mod.[co] *~

