AREA=JP
DEBUG=OFF
RBUF=16
#RF=MK74040

ifeq ($(DEBUG),ON)
	EXTRA_CFLAGS += -DDEBUG
endif

EXTRA_CFLAGS += -D$(AREA) -DRBUF=$(RBUF)

CFILES = drv-lazurite.c subghz_api.c aes/aes.c mach.c  macl.c hwif/hal-lzpi.c  hwif/random-lzpi.c  hwif/spi-lzpi.c hwif/i2c-lzpi.c 
ifeq ($(RF),MK74040)
	CFILES += phy_ml7404/ml7404.c
else
	CFILES += phy/phy_ml7396.c
endif

lazdriver-objs := $(CFILES:.c=.o)
obj-m += lazdriver.o
clean-files := *.o *.ko *.mod.[co] *~

ifeq ($(shell uname -n),atde7)
	KERNEL_SRC=/home/atmark/linux
all:
	echo $(CFILES)
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C $(KERNEL_SRC) SUBDIRS=$(PWD) modules

clean:
	make -C $(KERNEL_SRC) SUBDIRS=$(PWD) clean
endif

ifeq ($(shell uname -n),armadillo)
	KERNEL_SRC=/lib/modules/$(shell uname -r)/build
all:
	echo $(CFILES)
	make -C $(KERNEL_SRC) SUBDIRS=$(PWD) modules

clean:
	make -C $(KERNEL_SRC) SUBDIRS=$(PWD) clean
endif

ifeq ($(shell uname -n),raspberrypi)
	KERNEL_SRC=/lib/modules/$(shell uname -r)/build

all:
	echo $(EXTRA_CFLAGS)
	make -C $(KERNEL_SRC) SUBDIRS=$(PWD) modules

clean:
	make -C $(KERNEL_SRC) SUBDIRS=$(PWD) clean
endif

