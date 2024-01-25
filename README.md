# E93

Erdem Ersoy's (eersoy93's) hobby operating system for old PCs.

## Building and Running

In [Pardus 23](https://www.pardus.org.tr/), clone this repository. After that, install GCC x86 cross compiler, NASM and QEMU:

`sudo apt install nasm qemu-system-x86 gcc-i686-linux-gnu xorriso`

After that, move to the src directory:

`cd src`

After that, build the OS:

`./build.sh`

After building, you can run:

`./run.sh`

## Studying TODOs

- [X] Finish studying [os-tutorial](https://github.com/cfenollosa/os-tutorial).
- [ ] Finish studying [The Little Book About OS Development](https://littleosbook.github.io/).
- [ ] Finish studying [OSTEP](https://pages.cs.wisc.edu/~remzi/OSTEP/).

## ROADMAP

### 0.1.0

- [ ] Rewrite the OS with [The Little Book About OS Development](https://littleosbook.github.io/).

## References

- [The Little Book About OS Development](https://littleosbook.github.io/)
- [GRUB 0.97 stage2_eltorito Binary File](https://github.com/pasandevin/carbonOS/blob/setup_booting_os/stage2_eltorito)

## Copyright and License

Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).

Licensed with MIT License. See LICENSE file for details.
