ROOTDIR:= $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))
CC_PREFIX?= sh-elf

AS= $(CC_PREFIX)-as
CC= $(CC_PREFIX)-gcc
LD= $(CC_PREFIX)-gcc
CXX= $(CC_PREFIX)-g++
NM= $(CC_PREFIX)-nm
OB= $(CC_PREFIX)-objcopy
OD= $(CC_PREFIX)-objdump

AFLAGS= --fatal-warnings --isa=sh2 --big --reduce-memory-overheads \
	-I$(ROOTDIR)/common
CFLAGS= -W -Wall -Wextra -Werror -Wunused-parameter -Wstrict-aliasing -Wno-main \
	-m2 -mb -O2 -fomit-frame-pointer \
	-ffast-math -fstrict-aliasing \
	-I../../libtga \
	-I../../libfixmath \
	-I../../libyaul \
	-I../../libyaul/common \
	-I../../libyaul/common/gdb \
	-I../../libyaul/cons \
	-I../../libyaul/kernel \
	-I../../libyaul/kernel/vfs \
	-I../../libyaul/scu \
	-I../../libyaul/scu/bus/a/cs0/arp \
	-I../../libyaul/scu/bus/a/cs0/dram-cartridge \
	-I../../libyaul/scu/bus/a/cs0/usb-cartridge \
	-I../../libyaul/scu/bus/a/cs2/cd-block \
	-I../../libyaul/scu/bus/b/scsp \
	-I../../libyaul/scu/bus/b/vdp1 \
	-I../../libyaul/scu/bus/b/vdp2 \
	-I../../libyaul/scu/bus/cpu \
	-I../../libyaul/scu/bus/cpu/smpc
LDFLAGS= -Wl,-Map,${PROJECT}.map \
	-L$(ROOTDIR)/../build/libfixmath \
	-L$(ROOTDIR)/../build/libtga \
	-L$(ROOTDIR)/../build/libyaul \
	-Wl,--start-group -lfixmath -ltga -lyaul -lc -lgcc \
	-Wl,--end-group \
	-Wl,--gc-sections \
	-nostartfiles -T $(ROOTDIR)/common/ldscripts/sh-elf.x
CXXFLAGS= $(CFLAGS) -ffreestanding -fno-exceptions -fno-rtti
LXXFLAGS= -Wl,-Map,${PROJECT}.map \
	-L$(ROOTDIR)/../build/libtga \
	-L$(ROOTDIR)/../build/libyaul \
	-Wl,--start-group -lfixmath -ltga -lyaul -lstdc++ -lc -lgcc \
	-Wl,--end-group \
	-Wl,--gc-sections \
	-nostartfiles -T $(ROOTDIR)/common/ldscripts/sh-elf.x \
	-ffreestanding -fno-exceptions -fno-rtti

# All programs must link this as the first object (crt0.o)
OBJECTS:= $(ROOTDIR)/common/crt0.o \
	$(ROOTDIR)/common/crt0-init.o

SUFFIXES:= .c .S .o .bin .elf .romdisk .romdisk.o

.PHONY: clean example romdisk image

.SUFFIXES:
.SUFFIXES: $(SUFFIXES)

PROJECT?=unknown