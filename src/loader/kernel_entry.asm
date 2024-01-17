; DESCRIPTION: E93 Kernel Entry Point Assembly File
; AUTHOR: Erdem Ersoy (eersoy93)
; COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
; LICENSE: Licensed with MIT License. See LICENSE file for details.

[bits 32]

[extern kernel_main]
call kernel_main
jmp $
