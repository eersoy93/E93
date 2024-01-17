; DESCRIPTION: E93 Loader Assembly File
; AUTHOR: Erdem Ersoy (eersoy93)
; COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
; LICENSE: Licensed with MIT License. See LICENSE file for details.

[org 0x7c00]

KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl
mov bp, 0x9000
mov sp, bp

mov bx, MSG_WELCOME
call print

mov bx, MSG_ENTER_REALMODE
call print

call load_kernel
call switch_to_protected_mode
jmp $

%include "loader/loader_print.asm"  ; E93 Loader Printing Module
%include "loader/loader_print_hex.asm"  ; E93 Loader Printing Hex Values Module
%include "loader/loader_disk.asm"  ; E93 Loader Disk Module
%include "loader/loader_gdt.asm"  ; E93 Loader Global Descriptor Table Module
%include "loader/loader_switch_to_protected_mode.asm"  ; E93 Loader Switch to Protected Mode Module
%include "loader/loader_print_protected_mode.asm"  ; E93 Loader Printing Module (for Protected Mode)

[bits 16]

load_kernel:
    mov bx, MSG_LOADING_KERNEL
    call print

    mov bx, KERNEL_OFFSET
    mov dh, 31
    mov dl, [BOOT_DRIVE]
    call disk_load
    ret

[bits 32]

begin_protected_mode:
    mov ebx, MSG_ENTER_PROTECTEDMODE
    call print_protected_mode
    call KERNEL_OFFSET
    jmp $

BOOT_DRIVE db 0
MSG_WELCOME db "Welcome to E93 Loader!", 0
MSG_ENTER_REALMODE db "Started in 16-bit real mode!", 0
MSG_LOADING_KERNEL db "Loading the kernel...", 0
MSG_ENTER_PROTECTEDMODE db "Started in 32-bit protected mode!", 0

times 510-($-$$) db 0
dw 0xaa55
