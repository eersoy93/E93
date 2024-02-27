/* DESCRIPTION: E93 Driver Utility Definitions Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#define UNUSED(x) (void)(x)

#define low16(address) (uint16_t)((address) & 0xFFFF)
#define high16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

void int_to_ascii(int n, char str[]);
void reverse(char str[]);
int strlen(char str[]);

#endif
