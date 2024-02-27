/* DESCRIPTION: E93 Keyboard Driver Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "keyboard.h"

#include "../cpu/drvutils.h"
#include "../cpu/isr.h"
#include "../cpu/ports.h"
#include "screen.h"

void keydown_handler(uint8_t scancode)
{
    current_scancode = scancode;
    current_mode = KEYDOWN;
}

void keyup_handler(uint8_t scancode)
{
    current_scancode = scancode;
    current_mode = KEYUP;
}

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
    printl_color("Initializing the keyboard...\n", OUTPUT_COLOR);
    current_mode = KEYUP;
    current_scancode = 0;
    register_interrupt_handler(IRQ1, keyboard_callback); 
}
