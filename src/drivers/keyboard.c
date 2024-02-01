/* DESCRIPTION: E93 Keyboard Driver Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "keyboard.h"

#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel_main.h"
#include "../kernel/command.h"

static char key_buffer[256];

static void keyboard_callback(registers_struct_type * registers)
{
    uint8_t scancode = port_byte_in(0x60);

    if (kernel_mode == SHELL_MODE)
    {
        if (scancode > SCANCODE_MAX)
        {
            return;
        }
        else if (scancode == BACKSPACE)
        {
            backspace(key_buffer);
            printk_backspace();
        }
        else if (scancode == ENTER)
        {
            printk("\n");
            command_execute(key_buffer);
            key_buffer[0] = '\0';
        }
        else
        {
            char letter = scancode_ascii[(int)scancode];
            char str[2] = {letter, '\0'};
            append(key_buffer, letter);
            printk_color(str, COMMAND_COLOR);
        }
    }

    UNUSED(registers);
}

void init_keyboard(void)
{
    printk_color("Initializing the keyboard...\n", OUTPUT_COLOR);
    register_interrupt_handler(IRQ1, keyboard_callback); 
}
