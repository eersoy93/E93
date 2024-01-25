#!/bin/sh

# DESCRIPTION: E93 Build Script
# AUTHOR: Erdem Ersoy (eersoy93)
# COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
# LICENSE: Licensed with MIT License. See LICENSE file for details.

nasm -f elf32 loader.asm -o loader.o
ld -T link.ld -melf_i386 loader.o -o kernel.elf

mkdir -p iso/boot/grub

cp ../bin/stage2_eltorito iso/boot/grub/
cp menu.lst iso/boot/grub/
cp kernel.elf iso/boot/

xorriso -as mkisofs -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -o iso/e93.iso iso/
