# E93

Erdem Ersoy's (eersoy93's) hobby operating system for old PCs.

## Building and Running

In [Pardus 23](https://www.pardus.org.tr/) or Debian 12 or Linux Mint 21.3, clone this repository. After that, install GCC x86 cross compiler, NASM and QEMU:

`sudo apt install build-essential nasm qemu-system-x86 gcc-i686-linux-gnu xorriso`

After that, move to the src directory:

`cd src`

After that, build the OS:

`make iso`

After building, you can run:

`make run`

## Studying TODOs

- [X] Finish studying [os-tutorial](https://github.com/cfenollosa/os-tutorial). (0.0.x)
- [X] Finish studying [The Little Book About OS Development](https://littleosbook.github.io/). (0.1.x)

## ROADMAP

### 0.2.x

- [ ] Add/Improve device drivers and implementations to the C library as much as possible.

### 0.2.0

- [X] Restructure the OS.

### 0.1.x

- [X] Add/Improve device drivers and implementations to the C library as much as possible.

### 0.1.0

- [X] Rewrite the bootloader with [The Little Book About OS Development](https://littleosbook.github.io/).

## References

- [The Little Book About OS Development](https://littleosbook.github.io/)
- [GRUB 0.97 stage2_eltorito Binary File](https://github.com/pasandevin/carbonOS/blob/setup_booting_os/stage2_eltorito)
- [cfenollosa's OS Tutorial](https://github.com/cfenollosa/os-tutorial)
- [OSDev Wiki PC Speaker Page](https://wiki.osdev.org/PC_Speaker)
- [OSDev Wiki Color/Monochrome Monitors Page](https://wiki.osdev.org/Detecting_Colour_and_Monochrome_Monitors)
- [OSDev Wiki Text Mode Cursor Page](https://wiki.osdev.org/Text_Mode_Cursor)
- [OSDev Wiki PCI Page](https://wiki.osdev.org/PCI)
- [OSDev Wiki PCI IDE Controller Page](https://wiki.osdev.org/PCI_IDE_Controller)
- [OSDev Wiki Inline Assembly/Examples](https://wiki.osdev.org/Inline_Assembly/Examples)
- [OSDev Forum of Keydown and Keyup Events](https://forum.osdev.org/viewtopic.php?t=9761)
- [x86 and amd64 Instruction Reference](https://www.felixcloutier.com/x86/index.html)
- [VGA Color Palettes](https://www.fountainware.com/EXPL/vga_color_palettes.htm)
- [VGA Text Mode (Wikipedia)](https://en.wikipedia.org/wiki/VGA_text_mode)
- [Device Hunt](https://devicehunt.com/)
- [The PCI ID Repository](https://pci-ids.ucw.cz/)
- [RapidTables ASCII Table](https://www.rapidtables.com/code/text/ascii-table.html)
- [Pardus's Calculator :)](https://apps.pardus.org.tr/app/gnome-calculator)

**NOTE:** Also I have being used GitHub Copilot and ChatGPT but I don't directly use code completions.

## Copyright and License

Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).

Licensed with MIT License. See LICENSE file for details.

**NOTE:** bin/stage2_eltorito, shell/mb_header.h and shell/mb_info.h is GNU GPLv2 licensed because GNU GRUB 0.97 is licensed with GNU GPLv2.

**NOTE 2:** The copyright of GNU GRUB 0.97 (from https://www.gnu.org/software/grub/):

    Copyright © 2010-2018 Free Software Foundation, Inc.

    Copyright © 1999,2000,2001,2002,2003,2004,2005,2006 Yoshinori K. Okuji
