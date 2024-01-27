/* DESCRIPTION: E93 C Library Memory Functions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "memory.h"

void memory_copy(uint8_t * source, uint8_t * destination, int n_bytes)
{
    int i = 0;
    for (i = 0; i < n_bytes; i++)
    {
        *(destination + i) = *(source + i);
    }
}

void memory_set(uint8_t * destination, uint8_t value, uint32_t length)
{
    uint8_t * tmp = (uint8_t *) destination;
    for( ; length != 0; length--)
    {
        *tmp = value;
        tmp++;
    }
}

uint32_t kmalloc(size_t size, int align, uint32_t * physical_address)
{
    if (align == 1 && (free_memory_address & 0xFFFFF000))
    {
        free_memory_address &= 0xFFFFF000;
        free_memory_address += 0x1000; 
    }

    if (physical_address)
    {
        *physical_address = free_memory_address;
    }

    uint32_t temp = free_memory_address;
    free_memory_address += size;
    return temp;
}
