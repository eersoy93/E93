/* DESCRIPTION: E93 Interrupt Descriptor Table Code File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "idt.h"

#include "../cpu/drvutils.h"

void set_idt_gate(int n, uint32_t handler)
{
    idt[n].offset_handler_function_address_low = low16(handler);
    idt[n].kernel_segment_selector = KERNEL_CS;
    idt[n].always_zero = (uint8_t) 0;
    idt[n].flags = 0x8E; // 1000 1110
    idt[n].offset_handler_function_address_high = high16(handler);
}

void set_idt(void)
{
    idt_register.base = (uint32_t) &idt;
    idt_register.limit = sizeof(idt_gate_type) * IDT_ENTRIES_COUNT - 1;
    asm volatile("lidtl (%0)" : : "r" (&idt_register));
}
