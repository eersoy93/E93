/* DESCRIPTION: E93 Kernel Main Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef KERNEL_H
#define KERNEL_H

#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/screen.h"
#include "../drivers/speaker.h"
#include "../libc/memory.h"
#include "../libc/string.h"

enum kernel_modes
{
    SHELL_MODE,
    COMMAND_MODE
};

enum kernel_modes kernel_mode = SHELL_MODE;

void printk_help(void);
void show_prompt(void);
void command_input(char * input);

#endif
