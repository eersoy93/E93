/* DESCRIPTION: E93 VGA Driver Functions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2025 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "vga.h"

#include "../cpu/ports.h"
#include "../cpu/timer.h"
#include "screen.h"
#include "vga_font.h"

volatile uint8_t * VGA_MODE_PTR;

volatile uint8_t current_vga_mode;

void switch_to_vga_12h_mode(uint8_t * regs_values)
{
    VGA_MODE_PTR = (volatile uint8_t *)0xA0000;
    current_vga_mode = 0x12; // Set current mode to 12h
    int32_t index = 0;
    int32_t i = 0;

    // Write miscellaneous output register
    port_byte_out(VGA_MISC_WRITE, regs_values[index++]);

    // Write sequencer registers
    for (i = 0; i < NUM_SEQ; i++)
    {
        port_byte_out(VGA_SEQ_INDEX, i);
        port_byte_out(VGA_SEQ_DATA, regs_values[index++]);
    }

    // Unlock CRTC registers 0x03 and 0x11
    port_byte_out(VGA_CRTC_INDEX, 0x03);
    port_byte_out(VGA_CRTC_DATA, port_byte_in(VGA_CRTC_DATA) | 0x80);
    port_byte_out(VGA_CRTC_INDEX, 0x11);
    port_byte_out(VGA_CRTC_DATA, port_byte_in(VGA_CRTC_DATA) & ~0x80);

    // Write CRTC registers
    for (i = 0; i < NUM_CRTC; i++)
    {
        port_byte_out(VGA_CRTC_INDEX, i);
        port_byte_out(VGA_CRTC_DATA, regs_values[index++]);
    }

    // Write graphics controller registers
    for (i = 0; i < NUM_GC; i++)
    {
        port_byte_out(VGA_GC_INDEX, i);
        port_byte_out(VGA_GC_DATA, regs_values[index++]);
    }

    // Write attribute controller registers
    for (i = 0; i < NUM_AC; i++)
    {
        (void)port_byte_in(VGA_INSTAT_READ); // Reset flip-flop before writing each register
        port_byte_out(VGA_AC_INDEX, i);
        port_byte_out(VGA_AC_INDEX, regs_values[index++]); // Same port!
    }
    
    // Finalize attribute controller write
    (void)port_byte_in(VGA_INSTAT_READ);
    port_byte_out(VGA_AC_INDEX, 0x20);

    clear_screen_vga_12h_mode(); // Clear screen after mode switch
}

void clear_screen_vga_12h_mode(void)
{
    wait_vsync(); // Wait for vertical retrace to avoid tearing
    volatile uint8_t * vga = (volatile uint8_t *)VGA_MODE_PTR;
    int32_t plane = 0;
    int32_t i = 0;
    int32_t plane_size = 80 * 480; // Each plane: 80 bytes per scanline (640/8) * 480 scanlines

    for (plane = 0; plane < 4; plane++)
    {
        // Select the current plane by writing to the Sequencer Map Mask Register (index 2)
        port_byte_out(VGA_SEQ_INDEX, 2);
        port_byte_out(VGA_SEQ_DATA, 1 << plane);

        // Clear the current plane by setting all bytes to 0
        for (i = 0; i < plane_size; i++)
        {
            vga[i] = 0;
        }
    }
    
    // Restore writing to all planes
    port_byte_out(VGA_SEQ_INDEX, 2);
    port_byte_out(VGA_SEQ_DATA, 0x0F);
}

void put_pixel_vga_12h_mode(int32_t x, int32_t y, uint8_t color)
{
    // Clip coordinates to VGA boundaries
    if (x < 0) x = 0;
    if (x >= VGA_12H_WIDTH) x = VGA_12H_WIDTH - 1;
    if (y < 0) y = 0;
    if (y >= VGA_12H_HEIGHT) y = VGA_12H_HEIGHT - 1;

    volatile uint8_t * vga = (volatile uint8_t *)VGA_MODE_PTR;
    int32_t offset = y * 80 + (x >> 3);
    uint8_t bit_mask = 0x80 >> (x & 7);

    // Set Read Mode 0
    port_byte_out(VGA_GC_INDEX, 0x05);
    port_byte_out(VGA_GC_DATA, 0x00);
    
    // Set the Bit Mask Register to affect only this pixel
    port_byte_out(VGA_GC_INDEX, 0x08);
    port_byte_out(VGA_GC_DATA, bit_mask);
    
    // Enable all planes for writing
    port_byte_out(VGA_SEQ_INDEX, 0x02);
    port_byte_out(VGA_SEQ_DATA, 0x0F);
    
    // Set Data Rotate Register to copy mode (no rotation, no logical operation)
    port_byte_out(VGA_GC_INDEX, 0x03);
    port_byte_out(VGA_GC_DATA, 0x00);
    
    // Set Write Mode 0
    port_byte_out(VGA_GC_INDEX, 0x05);
    port_byte_out(VGA_GC_DATA, 0x00);
    
    // Set all planes to write the value 0
    port_byte_out(VGA_GC_INDEX, 0x00);
    port_byte_out(VGA_GC_DATA, 0x00);
    port_byte_out(VGA_GC_INDEX, 0x01);
    port_byte_out(VGA_GC_DATA, 0x00);
    port_byte_out(VGA_GC_INDEX, 0x02);
    port_byte_out(VGA_GC_DATA, 0x00);
    port_byte_out(VGA_GC_INDEX, 0x03);
    port_byte_out(VGA_GC_DATA, 0x00);
    
    // Use Map Mask Register to select which planes to write
    port_byte_out(VGA_SEQ_INDEX, 0x02);
    port_byte_out(VGA_SEQ_DATA, color & 0x0F);
    
    // Write to the pixel (using latch mechanism)
    vga[offset] |= 0xFF;
    
    // Reset settings
    port_byte_out(VGA_SEQ_INDEX, 0x02);
    port_byte_out(VGA_SEQ_DATA, 0x0F);
    port_byte_out(VGA_GC_INDEX, 0x08);
    port_byte_out(VGA_GC_DATA, 0xFF);
}

void draw_line_vga_12h_mode(int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint8_t color)
{
    // Clip coordinates to VGA boundaries
    if (x0 < 0) x0 = 0;
    if (x0 >= VGA_12H_WIDTH) x0 = VGA_12H_WIDTH - 1;
    if (y0 < 0) y0 = 0;
    if (y0 >= VGA_12H_HEIGHT) y0 = VGA_12H_HEIGHT - 1;
    if (x1 < 0) x1 = 0;
    if (x1 >= VGA_12H_WIDTH) x1 = VGA_12H_WIDTH - 1;
    if (y1 < 0) y1 = 0;
    if (y1 >= VGA_12H_HEIGHT) y1 = VGA_12H_HEIGHT - 1;

    // Eraly exit if the start and end points are the same
    if (x0 == x1 && y0 == y1) {
        put_pixel_vga_12h_mode(x0, y0, color);
        return;
    }

    // Bresenham line algorithm for calculating differences
    int32_t dx = (x1 > x0) ? (x1 - x0) : (x0 - x1);
    int32_t dy = (y1 > y0) ? (y1 - y0) : (y0 - y1);
    int32_t sx = (x0 < x1) ? 1 : -1;
    int32_t sy = (y0 < y1) ? 1 : -1;
    int32_t err = dx - dy;
    int32_t e2;
    
    while (1) {
        put_pixel_vga_12h_mode(x0, y0, color);
        
        if (x0 == x1 && y0 == y1) {
            break;
        }
        
        e2 = err * 2; // Prevent overflow
        
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// Draw a rectangle outline
void draw_rectangle_vga_12h_mode(int32_t x, int32_t y, int32_t width, int32_t height, uint8_t color)
{
    // Check bounds
    if (x < 0 || y < 0 || x + width > VGA_12H_WIDTH || y + height > VGA_12H_HEIGHT)
    {
        return;
    }

    // Draw the four lines
    int32_t x2 = x + width - 1;
    int32_t y2 = y + height - 1;

    // Top horizontal line
    draw_line_vga_12h_mode(x, y, x2, y, color);
    
    // Bottom horizontal line
    draw_line_vga_12h_mode(x, y2, x2, y2, color);
    
    // Left vertical line
    draw_line_vga_12h_mode(x, y, x, y2, color);
    
    // Right vertical line
    draw_line_vga_12h_mode(x2, y, x2, y2, color);
}

// Draw a filled rectangle
void draw_filled_rectangle_vga_12h_mode(int32_t x, int32_t y, int32_t width, int32_t height, uint8_t color)
{
    int32_t j = 0;

    // Check bounds
    if (x < 0 || y < 0 || x + width > VGA_12H_WIDTH || y + height > VGA_12H_HEIGHT)
    {
        return;
    }

    // Draw the rectangle line by line (horizontal scanlines) for efficiency
    for (j = y; j < y + height; j++)
    {
        draw_line_vga_12h_mode(x, j, x + width - 1, j, color);
    }
}

// Draw a circle using the midpoint circle algorithm
void draw_circle_vga_12h_mode(int32_t x0, int32_t y0, int32_t radius, uint8_t color)
{
    int32_t x = radius;
    int32_t y = 0;
    int32_t err = 0;

    while (x >= y)
    {
        // Draw 8 octants
        if (x0 + x >= 0 && x0 + x < VGA_12H_WIDTH && y0 + y >= 0 && y0 + y < VGA_12H_HEIGHT)
        {
            put_pixel_vga_12h_mode(x0 + x, y0 + y, color);
        }
            
        if (x0 + y >= 0 && x0 + y < VGA_12H_WIDTH && y0 + x >= 0 && y0 + x < VGA_12H_HEIGHT)
        {
            put_pixel_vga_12h_mode(x0 + y, y0 + x, color);
        }
            
        if (x0 - y >= 0 && x0 - y < VGA_12H_WIDTH && y0 + x >= 0 && y0 + x < VGA_12H_HEIGHT)
        {
            put_pixel_vga_12h_mode(x0 - y, y0 + x, color);
        }
            
        if (x0 - x >= 0 && x0 - x < VGA_12H_WIDTH && y0 + y >= 0 && y0 + y < VGA_12H_HEIGHT)
        {
            put_pixel_vga_12h_mode(x0 - x, y0 + y, color);
        }
            
        if (x0 - x >= 0 && x0 - x < VGA_12H_WIDTH && y0 - y >= 0 && y0 - y < VGA_12H_HEIGHT)
        {
            put_pixel_vga_12h_mode(x0 - x, y0 - y, color);
        }
            
        if (x0 - y >= 0 && x0 - y < VGA_12H_WIDTH && y0 - x >= 0 && y0 - x < VGA_12H_HEIGHT)
        {
            put_pixel_vga_12h_mode(x0 - y, y0 - x, color);
        }
            
        if (x0 + y >= 0 && x0 + y < VGA_12H_WIDTH && y0 - x >= 0 && y0 - x < VGA_12H_HEIGHT)
        {
            put_pixel_vga_12h_mode(x0 + y, y0 - x, color);
        }
            
        if (x0 + x >= 0 && x0 + x < VGA_12H_WIDTH && y0 - y >= 0 && y0 - y < VGA_12H_HEIGHT)
        {
            put_pixel_vga_12h_mode(x0 + x, y0 - y, color);
        }

        if (err <= 0)
        {
            y += 1;
            err += 2 * y + 1;
        }
        else
        {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

// Draw a filled circle using the midpoint circle algorithm
void draw_filled_circle_vga_12h_mode(int32_t x0, int32_t y0, int32_t radius, uint8_t color)
{
    int32_t x = radius;
    int32_t y = 0;
    int32_t err = 0;
    int32_t x1, x2;

    while (x >= y)
    {
        // For each horizontal scan line within the circle, draw a line
        
        // Y0 + Y level
        x1 = x0 - x;
        x2 = x0 + x;
        if (y0 + y >= 0 && y0 + y < VGA_12H_HEIGHT) {
            if (x1 < 0) x1 = 0;
            if (x2 >= VGA_12H_WIDTH) x2 = VGA_12H_WIDTH - 1;
            draw_line_vga_12h_mode(x1, y0 + y, x2, y0 + y, color);
        }
        
        // Y0 - Y level
        if (y0 - y >= 0 && y0 - y < VGA_12H_HEIGHT) {
            if (x1 < 0) x1 = 0;
            if (x2 >= VGA_12H_WIDTH) x2 = VGA_12H_WIDTH - 1;
            draw_line_vga_12h_mode(x1, y0 - y, x2, y0 - y, color);
        }
        
        // Y0 + X level
        x1 = x0 - y;
        x2 = x0 + y;
        if (y0 + x >= 0 && y0 + x < VGA_12H_HEIGHT) {
            if (x1 < 0) x1 = 0;
            if (x2 >= VGA_12H_WIDTH) x2 = VGA_12H_WIDTH - 1;
            draw_line_vga_12h_mode(x1, y0 + x, x2, y0 + x, color);
        }
        
        // Y0 - X level
        if (y0 - x >= 0 && y0 - x < VGA_12H_HEIGHT) {
            if (x1 < 0) x1 = 0;
            if (x2 >= VGA_12H_WIDTH) x2 = VGA_12H_WIDTH - 1;
            draw_line_vga_12h_mode(x1, y0 - x, x2, y0 - x, color);
        }

        // Update circle parameters
        if (err <= 0)
        {
            y += 1;
            err += 2 * y + 1;
        }
        else
        {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void draw_char_vga_12h_mode(int32_t x, int32_t y, uint8_t c, uint8_t color, uint8_t bgcolor)
{
    // Clip coordinates to VGA boundaries
    if (x < 0) x = 0;
    if (x >= VGA_12H_WIDTH) x = VGA_12H_WIDTH - 1;
    if (y < 0) y = 0;
    if (y >= VGA_12H_HEIGHT) y = VGA_12H_HEIGHT - 1;

    // Draw character using the font data
    const uint8_t * font = vga_font_8x16 + (c * 16);
    for (int32_t row = 0; row < 16; row++)
    {
        uint8_t line = font[row];
        for (int32_t col = 0; col < 8; col++)
        {
            if (line & (0x80 >> col))
            {
                put_pixel_vga_12h_mode(x + col, y + row, color);
            }
            else
            {
                put_pixel_vga_12h_mode(x + col, y + row, bgcolor);
            }
        }
    }
}

// Wait for vertical sync to avoid screen tearing
void wait_vsync(void)
{
    // Wait until vertical retrace is not in progress
    while (port_byte_in(VGA_INSTAT_READ) & 8);

    // Wait until vertical retrace is in progress
    while (!(port_byte_in(VGA_INSTAT_READ) & 8));
}

void switch_to_vga_3h_mode(uint8_t * regs_values)
{
    current_vga_mode = 0x03; // Set current mode to 3h
    VGA_MODE_PTR = (volatile uint8_t *)0xB8000;
    int32_t index = 0;
    int32_t i = 0;

    // 1. Misc register
    port_byte_out(VGA_MISC_WRITE, regs_values[index++]);

    // 2. Sequencer registers
    for (i = 0; i < NUM_SEQ; i++)
    {
        port_byte_out(VGA_SEQ_INDEX, i);
        port_byte_out(VGA_SEQ_DATA, regs_values[index++]);
    }

    // 3. Unlock CRTC reg 0x11
    port_byte_out(VGA_CRTC_INDEX, 0x11);
    port_byte_out(VGA_CRTC_DATA, port_byte_in(VGA_CRTC_DATA) & ~0x80);

    // 4. CRTC registers
    for (i = 0; i < NUM_CRTC; i++)
    {
        port_byte_out(VGA_CRTC_INDEX, i);
        port_byte_out(VGA_CRTC_DATA, regs_values[index++]);
    }

    // 5. Graphics controller
    for (i = 0; i < NUM_GC; i++)
    {
        port_byte_out(VGA_GC_INDEX, i);
        port_byte_out(VGA_GC_DATA, regs_values[index++]);
    }

    // 6. Attribute controller
    for (int32_t i = 0; i < NUM_AC; i++)
    {
        (void)port_byte_in(VGA_INSTAT_READ);
        port_byte_out(VGA_AC_INDEX, i);
        port_byte_out(VGA_AC_INDEX, regs_values[index++]);
    }
    (void)port_byte_in(VGA_INSTAT_READ);
    port_byte_out(VGA_AC_INDEX, 0x20); // enable output

    // 7. Upload 8x16 font
    vga_upload_font(vga_font_8x16);

    // 8. Reset DAC/palette
    vga_reset_palette();

    // Clear screen after mode switch
    clear_screen();
}


// --- Upload standard 8x16 font (plane 2) ---
void vga_upload_font(const uint8_t * font)
{
    port_byte_out(VGA_SEQ_INDEX, 0x02); port_byte_out(VGA_SEQ_DATA, 0x04);
    port_byte_out(VGA_SEQ_INDEX, 0x04); port_byte_out(VGA_SEQ_DATA, 0x06);
    port_byte_out(VGA_GC_INDEX, 0x04); port_byte_out(VGA_GC_DATA, 0x02);
    port_byte_out(VGA_GC_INDEX, 0x05); port_byte_out(VGA_GC_DATA, 0x00);
    port_byte_out(VGA_GC_INDEX, 0x06); port_byte_out(VGA_GC_DATA, 0x04);

    volatile uint8_t * fontmem = (uint8_t *)0xA0000;
    for (int32_t ch = 0; ch < 256; ch++)
    {
        for (int32_t row = 0; row < 16; row++)
        {
            fontmem[ch * 32 + row] = *font++;
        }
    }

    // Restore normal access
    port_byte_out(VGA_SEQ_INDEX, 0x02); port_byte_out(VGA_SEQ_DATA, 0x03);
    port_byte_out(VGA_SEQ_INDEX, 0x04); port_byte_out(VGA_SEQ_DATA, 0x02);
    port_byte_out(VGA_GC_INDEX, 0x04); port_byte_out(VGA_GC_DATA, 0x00);
    port_byte_out(VGA_GC_INDEX, 0x05); port_byte_out(VGA_GC_DATA, 0x10);
    port_byte_out(VGA_GC_INDEX, 0x06); port_byte_out(VGA_GC_DATA, 0x0E);
}

// --- Reset 16-color DAC/palette (standard VGA) ---
void vga_reset_palette(void)
{
    static const uint8_t vga_palette[48] = {
        0x00,0x00,0x00,   0x00,0x00,0x2A,   0x00,0x2A,0x00,   0x00,0x2A,0x2A,
        0x2A,0x00,0x00,   0x2A,0x00,0x2A,   0x2A,0x15,0x00,   0x2A,0x2A,0x2A,
        0x15,0x15,0x15,   0x15,0x15,0x3F,   0x15,0x3F,0x15,   0x15,0x3F,0x3F,
        0x3F,0x15,0x15,   0x3F,0x15,0x3F,   0x3F,0x3F,0x15,   0x3F,0x3F,0x3F
    };

    port_byte_out(VGA_DAC_WRITE_INDEX, 0);
    for (int32_t i = 0; i < 48; i++)
    {
        port_byte_out(VGA_DAC_DATA, vga_palette[i]);
    }
}
