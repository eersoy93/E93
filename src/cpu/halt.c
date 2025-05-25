/* DESCRIPTION: E93 CPU Halting Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with GPLv2 License. See LICENSE file for details.
 */

#include "halt.h"

void halt(void)
{
    asm volatile("cli");
    asm volatile("hlt");
}
