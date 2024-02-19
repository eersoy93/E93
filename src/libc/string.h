/* DESCRIPTION: E93 C Library String Functions Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef STRING_H
#define STRING_H

#include <stdint.h>

void int_to_ascii(int n, char str[]);
void hex_to_ascii(int n, char str[]);

void reverse(char str[]);
int strlen(char str[]);

void backspace(char str[]);
void append(char str[], char n);
int strcmp(char str_1[], char str_2[]);
void strcpy(char str_1[], char str_2[]);

#endif
