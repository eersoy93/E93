; DESCRIPTION: E93 Shell Entry Assembly File
; AUTHOR: Erdem Ersoy (eersoy93)
; COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
; LICENSE: Licensed with MIT License. See LICENSE file for details.

global shell_entry

MAGIC_NUMBER equ 0x1BADB002
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER
SHELL_STACK_SIZE equ 4096

extern shell_main

section .bss
align 4

shell_stack:
    resb SHELL_STACK_SIZE

section .text
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

shell_entry:
    mov esp, shell_stack + SHELL_STACK_SIZE
    call shell_main

.loop:
    jmp .loop
