/* DESCRIPTION: E93 C Library String Functions Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

void int_to_ascii(int32_t n, char str[]);
void hex_to_ascii(uint32_t n, char str[]);

void reverse(char str[]);
uint16_t strlen(char str[]);

void backspace(char str[]);
void append(char str[], char n);
void strcat(char str_1[], char str_2[]);
int32_t strcmp(char str_1[], char str_2[]);
void strcpy(char str_1[], char str_2[]);
int32_t strncmp(char str_1[], char str_2[], uint32_t n);
char * strstr(char str[], char substr[]);
char * strchr(char str[], int c);
char * strrchr(char str[], int c);
char * strpbrk(char str[], char accept[]);
char * strtok(char str[], char delim[]);
int atoi(char str[]);

#endif
