/* DESCRIPTION: E93 C Library VGA Definitions Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2025 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef VGA_LIBC_H
#define VGA_LIBC_H

#include <stdint.h>

void switch_vga_mode(uint8_t vga_mode);
void clear_screen(void);

void putpixel(int32_t x, int32_t y, uint8_t color);
void draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint8_t color);
void draw_rectangle(int32_t x, int32_t y, int32_t width, int32_t height, uint8_t color);
void draw_filled_rectangle(int32_t x, int32_t y, int32_t width, int32_t height, uint8_t color);
void draw_circle(int32_t x0, int32_t y0, int32_t radius, uint8_t color);
void draw_filled_circle(int32_t x0, int32_t y0, int32_t radius, uint8_t color);
void draw_char(int32_t x, int32_t y, uint8_t c, uint8_t color, uint8_t bgcolor);
void draw_string(int32_t x, int32_t y, uint8_t * str, uint8_t color, uint8_t bgcolor);

void show_vga_demo(void);

#endif // VGA_LIBC_H