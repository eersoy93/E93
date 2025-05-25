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

void int_to_ascii(int32_t n, uint8_t str[]);
void reverse(uint8_t str[]);
uint16_t strlen(uint8_t str[]);
uint8_t * strchr(uint8_t str[], int c);
uint8_t * strtok(uint8_t str[], uint8_t delim[]);
int32_t strcmp(uint8_t str1[], uint8_t str2[]);

int8_t memcmp(uint8_t * source, uint8_t * destination, uint32_t n_bytes);
void memcpy(uint8_t * source, uint8_t * destination, uint32_t n_bytes);

#endif
