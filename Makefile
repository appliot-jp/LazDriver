KERNEL_SRC=/lib/modules/$(shell uname -r)/build
CFILES = drv-lazurite.c subghz_api.c mac-lazurite.c phy-ml7396b.c i2c-lzpi.c spi-lzpi.c hal-lzpi.c

obj-m += lazdriver.o
lazdriver-objs := $(CFILES:.c=.o)

all:
	make -C $(KERNEL_SRC) SUBDIRS=$(PWD) modules

clean:
	make -C $(KERNEL_SRC) SUBDIRS=$(PWD) clean

clean-files := *.o *.ko *.mod.[co] *~

