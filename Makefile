#	makefile for building modules of kernel
#	author: a.smirnov
##

TARGET_NAME := can_ocp.c

PWD := $(shell pwd)
SRC := src

KERNEL_SOURCE := /usr/src/linux-2.6.32.71

KERNEL_VERS := $(shell uname -r)
# KERNEL_DIR := /lib/modules/$(KERNEL_VERS)/build

$(TARGET_NAME)-objs = $(SRC)/$(TARGET_NAME:.c=.o)
obj-m := $(TARGET_NAME).o

default: 
	$(MAKE) -C $(KERNEL_SOURCE) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_SOURCE) M=$(PWD) clean


TARGET_NAME := can_ocp.c

PWD := $(shell pwd)
SRC := src

KERNEL_SOURCE := /usr/src/linux-2.6.32.71

KERNEL_VERS := $(shell uname -r)
# KERNEL_DIR := /lib/modules/$(KERNEL_VERS)/build

$(TARGET_NAME)-objs = $(SRC)/$(TARGET_NAME:.c=.o)
obj-m := $(TARGET_NAME).o

default: 
	$(MAKE) -C $(KERNEL_SOURCE) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_SOURCE) M=$(PWD) clean
