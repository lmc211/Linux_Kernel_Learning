obj-m += dev_t.o
KDIR:= /home/alientek/rk3588_linux_sdk/kernel
PWD?= $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.o *.ko *.mod.o* *.symvers *.order 