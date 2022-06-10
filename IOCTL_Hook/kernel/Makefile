# https://github.com/croemheld/lkm-rootkit/blob/master/Makefile
# Module name
MODULE_NAME := hello

# Build
BUILDDIR := ../../linux-5.4

PWD := $(shell pwd)

ifneq ($(KERNELRELEASE),)

# Module
obj-m := $(MODULE_NAME).o

# Source
$(MODULE_NAME)-y += core.o
$(MODULE_NAME)-y += ioctl_hook.o

else

all:
	$(MAKE) -C $(BUILDDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(BUILDDIR) M=$(PWD) clean

endif
