/* DESCRIPTION: E93 C Library Memory Functions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2025 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "memory.h"

void * memcpy(const void * source, void * destination, uint32_t n_bytes)
{
    const uint8_t * src = (const uint8_t *)source;
    uint8_t * dest = (uint8_t *)destination;
    
    for (uint32_t i = 0; i < n_bytes; i++)
    {
        dest[i] = src[i];
    }
    
    return destination;
}

void * memset(void * destination, int value, uint32_t length)
{
    uint8_t * tmp = (uint8_t *)destination;
    for( ; length != 0; length--)
    {
        *tmp++ = (uint8_t)value;
    }
    
    return destination;
}

int32_t memcmp(uint8_t * ptr_1, uint8_t * ptr_2, uint32_t n_bytes)
{
    uint32_t i = 0;

    for (i = 0; i < n_bytes; i++)
    {
        if (*(ptr_1 + i) != *(ptr_2 + i))
        {
            return *(ptr_1 + i) - *(ptr_2 + i);
        }
    }

    return 0;
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
