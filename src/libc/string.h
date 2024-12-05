/* DESCRIPTION: E93 C Library String Functions Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef STRING_H
#define STRING_H

#include <stdint.h>

void int_to_ascii(int32_t n, char str[]);
void hex_to_ascii(uint32_t n, char str[]);

void reverse(char str[]);
uint16_t strlen(char str[]);

void backspace(char str[]);
void append(char str[], char n);
void strcat(char str_1[], char str_2[]);
uint32_t strcmp(char str_1[], char str_2[]);
void strcpy(char str_1[], char str_2[]);
char * strstr(const char * str, const char * substr);
int atoi(const char * str);

#endif
