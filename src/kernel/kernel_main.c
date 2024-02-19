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
#include "../libc/boolean.h"
#include "../libc/memory.h"
#include "../libc/string.h"

void kernel_main(void)
{
    clear_screen();

    printk_color("Executing the kernel...\n", OUTPUT_COLOR);

    if (is_video_colored() == TRUE)
    {
        printk_color("Your video card is colored!\n", OUTPUT_COLOR);
    }
    else
    {
        end();
    }

    printk_color("Initializing the ISR...\n", OUTPUT_COLOR);
    isr_install();

    printk_color("Initializing the IRQ...\n", OUTPUT_COLOR);
    irq_install();

    printk_color("\nWelcome to E93!\n", OUTPUT_COLOR);
    printk_color("Type HELP for help.\n", OUTPUT_COLOR);

    show_prompt();
}

void show_prompt(void)
{
    printk_color(">", PROMPT_COLOR);
    enable_cursor(0, 15);
}
