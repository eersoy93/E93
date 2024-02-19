/* DESCRIPTION: E93 Ending Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "end.h"

#include "../drivers/screen.h"

void end(void)
{
    printk_color("Halting the CPU...\n", HALT_COLOR);
    asm volatile("cli");
    asm volatile("hlt");
}
