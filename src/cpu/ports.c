/* DESCRIPTION: E93 Port Driver Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "ports.h"

// Read byte from port
uint8_t port_byte_in(uint16_t port)
{
    uint8_t result;
    asm("in %%dx, %%al": "=a" (result) : "d" (port));
    return result;
}

// Write byte to port
void port_byte_out(uint16_t port, uint8_t data)
{
    asm("out %%al, %%dx": : "a" (data), "d" (port));
}

// Read word from port
uint16_t port_word_in(uint16_t port)
{
    uint16_t result;
    asm("in %%dx, %%ax": "=a" (result) : "d" (port));
    return result;
}

// Write word to port
void port_word_out(uint16_t port, uint16_t data)
{
    asm("out %%ax, %%dx": : "a" (data), "d" (port));
}

// Read double word from port
uint32_t port_dword_in(uint16_t port)
{
    uint32_t result;
    asm("in %%dx, %%eax": "=a" (result) : "d" (port));
    return result;
}

// Write double word to port
void port_dword_out(uint16_t port, uint32_t data)
{
    asm("out %%eax, %%dx": : "a" (data), "d" (port));
}
