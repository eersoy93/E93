/* DESCRIPTION: E93 Kernel Main Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "kernel_main.h"

#include "../cpu/end.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/screen.h"
#include "../drivers/speaker.h"
#include "command.h"
#include "../libc/boolean.h"
#include "../libc/io.h"
#include "../libc/memory.h"
#include "../libc/string.h"

void kernel_main(void)
{
    clear_screen();

    println("Executing the kernel...", OUTPUT_COLOR);

    if (is_video_colored() == TRUE)
    {
        println("Your video card is colored!", OUTPUT_COLOR);
    }
    else
    {
        end();
    }

    println("Initializing the ISR...", OUTPUT_COLOR);
    isr_install();

    println("Initializing the IRQ...", OUTPUT_COLOR);
    irq_install();

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
