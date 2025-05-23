/* DESCRIPTION: E93 Shell Commands Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024-2025 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "command.h"

#include "../libc/ending.h"
#include "../libc/io.h"
#include "../libc/ide_libc.h"
#include "../libc/pci_libc.h"
#include "../libc/sound.h"
#include "../libc/string.h"
#include "../libc/vga_libc.h"
#include "shell_main.h"
#include "paging.h"

struct command commands[] = {
    {0, (uint8_t *)"BEEP", (uint8_t *)"Beeps from PC speaker.", &beep},
    {1, (uint8_t *)"CLS", (uint8_t *)"Clears the screen.", &cls},
    {2, (uint8_t *)"END", (uint8_t *)"Halts the CPU.", &end},
    {3, (uint8_t *)"HELP", (uint8_t *)"Shows this help message.", &commands_help},
    {4, (uint8_t *)"IDEDEVS", (uint8_t *)"Lists IDE devices.", &list_ide_devices},
    {5, (uint8_t *)"PAGE", (uint8_t *)"Requests a kernel allocation.", &allocate_page},
    {6, (uint8_t *)"PCIDEVS", (uint8_t *)"Lists PCI devices.", &list_pci_devices},
    {7, (uint8_t *)"VGADEMO", (uint8_t *)"Shows a VGA 12h mode demo.", &show_vga_demo}
};

void command_execute(uint8_t * input_command)
{
    for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); i++)
    {
        if (strcmp(commands[i].command_name, input_command) == 0)
        {
            commands[i].command_function();
            return;
        }
    }

    if (strcmp(input_command, (uint8_t *)"") != 0)
    {
        print((uint8_t *)"Unrecognized command: ", ERROR_COLOR);
        print(input_command, INPUT_COLOR);
        print((uint8_t *)"\n", INPUT_COLOR);
    }
}

void commands_help(void)
{
    for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); i++)
    {
        print(commands[i].command_name, INPUT_COLOR);
        print((uint8_t *)": ", INPUT_COLOR);
        print(commands[i].command_help, OUTPUT_COLOR);
        print((uint8_t *)"\n", OUTPUT_COLOR);
    }
}
