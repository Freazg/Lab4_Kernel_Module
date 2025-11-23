# Makefile for hello kernel module
ifneq ($(KERNELRELEASE),)
	obj-m := hello.o
else
	KDIR ?= $(HOME)/repos/linux-stable

all:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE="$(CROSS_COMPILE)" modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=arm CROSS_COMPILE="$(CROSS_COMPILE)" clean

check:
	$(KDIR)/scripts/checkpatch.pl -f hello.c

endif

.PHONY: all clean check
