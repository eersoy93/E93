/* DESCRIPTION: E93 C Library Ending Functions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with GPLv2 License. See LICENSE file for details.
 */

#include "ending.h"

#include "../cpu/halt.h"
#include "io.h"

void end(void)
{
    println((uint8_t *)"Halting the CPU...", ERROR_COLOR);
    halt();
}
