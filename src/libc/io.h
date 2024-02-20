/* DESCRIPTION: E93 C Library Input/Output Definitions Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef IO_H
#define IO_H

#include <stdint.h>

#include "../drivers/screen_colors.h"

void print_char(char character, char attribute);
void print(char * str, char attribute);
void println(char * str, char attribute);

char read_char(void);
char * input(void);

void cls(void);

#endif
