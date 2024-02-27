/* DESCRIPTION: E93 Screen Driver Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef SCREEN_H
#define SCREEN_H

#include "../libc/boolean.h"
#include "screen_colors.h"

#include <stdint.h>

// Video Constants Definitions

#define VIDEO_ADDRESS (char *) 0xb8000
#define VIDEO_TYPE_ADDRESS (char *) 0x410
#define ROWS_MAX 25
#define COLS_MAX 80

// Screen I/O Ports Definitions

#define PORT_SCREEN_CTRL 0x3d4
#define PORT_SCREEN_DATA 0x3d5

// Public Kernel API Declarations

void clear_screen(void);

void disable_cursor(void);
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end);

uint16_t get_cursor_column_and_row(void);

uint8_t get_video_colored_type(void);

void printl(char * message);
void printl_at(char * message, int col, int row);

void printl_color(char * message, char color);
void printl_at_color(char * message, int col, int row, char color);

void printl_backspace(void);

void set_cursor_column_and_row(int col, int row);

#endif
