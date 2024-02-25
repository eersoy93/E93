SOURCES_ASM = $(wildcard cpu/*.asm shell/*.asm)
SOURCES_C = $(wildcard cpu/*.c drivers/*.c shell/*.c libc/*.c)
OBJECTS = ${SOURCES_ASM:.asm=.o} ${SOURCES_C:.c=.o}

CC = i686-linux-gnu-gcc
CFLAGS = -m32 -nostdlib -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c

LD = i686-linux-gnu-ld
LDFLAGS = -T link.ld -melf_i386 --allow-multiple-definition -z noexecstack

AS = nasm
ASFLAGS = -f elf32

all: E93.elf

E93.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o $@

E93.iso: E93.elf
	mkdir -p iso/boot/grub
	cp $< iso/boot/E93.elf
	cp menu.lst iso/boot/grub/menu.lst
	cp ../bin/stage2_eltorito iso/boot/grub/stage2_eltorito
	xorriso -as mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o $@ iso/

iso: E93.iso

run: iso
	qemu-system-i386 -cdrom E93.iso -audiodev alsa,id=default -machine pcspk-audiodev=default

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf ${OBJECTS} *.elf *.iso *.img *.bin iso/ kernel/*.elf
