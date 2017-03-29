KERNEL_SRC=/lib/modules/$(shell uname -r)/build

CFILES = drv-lazurite.c subghz_api.c aes/aes.c mach.c  arib_lazurite.c macl.c phy/phy_ml7396.c hwif/hal-lzpi.c  hwif/random.c  hwif/spi-lzpi.c hwif/i2c-lzpi.c 

lazdriver-objs := $(CFILES:.c=.o)
obj-m += lazdriver.o
clean-files := *.o *.ko *.mod.[co] *~

all:
	echo $(CFILES)
	make -C $(KERNEL_SRC) SUBDIRS=$(PWD) modules
	make -C $(KERNEL_SRC) SUBDIRS=$(PWD) modules

clean:
	make -C $(KERNEL_SRC) SUBDIRS=$(PWD) clean

