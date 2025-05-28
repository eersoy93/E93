/* DESCRIPTION: E93 Interrupt Service Routine Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with GPLv2 License. See LICENSE file for details.
 */

#include "isr.h"

#include "idt.h"
#include "ports.h"
#include "timer.h"
#include "drvutils.h"
#include "../drivers/ide.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"

isr_t interrupt_handlers[256];

void isr_install()
{
    printl_color((uint8_t *)"Initializing the ISRs...\n", OUTPUT_COLOR);

    set_idt_gate(0, (uint32_t) isr0);
    set_idt_gate(1, (uint32_t) isr1);
    set_idt_gate(2, (uint32_t) isr2);
    set_idt_gate(3, (uint32_t) isr3);
    set_idt_gate(4, (uint32_t) isr4);
    set_idt_gate(5, (uint32_t) isr5);
    set_idt_gate(6, (uint32_t) isr6);
    set_idt_gate(7, (uint32_t) isr7);
    set_idt_gate(8, (uint32_t) isr8);
    set_idt_gate(9, (uint32_t) isr9);
    set_idt_gate(10, (uint32_t) isr10);
    set_idt_gate(11, (uint32_t) isr11);
    set_idt_gate(12, (uint32_t) isr12);
    set_idt_gate(13, (uint32_t) isr13);
    set_idt_gate(14, (uint32_t) isr14);
    set_idt_gate(15, (uint32_t) isr15);
    set_idt_gate(16, (uint32_t) isr16);
    set_idt_gate(17, (uint32_t) isr17);
    set_idt_gate(18, (uint32_t) isr18);
    set_idt_gate(19, (uint32_t) isr19);
    set_idt_gate(20, (uint32_t) isr20);
    set_idt_gate(21, (uint32_t) isr21);
    set_idt_gate(22, (uint32_t) isr22);
    set_idt_gate(23, (uint32_t) isr23);
    set_idt_gate(24, (uint32_t) isr24);
    set_idt_gate(25, (uint32_t) isr25);
    set_idt_gate(26, (uint32_t) isr26);
    set_idt_gate(27, (uint32_t) isr27);
    set_idt_gate(28, (uint32_t) isr28);
    set_idt_gate(29, (uint32_t) isr29);
    set_idt_gate(30, (uint32_t) isr30);
    set_idt_gate(31, (uint32_t) isr31);

    // Remap the PIC
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0);

    // Install the IRQs
    set_idt_gate(32, (uint32_t) irq0);
    set_idt_gate(33, (uint32_t) irq1);
    set_idt_gate(34, (uint32_t) irq2);
    set_idt_gate(35, (uint32_t) irq3);
    set_idt_gate(36, (uint32_t) irq4);
    set_idt_gate(37, (uint32_t) irq5);
    set_idt_gate(38, (uint32_t) irq6);
    set_idt_gate(39, (uint32_t) irq7);
    set_idt_gate(40, (uint32_t) irq8);
    set_idt_gate(41, (uint32_t) irq9);
    set_idt_gate(42, (uint32_t) irq10);
    set_idt_gate(43, (uint32_t) irq11);
    set_idt_gate(44, (uint32_t) irq12);
    set_idt_gate(45, (uint32_t) irq13);
    set_idt_gate(46, (uint32_t) irq14);
    set_idt_gate(47, (uint32_t) irq15);

    set_idt();
}

uint8_t * isr_exception_messages[] =
{
    (uint8_t *)"Division By Zero",
    (uint8_t *)"Debug",
    (uint8_t *)"Non Maskable Interrupt",
    (uint8_t *)"Breakpoint",
    (uint8_t *)"Overflow",
    (uint8_t *)"Out of Bounds",
    (uint8_t *)"Invalid Opcode",
    (uint8_t *)"Coprocessor Not Available",
    (uint8_t *)"Double Fault",
    (uint8_t *)"Coprocessor Segment Overrun",
    (uint8_t *)"Invalid Task State Segment",
    (uint8_t *)"Segment Not Present",
    (uint8_t *)"Stack Segment Fault",
    (uint8_t *)"General Protection Fault",
    (uint8_t *)"Page Fault",
    (uint8_t *)"Reserved",
    (uint8_t *)"x87 Floating Point Fault",
    (uint8_t *)"Alignment Check",
    (uint8_t *)"Machine Check",
    (uint8_t *)"Reserved",
    (uint8_t *)"Reserved",
    (uint8_t *)"Reserved",
    (uint8_t *)"Reserved",
    (uint8_t *)"Reserved",
    (uint8_t *)"Reserved",
    (uint8_t *)"Reserved",
    (uint8_t *)"Reserved",
    (uint8_t *)"Reserved",
    (uint8_t *)"Reserved",
    (uint8_t *)"Reserved",
    (uint8_t *)"Reserved"
};

void isr_handler(registers_struct_type * registers)
{
    printl_color((uint8_t *)"Received interrupt: ", OUTPUT_COLOR);
    uint8_t interrupt_no_str[3];
    int_to_ascii(registers->interrupt_no, interrupt_no_str);
    printl_color(interrupt_no_str, OUTPUT_COLOR);
    printl_color((uint8_t *)"\n", OUTPUT_COLOR);

    printl_color(isr_exception_messages[registers->interrupt_no], OUTPUT_COLOR);
    printl_color((uint8_t *)"\n", OUTPUT_COLOR);
}

void register_interrupt_handler(uint8_t n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}

void irq_handler(registers_struct_type * registers)
{
    if (registers->interrupt_no >= 40) port_byte_out(0xA0, 0x20);
    port_byte_out(0x20, 0x20);

    if (interrupt_handlers[registers->interrupt_no] != 0)
    {
        isr_t handler = interrupt_handlers[registers->interrupt_no];
        handler(registers);
    }
}

void irq_install(void)
{
    printl_color((uint8_t *)"Initializing the IRQs...\n", OUTPUT_COLOR);
    asm volatile("sti");
    init_timer(50);
    init_keyboard();
    init_ide(0x1F0, 0x3F6, 0x170, 0x376, 0x000);
}
