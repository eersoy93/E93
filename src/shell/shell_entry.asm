; DESCRIPTION: E93 Shell Entry Assembly File
; AUTHOR: Erdem Ersoy (eersoy93)
; COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
; LICENSE: Licensed with MIT License. See LICENSE file for details.

bits 32
global shell_entry

MAGIC_NUMBER       equ 0x1BADB002
FLAGS              equ 0x00000004
CHECKSUM           equ -(MAGIC_NUMBER + FLAGS)
SHELL_STACK_SIZE   equ 4096

extern shell_main

section .multiboot
align 4
    dd MAGIC_NUMBER
    dd FLAGS
    dd CHECKSUM

section .text
align 4
shell_entry:
    ; At this point:
    ; EAX contains the magic number
    ; EBX contains the pointer to multiboot_info

    ; Set up your own stack
    mov esp, shell_stack + SHELL_STACK_SIZE

    ; Push parameters onto the stack in reverse order (cdecl calling convention)
    push ebx              ; Push multiboot_info pointer
    push eax              ; Push magic number
    call shell_main

.loop:
    jmp .loop

section .bss
align 4
shell_stack:
    resb SHELL_STACK_SIZE
