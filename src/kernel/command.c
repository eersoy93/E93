/* DESCRIPTION: E93 Kernel Shell Commands Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "command.h"

#include "../cpu/end.h"
#include "../drivers/screen.h"
#include "../drivers/speaker.h"
#include "../libc/string.h"
#include "kernel_main.h"
#include "paging.h"

struct command commands[] = {
    {0, "BEEP", "Beeps from PC speaker.", &beep},
    {1, "CLS", "Clears the screen.", &clear_screen},
    {2, "END", "Halts the CPU.", &end},
    {3, "HELP", "Shows this help message.", &commands_help},
    {4, "PAGE", "Requests a kernel allocation.", &allocate_page}
};

void command_execute(char * input_command)
{
    for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); i++)
    {
        if (strcmp(commands[i].command_name, input_command) == 0)
        {
            disable_cursor();
            kernel_mode = COMMAND_MODE;
            commands[i].command_function();
            kernel_mode = SHELL_MODE;
            show_prompt();
            return;
        }
    }

    if (strcmp(input_command, "") == 0)
    {
        show_prompt();
    }
    else
    {
        printk_color("Unrecognized command: ", ERROR_COLOR);
        printk_color(input_command, COMMAND_COLOR);
        printk_color("\n", OUTPUT_COLOR);
        show_prompt();
    }
}

void commands_help(void)
{
    for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); i++)
    {
        printk_color(commands[i].command_name, COMMAND_COLOR);
        printk_color(": ", COMMAND_COLOR);
        printk_color(commands[i].command_help, OUTPUT_COLOR);
        printk_color("\n", OUTPUT_COLOR);
    }
}
