/* DESCRIPTION: E93 Keyboard Driver Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "keyboard.h"

#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/function.h"
#include "../libc/io.h"

static void keyboard_callback(registers_struct_type * registers)
{
    volatile uint8_t scancode = port_byte_in(0x60);

    if ((scancode & 0x80) == 0x80)
    {
        scancode &= 0x7F;
        keyup_handler(scancode);
    }
    else
    {
        keydown_handler(scancode);
    }

    UNUSED(registers);
}

void init_keyboard(void)
{
    printk_color("Initializing the keyboard...\n", OUTPUT_COLOR);
    register_interrupt_handler(IRQ1, keyboard_callback); 
}
