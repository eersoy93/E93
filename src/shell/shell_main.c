/* DESCRIPTION: E93 Shell Main Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "shell_main.h"

#include "command.h"
#include "mb_header.h"
#include "mb_info.h"
#include "../libc/boolean.h"
#include "../libc/init.h"
#include "../libc/io.h"
#include "../libc/memory.h"
#include "../libc/string.h"

void shell_main(uint32_t magic, struct multiboot_info * mb_info)
{
    cls();

    uint32_t win_mode = 0;

    if (magic != MULTIBOOT_VALID)
    {
        println("Invalid magic number!", ERROR_COLOR);

        while(TRUE);
    }

    if (!(mb_info->flags & (1 << 2)))
    {
        println("Multiboot command line is not available!", ERROR_COLOR);

        while(TRUE);
    }

    char * cmdline = (char *)(mb_info->cmdline);
    char *mode_str = strstr(cmdline, "mode=");

    if (mode_str != NULL)
    {
        mode_str += 5;
        win_mode = atoi(mode_str);
    }
    else
    {
        println("Mode parameter not found in command line!", ERROR_COLOR);

        while(TRUE);
    }

    if (win_mode == 0)
    {
        println("Executing the shell...", OUTPUT_COLOR);

        init();

        println("Welcome to E93!", OUTPUT_COLOR);
        println("Type HELP for help.", OUTPUT_COLOR);

        while(TRUE)
        {
            show_prompt();
            char * str = input();
            command_execute(str);
        }
    }
    else
    {
        println("Windows mode has not implemented yet!", ERROR_COLOR);

        while(TRUE);
    }
}

void show_prompt(void)
{
    print(">", PROMPT_COLOR);
}
