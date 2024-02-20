/* DESCRIPTION: E93 Shell Commands Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "command.h"

#include "../libc/ending.h"
#include "../libc/io.h"
#include "../libc/sound.h"
#include "../libc/string.h"
#include "shell_main.h"
#include "paging.h"

struct command commands[] = {
    {0, "BEEP", "Beeps from PC speaker.", &beep},
    {1, "CLS", "Clears the screen.", &cls},
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
            commands[i].command_function();
            return;
        }
    }

    if (strcmp(input_command, "") != 0)
    {
        print("Unrecognized command: ", ERROR_COLOR);
        print(input_command, INPUT_COLOR);
        print("\n", INPUT_COLOR);
    }
}

void commands_help(void)
{
    for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); i++)
    {
        print(commands[i].command_name, INPUT_COLOR);
        print(": ", INPUT_COLOR);
        print(commands[i].command_help, OUTPUT_COLOR);
        print("\n", OUTPUT_COLOR);
    }
}
