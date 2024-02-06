/* DESCRIPTION: E93 C Library Input/Output Functions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "io.h"

#include "../drivers/keyboard.h"
#include "function.h"
#include "string.h"
#include "../kernel/command.h"
#include "../kernel/kernel_main.h"

static char key_buffer[256];

void keydown_handler(uint8_t scancode)
{
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
}

void keyup_handler(uint8_t scancode)
{
    UNUSED(scancode);
}
