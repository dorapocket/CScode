MODULE_NAME := mypstree
obj-m := $(MODULE_NAME).o
KERN_VER := $(shell uname -r)
KERN_DIR ?= /lib/modules/$(KERN_VER)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERN_DIR) M=$(PWD) modules
clean: 
	$(MAKE) -C $(KERN_DIR) M=$(PWD) clean
ins:
	sudo insmod $(MODULE_NAME).ko
rm:
	sudo rmmod $(MODULE_NAME)
	sudo dmesg -C
