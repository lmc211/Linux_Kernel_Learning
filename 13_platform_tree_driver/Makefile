obj-m += platform_tree_driver.o
KDIR:= /lib/modules/5.15.0-139-generic/build
PWD?= $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.o *.ko *.mod.o* *.symvers *.order *.mod.c *.mod *.cmd .*.*.cmd