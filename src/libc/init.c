/* DESCRIPTION: E93 C Library Shell Init Function Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "init.h"

#include "../cpu/isr.h"

void init(void)
{
    isr_install();
    irq_install();
}
