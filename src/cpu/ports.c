/* DESCRIPTION: E93 Port Driver Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "ports.h"

// Read byte from port
unsigned char port_byte_in(unsigned short port)
{
    unsigned char result;
    asm("in %%dx, %%al": "=a" (result) : "d" (port));
    return result;
}

// Write byte to port
void port_byte_out(unsigned short port, unsigned char data)
{
    asm("out %%al, %%dx": : "a" (data), "d" (port));
}

// Read word from port
unsigned short port_word_in(unsigned short port)
{
    unsigned char result;
    asm("in %%dx, %%ax": "=a" (result) : "d" (port));
    return result;
}

// Write word to port
void port_word_out(unsigned short port, unsigned short data)
{
    asm("out %%ax, %%dx": : "a" (data), "d" (port));
}

// Read double word from port
unsigned int port_dword_in(unsigned short port)
{
    unsigned int result;
    asm("in %%dx, %%eax": "=a" (result) : "d" (port));
    return result;
}

// Write double word to port
void port_dword_out(unsigned short port, unsigned int data)
{
    asm("out %%eax, %%dx": : "a" (data), "d" (port));
}
