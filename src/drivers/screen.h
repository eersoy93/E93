/* DESCRIPTION: E93 Screen Driver Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with GPLv2 License. See LICENSE file for details.
 */

#ifndef SCREEN_H
#define SCREEN_H

#include "screen_colors.h"

#include <stdint.h>

// Video Constants Definitions

#define VIDEO_ADDRESS (uint8_t *) 0xb8000
#define VIDEO_TYPE_ADDRESS (uint8_t *) 0x410
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

int32_t printl_char(uint8_t character, int32_t col, int32_t row, uint8_t attribute);

void printl(uint8_t * message);
void printl_at(uint8_t * message, int32_t col, int32_t row);

void printl_color(uint8_t * message, uint8_t color);
void printl_at_color(uint8_t * message, int32_t col, int32_t row, uint8_t color);

void printl_backspace(void);

void set_cursor_column_and_row(int32_t col, int32_t row);

#endif
