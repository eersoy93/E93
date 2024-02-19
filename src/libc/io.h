/* DESCRIPTION: E93 C Library Input/Output Functions Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef IO_H
#define IO_H

#include <stdint.h>

char key_buffer[256];

void keydown_handler(uint8_t scancode);
void keyup_handler(uint8_t scancode);

#endif
