/* DESCRIPTION: E93 Kernel Main Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef KERNEL_MAIN_H
#define KERNEL_MAIN_H

enum kernel_modes
{
    SHELL_MODE,
    COMMAND_MODE
};

enum kernel_modes kernel_mode = SHELL_MODE;

void show_prompt(void);

#endif
