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
#include "../libc/function.h"
#include "../libc/init.h"
#include "../libc/io.h"
#include "../libc/memory.h"
#include "../libc/string.h"

void shell_main(uint32_t magic, struct multiboot_info * mb_info)
{
    cls();

    if (magic != MULTIBOOT_VALID)
    {
        println((uint8_t *)"Invalid magic number!", ERROR_COLOR);

        while(TRUE);
    }

    if (!(mb_info->flags & (1 << 2)))
    {
        println((uint8_t *)"Multiboot command line is not available!", ERROR_COLOR);

        while(TRUE);
    }

    uint8_t * boot_cmdline = (uint8_t *)(mb_info->cmdline);

    println((uint8_t *)"Executing the shell...", OUTPUT_COLOR);

    init();

    println((uint8_t *)"Welcome to E93!", OUTPUT_COLOR);
    println((uint8_t *)"Type HELP for help.", OUTPUT_COLOR);

    while(TRUE)
    {
        show_prompt();
        uint8_t * str = input();
        command_execute(str);
    }

    UNUSED(boot_cmdline);
}

void show_prompt(void)
{
    print((uint8_t *)">", PROMPT_COLOR);
}
