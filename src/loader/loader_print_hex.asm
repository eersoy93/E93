; DESCRIPTION: E93 Loader Printing Hex Values Module Assembly File
; AUTHOR: Erdem Ersoy (eersoy93)
; COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
; LICENSE: Licensed with MIT License. See LICENSE file for details.

print_hex:
    pusha
    mov cx, 0

print_hex_loop:
    cmp cx, 4
    je print_hex_end

    mov ax, dx
    and ax, 0x000f
    add al, 0x30
    cmp al, 0x39
    jle print_hex_step2
    add al, 7

print_hex_step2:
    mov bx, HEX_OUTPUT + 5
    sub bx, cx
    mov [bx], al
    ror dx, 4

    add cx, 1
    jmp print_hex_loop

print_hex_end:
    mov bx, HEX_OUTPUT
    call print

    popa
    ret

HEX_OUTPUT db "0x0000", 0
