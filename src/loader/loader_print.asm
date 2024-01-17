; DESCRIPTION: E93 Loader Printing Module Assembly File
; AUTHOR: Erdem Ersoy (eersoy93)
; COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
; LICENSE: Licensed with MIT License. See LICENSE file for details.

print:
    pusha

print_loop:
    mov al, [bx]
    cmp al, 0
    je print_done

    ; Print shift out character for printing
    mov ah, 0x0e
    int 0x10

    add bx, 1
    jmp print_loop

print_done:
    ; Print newline characters (CR + LF)
    mov al, 0x0d
    int 0x10
    mov al, 0x0a
    int 0x10

    popa
    ret
