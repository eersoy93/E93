/* DESCRIPTION: E93 Interrupt Descriptor Table Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef IDT_H
#define IDT_H

#include <stdint.h>

// Segment selectors
#define KERNEL_CS (uint16_t)0x08

// Interrupt gate handler struct
typedef struct
{
    uint16_t offset_handler_function_address_low;
    uint16_t kernel_segment_selector;
    uint8_t always_zero;

    /* 7:   Interrupt is present
     * 6-5: CPU privilege level of the caller
     * 4:   Zero for interrupt gates
     * 3-0: 32-bit interrupt gate */
    uint8_t flags;
    uint16_t offset_handler_function_address_high;
} __attribute__((packed)) idt_gate_type;

// Interrupt handlers array pointer
typedef struct
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_type;

#define IDT_ENTRIES_COUNT 256
idt_gate_type idt[IDT_ENTRIES_COUNT];
idt_register_type idt_register;

// IDT Functions
void set_idt_gate(int n, uint32_t handler);
void set_idt(void);

#endif
