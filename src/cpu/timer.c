/* DESCRIPTION: E93 CPU Timer Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "timer.h"

#include "drvutils.h"
#include "isr.h"
#include "ports.h"
#include "registers.h"
#include "../drivers/screen.h"

volatile uint32_t tick = 0;

static void timer_callback(registers_struct_type * registers)
{
    tick++;
    UNUSED(registers);
}

void set_PIT_2(uint32_t frequency)
{
    uint32_t divisor = 1193180 / frequency;  // Hardware clock frequency is 1193180 Hz.
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    port_byte_out(0x43, 0xB6);
    port_byte_out(0x42, low);
    port_byte_out(0x42, high);
}

void init_timer(uint32_t frequency)
{
    printl_color("Initializing the CPU timer...\n", OUTPUT_COLOR);

    uint32_t divisor = 1193180 / frequency;  // Hardware clock frequency is 1193180 Hz.
    uint8_t low = (uint8_t)(divisor & 0xFF);
    uint8_t high = (uint8_t)((divisor >> 8) & 0xFF);

    port_byte_out(0x43, 0x36);
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);

    register_interrupt_handler(IRQ0, timer_callback);
}

void wait_timer(uint32_t ticks)
{
    uint32_t ticks_end = tick + ticks;

    while (tick < ticks_end)
    {
        asm volatile("nop");
    }
}
