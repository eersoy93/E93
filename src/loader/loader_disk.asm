; DESCRIPTION: E93 Loader Disk Module Assembly File
; AUTHOR: Erdem Ersoy (eersoy93)
; COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
; LICENSE: Licensed with MIT License. See LICENSE file for details.

disk_load:
    pusha

    push dx

    mov ah, 0x02
    mov al, dh
    mov cl, 0x02

    mov ch, 0x00
    mov dh, 0x00

    int 0x13
    jc disk_error

    pop dx
    cmp al, dh
    jne sectors_error

    popa
    ret

disk_error:
    mov bx, MSG_DISK_ERROR
    call print

    mov dh, ah
    call print_hex  ; For error codes, see INT 13 reference
    jmp disk_loop

sectors_error:
    mov bx, MSG_SECTORS_ERROR
    call print

disk_loop:
    jmp $

MSG_DISK_ERROR db "ERROR: Disk read error! Error code:", 0
MSG_SECTORS_ERROR db "ERROR: Incorrect number of sectors read!", 0
