/* DESCRIPTION: E93 Screen Driver Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef SCREEN_H
#define SCREEN_H

#include "../cpu/ports.h"
#include "../libc/memory.h"
#include "screen_colors.h"

#include <stdint.h>

// Video Constants Definitions

#define VIDEO_ADDRESS (char *) 0xb8000
#define ROWS_MAX 25
#define COLS_MAX 80

// Screen I/O Ports Definitions

#define PORT_SCREEN_CTRL 0x3d4
#define PORT_SCREEN_DATA 0x3d5

// Public Kernel API Declarations

void clear_screen(void);

void printk(char * message);
void printk_at(char * message, int col, int row);

void printk_color(char * message, char color);
void printk_at_color(char * message, int col, int row, char color);

void printk_backspace(void);

#endif