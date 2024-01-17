# DESCRIPTION: E93 Makefile
# AUTHOR: Erdem Ersoy (eersoy93)
# COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
# LICENSE: Licensed with MIT License. See LICENSE file for details.

C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c)
C_HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h)

OBJ = ${C_SOURCES:.c=.o cpu/interrupts.o}

CC = /usr/bin/i686-linux-gnu-gcc
CFLAGS = -g -m32 -ffreestanding -fno-PIC -fno-stack-protector -nostartfiles -nodefaultlibs \
         -Wall -Wextra -Werror

e93-os.img: loader/loader.bin kernel.bin
	cat $^ > e93-os.bin
	dd if=/dev/zero bs=512 count=2880 >> $@
	dd if=e93-os.bin of=$@ conv=notrunc

kernel.bin: loader/kernel_entry.o ${OBJ}
	i686-linux-gnu-ld -no-pie -o $@ -Ttext 0x1000 $^ --oformat binary --allow-multiple-definition

run: e93-os.img
	qemu-system-i386 -fda $< -audiodev alsa,id=default -machine pcspk-audiodev=default

%.o: %.c ${C_HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -f *.bin *.img *.o loader/*.bin kernel/*.o loader/*.o drivers/*.o cpu/*.o libc/*.o
