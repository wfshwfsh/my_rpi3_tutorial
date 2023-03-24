CROSS_COMPILE ?= aarch64-linux-gnu-

LINK_SCRIPT = linker.lds
CCFLAGS = -c -g
#CCFLAGS = -c

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
CFLAGS = -I. -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles


QEMU_DIR="`pwd`/../qemu_install/bin/"
QEMU_CMD=$(QEMU_DIR)"qemu-system-aarch64"


all: kernel8.img

start.o: start.s
	$(CROSS_COMPILE)gcc $(CCFLAGS) start.s -o start.o $(CFLAGS)

%.o: %.c
	$(CROSS_COMPILE)gcc $(CCFLAGS) $< -o $@ $(CFLAGS)

kernel8.img: start.o $(OBJS)
	$(CROSS_COMPILE)ld -nostdlib -nostartfiles start.o $(OBJS) -T $(LINK_SCRIPT) -o kernel8.elf
	$(CROSS_COMPILE)objcopy -O binary kernel8.elf kernel8.img
	${CROSS_COMPILE}objdump -D -m arm kernel8.elf > kernel8.dis

clean:
	rm -f *.img *.elf *.dis *.o

run:
	$(QEMU_CMD) -M raspi3b -kernel kernel8.img -display none -serial null -serial stdio

gdb:
	$(QEMU_CMD) -M raspi3b -kernel kernel8.img -display none -serial null -serial stdio -S -s
