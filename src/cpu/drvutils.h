/* DESCRIPTION: E93 Driver Utility Definitions Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>
#include <stdint.h>

#define UNUSED(x) (void)(x)

typedef uint8_t boolean;

#define FALSE (boolean)0
#define TRUE (boolean)1

#define low16(address) (uint16_t)((address) & 0xFFFF)
#define high16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

void int_to_ascii(int32_t n, char str[]);
void reverse(char str[]);
uint16_t strlen(char str[]);
char * strchr(char str[], int c);
char * strtok(char str[], char delim[]);

void memory_copy(uint8_t * source, uint8_t * destination, uint32_t n_bytes);

#endif
