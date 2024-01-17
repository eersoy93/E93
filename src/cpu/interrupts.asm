; DESCRIPTION: E93 Interrupts Assembly File
; AUTHOR: Erdem Ersoy (eersoy93)
; COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
; LICENSE: Licensed with MIT License. See LICENSE file for details.

[extern isr_handler]
[extern irq_handler]

; Common ISR code
isr_common_stub:
    ; Save CPU state
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp
    cld

    ; Call C ISR handler
    call isr_handler

    ; Restore CPU state
    pop eax
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8
    iret

; Common IRQ code
irq_common_stub:
    ; Save CPU state
    pusha 
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    push esp
    cld

    ; Call C IRQ Handler
    call irq_handler

    ; Restore CPU state
    pop ebx
    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    popa
    add esp, 8
    iret

; Make ISRs global
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

; Make IRQs global
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; Division By Zero Exception
isr0:
    push byte 0
    push byte 0
    jmp isr_common_stub

; Debug Exception
isr1:
    push byte 0
    push byte 1
    jmp isr_common_stub

; Non Maskable Interrupt Exception
isr2:
    push byte 0
    push byte 2
    jmp isr_common_stub

; Breakpoint Exception
isr3:
    push byte 0
    push byte 3
    jmp isr_common_stub

; Overflow Exception
isr4:
    push byte 0
    push byte 4
    jmp isr_common_stub

; Out of Bounds Exception
isr5:
    push byte 0
    push byte 5
    jmp isr_common_stub

; Invalid Opcode Exception
isr6:
    push byte 0
    push byte 6
    jmp isr_common_stub

; Coprocessor Not Available Exception
isr7:
    push byte 0
    push byte 7
    jmp isr_common_stub

; Double Fault Exception (with error code)
isr8:
    push byte 8
    jmp isr_common_stub

; Coprocessor Segment Overrun Exception
isr9:
    push byte 0
    push byte 9
    jmp isr_common_stub

; Invalid Task State Segment Exception (with error code)
isr10:
    push byte 10
    jmp isr_common_stub

; Segment Not Present Exception (with error code)
isr11:
    push byte 11
    jmp isr_common_stub

; Stack Segment Fault Exception (with error code)
isr12:
    push byte 12
    jmp isr_common_stub

; General Protection Fault Exception (with error code)
isr13:
    push byte 13
    jmp isr_common_stub

; Page Fault Exception (with error code)
isr14:
    push byte 14
    jmp isr_common_stub

; Reserved Exception
isr15:
    push byte 0
    push byte 15
    jmp isr_common_stub

; x87 Floating Point Fault Exception
isr16:
    push byte 0
    push byte 16
    jmp isr_common_stub

; Alignment Check Exception
isr17:
    push byte 0
    push byte 17
    jmp isr_common_stub

; Machine Check Exception
isr18:
    push byte 0
    push byte 18
    jmp isr_common_stub

; Reserved Exception
isr19:
    push byte 0
    push byte 19
    jmp isr_common_stub

; Reserved Exception
isr20:
    push byte 0
    push byte 20
    jmp isr_common_stub

; Reserved Exception
isr21:
    push byte 0
    push byte 21
    jmp isr_common_stub

; Reserved Exception
isr22:
    push byte 0
    push byte 22
    jmp isr_common_stub

; Reserved Exception
isr23:
    push byte 0
    push byte 23
    jmp isr_common_stub

; Reserved Exception
isr24:
    push byte 0
    push byte 24
    jmp isr_common_stub

; Reserved Exception
isr25:
    push byte 0
    push byte 25
    jmp isr_common_stub

; Reserved Exception
isr26:
    push byte 0
    push byte 26
    jmp isr_common_stub

; Reserved Exception
isr27:
    push byte 0
    push byte 27
    jmp isr_common_stub

; Reserved Exception
isr28:
    push byte 0
    push byte 28
    jmp isr_common_stub

; Reserved Exception
isr29:
    push byte 0
    push byte 29
    jmp isr_common_stub

; Reserved Exception
isr30:
    push byte 0
    push byte 30
    jmp isr_common_stub

; Reserved Exception
isr31:
    push byte 0
    push byte 31
    jmp isr_common_stub

; IRQ handlers
irq0:
    push byte 0
    push byte 32
    jmp irq_common_stub

irq1:
    push byte 1
    push byte 33
    jmp irq_common_stub

irq2:
    push byte 2
    push byte 34
    jmp irq_common_stub

irq3:
    push byte 3
    push byte 35
    jmp irq_common_stub

irq4:
    push byte 4
    push byte 36
    jmp irq_common_stub

irq5:
    push byte 5
    push byte 37
    jmp irq_common_stub

irq6:
    push byte 6
    push byte 38
    jmp irq_common_stub

irq7:
    push byte 7
    push byte 39
    jmp irq_common_stub

irq8:
    push byte 8
    push byte 40
    jmp irq_common_stub

irq9:
    push byte 9
    push byte 41
    jmp irq_common_stub

irq10:
    push byte 10
    push byte 42
    jmp irq_common_stub

irq11:
    push byte 11
    push byte 43
    jmp irq_common_stub

irq12:
    push byte 12
    push byte 44
    jmp irq_common_stub

irq13:
    push byte 13
    push byte 45
    jmp irq_common_stub

irq14:
    push byte 14
    push byte 46
    jmp irq_common_stub

irq15:
    push byte 15
    push byte 47
    jmp irq_common_stub
