/* DESCRIPTION: E93 C Library VGA Definitions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2025 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "vga_libc.h"

#include "../cpu/ports.h"
#include "../cpu/timer.h"
#include "../drivers/vga.h"
#include "../drivers/vga_font.h"
#include "io.h"

volatile uint8_t current_vga_mode;

void switch_vga_mode(uint8_t vga_mode)
{
    if (vga_mode == 0x12)
    {
        switch_to_vga_12h_mode(mode_12h_regs_values);
    }
    else if (vga_mode == 0x03)
    {
        switch_to_vga_3h_mode(mode_3h_regs_values);
    }
    else
    {
        return;
    }
}

void clear_screen(void)
{
    if (current_vga_mode == 0x12)
    {
        clear_screen_vga_12h_mode();
    }
    else if (current_vga_mode == 0x03)
    {
        cls();
    }
    else
    {
        return;
    }
}

void putpixel(int32_t x, int32_t y, uint8_t color)
{
    if (current_vga_mode == 0x12)
    {
        put_pixel_vga_12h_mode(x, y, color);
    }
    else
    {
        return;
    }
}

void draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint8_t color)
{
    if (current_vga_mode == 0x12)
    {
        draw_line_vga_12h_mode(x1, y1, x2, y2, color);
    }
    else
    {
        return;
    }
}
void draw_rectangle(int32_t x, int32_t y, int32_t width, int32_t height, uint8_t color)
{
    if (current_vga_mode == 0x12)
    {
        draw_rectangle_vga_12h_mode(x, y, width, height, color);
    }
    else
    {
        return;
    }
}

void draw_filled_rectangle(int32_t x, int32_t y, int32_t width, int32_t height, uint8_t color)
{
    if (current_vga_mode == 0x12)
    {
        draw_filled_rectangle_vga_12h_mode(x, y, width, height, color);
    }
    else
    {
        return;
    }
}

void draw_circle(int32_t x0, int32_t y0, int32_t radius, uint8_t color)
{
    if (current_vga_mode == 0x12)
    {
        draw_circle_vga_12h_mode(x0, y0, radius, color);
    }
    else
    {
        return;
    }
}

void draw_filled_circle(int32_t x0, int32_t y0, int32_t radius, uint8_t color)
{
    if (current_vga_mode == 0x12)
    {
        draw_filled_circle_vga_12h_mode(x0, y0, radius, color);
    }
    else
    {
        return;
    }
}

void show_vga_demo(void)
{
    switch_vga_mode(0x12);
    clear_screen();

    draw_filled_rectangle(50, 50, 100, 100, VGA_RED);
    draw_filled_circle(200, 200, 100, VGA_GREEN);
    draw_filled_rectangle(300, 300, 100, 100, VGA_BLUE);
    draw_line(350, 320, 150, 0, VGA_YELLOW);

    wait_timer(100);

    switch_vga_mode(0x03);
}
