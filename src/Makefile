OBJECTS = loader.o kernel_main.o

CC = i686-linux-gnu-gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c

LD = i686-linux-gnu-ld
LDFLAGS = -T link.ld -melf_i386

AS = nasm
ASFLAGS = -f elf32

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o $@

E93.iso: kernel.elf
	mkdir -p iso/boot/grub
	cp stage2_eltorito iso/boot/grub/stage2_eltorito
	cp kernel.elf iso/boot/kernel.elf
	cp menu.lst iso/boot/grub/menu.lst
	xorriso -as mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o $@ iso/

run: E93.iso
	qemu-system-i386 -cdrom E93.iso

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o *.elf *.iso *.img *.bin iso/