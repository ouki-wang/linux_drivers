obj-m += ker_items.o

ARCH            ?= arm
CROSS_COMPILE   ?= /home/dfrobot/Desktop/f1c/buildroot-tiny200/output/host/bin/arm-buildroot-linux-gnueabi-
KDIR := /home/dfrobot/Desktop/f1c/buildroot-tiny200/output/build/linux-5.4.66
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -f *.ko *.o *.mod *.mod.o *.mod.c *.symvers modul*
