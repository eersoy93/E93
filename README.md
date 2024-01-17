# E93

Erdem Ersoy's (eersoy93's) hobby operating system for old PCs.

## Building and Running

In [Pardus 23](https://www.pardus.org.tr/), clone this repository. After that, install GCC x86 cross compiler, NASM and QEMU:

`sudo apt install nasm qemu-system-x86 gcc-i686-linux-gnu`

After that, move to the src directory:

`cd src`

After that, build the OS:

`make`

After building, you can run:

`make run`

## TODO

- [X] Finish studying [os-tutorial](https://github.com/cfenollosa/os-tutorial).
- [ ] Finish studying [OSTEP](https://pages.cs.wisc.edu/~remzi/OSTEP/).

## References

- [https://github.com/cfenollosa/os-tutorial](https://github.com/cfenollosa/os-tutorial)
- [https://wiki.osdev.org/PC_Speaker](https://wiki.osdev.org/PC_Speaker)
- [https://www.felixcloutier.com/x86/index.html](https://www.felixcloutier.com/x86/index.html)
- [https://www.fountainware.com/EXPL/vga_color_palettes.htm](https://www.fountainware.com/EXPL/vga_color_palettes.htm)
- [https://en.wikipedia.org/wiki/VGA_text_mode](https://en.wikipedia.org/wiki/VGA_text_mode)
- [https://www.rapidtables.com/code/text/ascii-table.html](https://www.rapidtables.com/code/text/ascii-table.html)
- [Pardus's Calculator :)](https://apps.pardus.org.tr/app/gnome-calculator)

## Copyright and License

Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).

Licensed with MIT License. See LICENSE file for details.
