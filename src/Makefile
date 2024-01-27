SOURCES_ASM = $(wildcard kernel/*.asm)
SOURCES_C = $(wildcard kernel/*.c)
OBJECTS = ${SOURCES_ASM:.asm=.o} ${SOURCES_C:.c=.o}

CC = i686-linux-gnu-gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c

LD = i686-linux-gnu-ld
LDFLAGS = -T kernel/link.ld -melf_i386

AS = nasm
ASFLAGS = -f elf32

all: kernel/kernel.elf

kernel/kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o $@

E93.iso: kernel/kernel.elf
	mkdir -p iso/boot/grub
	cp $< iso/boot/kernel.elf
	cp menu.lst iso/boot/grub/menu.lst
	cp ../bin/stage2_eltorito iso/boot/grub/stage2_eltorito
	xorriso -as mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o $@ iso/

iso: E93.iso

run: iso
	qemu-system-i386 -cdrom E93.iso

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o *.elf *.iso *.img *.bin iso/ kernel/*.o kernel/*.elf kernel/*.img kernel/*.iso kernel/*.bin
