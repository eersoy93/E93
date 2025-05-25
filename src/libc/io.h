/* DESCRIPTION: E93 C Library Input/Output Definitions Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with GPLv2 License. See LICENSE file for details.
 */

#ifndef IO_H
#define IO_H

#include <stdint.h>

#include "../drivers/screen_colors.h"

void print_char(uint8_t character, uint8_t attribute);
void print(uint8_t * str, uint8_t attribute);
void println(uint8_t * str, uint8_t attribute);

uint8_t read_char(void);
uint8_t * input(void);

void cls(void);

uint8_t open_file(uint8_t filename[]);
uint32_t read_file(uint8_t file_descriptor, uint32_t offset, uint32_t size, uint8_t buffer[]);
uint8_t close_file(uint8_t file_descriptor);

#endif
