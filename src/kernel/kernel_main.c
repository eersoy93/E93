/* DESCRIPTION: E93 Kernel Main Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "kernel_main.h"

#include "command.h"
#include "../libc/boolean.h"
#include "../libc/ending.h"
#include "../libc/init.h"
#include "../libc/io.h"
#include "../libc/memory.h"
#include "../libc/string.h"
#include "../libc/video.h"

void kernel_main(void)
{
    cls();

    println("Executing the kernel...", OUTPUT_COLOR);

    if (get_video_type() == VIDEO_TYPE_COLOR)
    {
        println("Your video card is colored!", OUTPUT_COLOR);
    }
    else
    {
        end();
    }

    init();

    println("\nWelcome to E93!", OUTPUT_COLOR);
    println("Type HELP for help.", OUTPUT_COLOR);

    while(TRUE)
    {
        show_prompt();
        char * str = input();
        command_execute(str);
    }
}

void show_prompt(void)
{
    print(">", PROMPT_COLOR);
}
