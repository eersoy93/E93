/* DESCRIPTION: E93 Kernel Main Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */


#include "kernel.h"

void kernel_main(void)
{
    clear_screen();
    printk_color("Executing the kernel...\n", OUTPUT_COLOR);

    printk_color("Initializing the ISR...\n", OUTPUT_COLOR);
    isr_install();

    printk_color("Initializing the IRQ...\n", OUTPUT_COLOR);
    irq_install();

    printk_color("\nWelcome to E93!\n", OUTPUT_COLOR);
    printk_color("Type HELP for help.\n", OUTPUT_COLOR);
    show_prompt();
}

void printk_help(void)
{
    printk_color("Type BEEP to beep.\n", OUTPUT_COLOR);
    printk_color("Type CLS to clear the screen.\n", OUTPUT_COLOR);
    printk_color("Type END to halt the CPU.\n", OUTPUT_COLOR);
    printk_color("Type HELP for HELP.\n", OUTPUT_COLOR);
    printk_color("Type PAGE to request a kernel allocation.\n", OUTPUT_COLOR);
}

void show_prompt(void)
{
    printk_color(">", PROMPT_COLOR);
}

void user_input(char * input)
{
    if (strcmp(input, "BEEP") == 0)
    {
        beep();
        show_prompt();
    }
    else if (strcmp(input, "CLS") == 0)
    {
        clear_screen();
        show_prompt();
    }
    else if (strcmp(input, "END") == 0)
    {
        printk_color("Halting the CPU...\n", HALT_COLOR);
        asm volatile("hlt");
    }
    else if (strcmp(input, "HELP") == 0)
    {
        printk_help();
        show_prompt();
    }
    else if (strcmp(input, "PAGE") == 0)
    {
        uint32_t physical_address = 0;
        uint32_t page = kmalloc(1000, 1, &physical_address);

        char page_str[16] = "";
        hex_to_ascii(page, page_str);

        char physical_address_str[16] = "";
        hex_to_ascii(physical_address, physical_address_str);

        printk_color("Memory has been allocated. ", OUTPUT_COLOR);
        printk_color("Page: ", OUTPUT_COLOR);
        printk_color(page_str, VARIABLE_COLOR);
        printk_color("\nPhysical Address: ", OUTPUT_COLOR);
        printk_color(physical_address_str, VARIABLE_COLOR);
        printk_color("\n", OUTPUT_COLOR);
        show_prompt();
    }
    else if (strcmp(input, "") == 0)
    {
        show_prompt();
    }
    else
    {
        printk_color("Unrecognized command: ", ERROR_COLOR);
        printk_color(input, COMMAND_COLOR);
        printk_color("\n", OUTPUT_COLOR);
        show_prompt();
    }
}
