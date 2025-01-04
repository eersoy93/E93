/* DESCRIPTION: E93 C Library Memory Functions Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef MEM_H
#define MEM_H

#include <stddef.h>
#include <stdint.h>

void memcpy(uint8_t * source, uint8_t * destination, uint32_t n_bytes);
void memset(uint8_t * destination, uint8_t value, uint32_t length);
int32_t memcmp(uint8_t * ptr_1, uint8_t * ptr_2, uint32_t n_bytes);

uint32_t free_memory_address = 0x10000;

uint32_t kmalloc(size_t size, int align, uint32_t * physical_address);

#endif
