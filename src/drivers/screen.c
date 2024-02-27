/* DESCRIPTION: E93 Screen Driver Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "screen.h"

#include "../cpu/ports.h"
#include "../libc/memory.h"

#include <stdint.h>

// Private Kernel API Declarations

int get_cursor_offset(void);

int get_offset(int col, int row);
int get_offset_col(int offset);
int get_offset_row(int offset);

int printl_char(char character, int col, int row, char attribute);

void set_cursor_offset(int offset);
void set_cursor_shape(void);


// Public Kernel API Definitions

// Clear entire screen with black
void clear_screen(void)
{
    int screen_size = COLS_MAX * ROWS_MAX;
    int i = 0;
    char * screen = VIDEO_ADDRESS;

    for (i = 0; i < screen_size; i++)
    {
        screen[i * 2] = ' ';
        screen[i * 2 + 1] = CLRSCR_COLOR;
    }

    set_cursor_offset(get_offset(0, 0));
}

// Disable cursor
void disable_cursor(void)
{
    port_byte_out(PORT_SCREEN_CTRL, 0x0a);
    port_byte_out(PORT_SCREEN_DATA, 0x20);
}

// Enable cursor with specific start and end
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
    port_byte_out(PORT_SCREEN_CTRL, 0x0a);
    port_byte_out(PORT_SCREEN_DATA, (port_byte_in(PORT_SCREEN_DATA) & 0xc0) | cursor_start);
    port_byte_out(PORT_SCREEN_CTRL, 0x0b);
    port_byte_out(PORT_SCREEN_DATA, (port_byte_in(PORT_SCREEN_DATA) & 0xe0) | cursor_end);
    set_cursor_shape();
}

// Get cursor column and row
uint16_t get_cursor_column_and_row(void)
{
    int offset = get_cursor_offset();
    return offset / 2;
}

// Detect if the video is colored
uint8_t get_video_colored_type(void)
{
    const char * video_type_information = VIDEO_TYPE_ADDRESS;

    return ((*video_type_information) & 0x30);
}

// Print message at cursor location
void printl(char * message)
{
    printl_color(message, DEFAULT_COLOR);
}

// Print message at specific location
void printl_at(char * message, int col, int row)
{
    printl_at_color(message, col, row, DEFAULT_COLOR);
}

// Print message at cursor location  with specfific color
void printl_color(char * message, char color)
{
    printl_at_color(message, -1, -1, color);
}

// Print message at specific location with specfific color
void printl_at_color(char * message, int col, int row, char color)
{
    int offset = 0;

    if (col >= 0 && row >= 0)
    {
        offset = get_offset(col, row);
    }
    else
    {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    int i = 0;

    while (message[i] != 0)
    {
        offset = printl_char(message[i++], col, row, color);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

// Revert printing via backspace
void printl_backspace(void)
{
    int offset = get_cursor_offset() - 2;
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    if (col != 0)
    {
        printl_char(0x20, col, row, DEFAULT_COLOR);
        set_cursor_offset(offset);
    }
}

// Set cursor column and row
void set_cursor_column_and_row(int col, int row)
{
    int offset = get_offset(col, row);
    set_cursor_offset(offset);
}


// Private Kernel API Definitions

// Get cursor video memory offset
int get_cursor_offset()
{
    port_byte_out(PORT_SCREEN_CTRL, 14);
    int offset = port_byte_in(PORT_SCREEN_DATA) << 8;
    port_byte_out(PORT_SCREEN_CTRL, 15);
    offset += port_byte_in(PORT_SCREEN_DATA);

    return offset * 2;
}

// Get specific location video memory offset
int get_offset(int col, int row)
{
    return 2 * (row * COLS_MAX + col);
}

// Get specific column of video memory offset
int get_offset_col(int offset)
{
    return (offset - (get_offset_row(offset) * 2 * COLS_MAX)) / 2;
}

// Get specific row of video memory offset
int get_offset_row(int offset)
{
    return offset / (2 * COLS_MAX);
}

// Print specific character with specific attribute at specific loaction
int printl_char(char character, int col, int row, char attribute)
{
    unsigned char * video_memory = (unsigned char *) VIDEO_ADDRESS;
    if (!attribute)
    {
        attribute = DEFAULT_COLOR;
    }

    if (col >= COLS_MAX || row >= ROWS_MAX)
    {
        video_memory[2 * COLS_MAX * ROWS_MAX - 2] = 'E';
        video_memory[2 * COLS_MAX * ROWS_MAX - 1] = ERROR_COLOR_2;
        return get_offset(col, row);
    }

    int offset = 0;
    if (col >= 0 && row >= 0)
    {
        offset = get_offset(col, row);
    }
    else {
        offset = get_cursor_offset();
    }

    if (character == '\n')
    {
        row = get_offset_row(offset);
        offset = get_offset(0, row + 1) ;
    }
    else
    {
        video_memory[offset] = character;
        video_memory[offset + 1] = attribute;
        offset += 2;
    }

    if (offset >= ROWS_MAX * COLS_MAX * 2)
    {
        int i = 0;
        for (i = 1; i < ROWS_MAX; i++)
        {
            memory_copy((uint8_t *)(get_offset(0, i) + VIDEO_ADDRESS),
                        (uint8_t *)(get_offset(0, i - 1) + VIDEO_ADDRESS),
                        COLS_MAX * 2);
        }

    char * lastline = get_offset(0, ROWS_MAX - 1) + VIDEO_ADDRESS;
    for (i = 0; i < COLS_MAX * 2; i++)
    {
        lastline[i] = 0;
    }

    offset -= COLS_MAX * 2;
    }

    set_cursor_offset(offset);
    return offset;
}

// Set cursor video memory offset
void set_cursor_offset(int offset)
{
    offset /= 2;
    port_byte_out(PORT_SCREEN_CTRL, 14);
    port_byte_out(PORT_SCREEN_DATA, (unsigned char) (offset >> 8));
    port_byte_out(PORT_SCREEN_CTRL, 15);
    port_byte_out(PORT_SCREEN_DATA, (unsigned char) (offset & 0xff));
}

// Set cursor shape
void set_cursor_shape(void)
{
    port_byte_out(PORT_SCREEN_CTRL, 0x0a);
    port_byte_out(PORT_SCREEN_DATA, 0x0F);  // As '_' character shaped cursor
}
