KERNEL_SRC=/lib/modules/$(shell uname -r)/build
CFILES = drv-802154e.c subghz_api.c mac-802154e.c phy-bp3596.c i2c-lzgw.c spi-lzgw.c ieee802154e.c drv-cmdif.c hal-lzgw.c

obj-m += lazdriver.o
lazdriver-objs := $(CFILES:.c=.o)

all:
	make -C $(KERNEL_SRC) SUBDIRS=$(PWD) modules

clean:
	make -C $(KERNEL_SRC) SUBDIRS=$(PWD) clean

clean-files := *.o *.ko *.mod.[co] *~

