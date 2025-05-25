/* DESCRIPTION: E93 C Library String Functions Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2025 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with GPLv2 License. See LICENSE file for details.
 */

#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

void int_to_ascii(int32_t n, uint8_t str[]);
void hex_to_ascii(uint32_t n, uint8_t str[]);

void reverse(uint8_t str[]);
uint16_t strlen(uint8_t str[]);

void backspace(uint8_t str[]);
void append(uint8_t str[], uint8_t n);
void strcat(uint8_t str_1[], uint8_t str_2[]);
int32_t strcmp(uint8_t str_1[], uint8_t str_2[]);
void strcpy(uint8_t str_1[], uint8_t str_2[]);
int32_t strncmp(uint8_t str_1[], uint8_t str_2[], uint32_t n);
uint8_t * strstr(uint8_t str[], uint8_t substr[]);
uint8_t * strchr(uint8_t str[], int32_t c);
uint8_t * strrchr(uint8_t str[], int32_t c);
uint8_t * strpbrk(uint8_t str[], uint8_t accept[]);
uint8_t * strtok(uint8_t str[], uint8_t delim[]);
int32_t atoi(uint8_t str[]);

#endif
