/* DESCRIPTION: E93 C Library Input/Output Functions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "io.h"

#include "../drivers/ide.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "../fs/iso9660.h"
#include "boolean.h"
#include "function.h"
#include "string.h"

void print_char(char character, char attribute)
{
    char buffer[2] = {character, '\0'};
    printl_color(buffer, attribute);
}

void print(char * str, char attribute)
{
    for(int i = 0; str[i] != '\0'; i++)
    {
        print_char(str[i], attribute);
    }
}

void println(char * str, char attribute)
{
    print(str, attribute);
    print("\n", attribute);
}

char read_char(void)
{
    while(current_mode == KEYUP);

    if (current_scancode > SCANCODE_MAX)
    {
        current_mode = KEYUP;
        return '?';
    }
    else if (current_scancode == ENTER)
    {
        current_mode = KEYUP;
        return ENTER;
    }
    else if (current_scancode == BACKSPACE)
    {
        current_mode = KEYUP;
        return BACKSPACE;
    }
    else
    {
        current_mode = KEYUP;
        char character = scancode_ascii[(int)current_scancode];
        return character;
    }
}

char * input(void)
{
    enable_cursor(0, 15);

    char * key_buffer = "";
    for(uint32_t i = 0; i < strlen(key_buffer); i++)
    {
        key_buffer[i] = '\0';
    }

    while(TRUE)
    {
        char c = read_char();
        if (c != ENTER && c != BACKSPACE)
        {
            append(key_buffer, c);
            print_char(c, OUTPUT_COLOR);
        }
        else if (c == BACKSPACE)
        {
            backspace(key_buffer);
            printl_backspace();
        }
        else if (c == ENTER)
        {
            disable_cursor();
            print("\n", OUTPUT_COLOR);
            return key_buffer;
        }
    }
}

void cls(void)
{
    clear_screen();
    set_cursor_column_and_row(0, 0);
}

uint8_t open_file(char filename[])
{
    uint8_t file_descriptor = iso9660_open(filename);

    if (file_descriptor == 0xFF) // Assuming 0xFF indicates an error
    {
        println("Error: File not found or could not be opened!", ERROR_COLOR);
        return 0xFF;
    }

    return file_descriptor;
}

uint8_t read_file(uint8_t file_descriptor, uint32_t offset, uint32_t size, char buffer[])
{
    uint8_t read_status = iso9660_read(file_descriptor, offset, size, buffer);

    if (read_status == 0xFF) // Assuming 0xFF indicates an error
    {
        println("Error: File could not be read!", ERROR_COLOR);
        return 0xFF;
    }

    return 0;
}

uint8_t close_file(uint8_t file_descriptor)
{
    uint8_t close_status = iso9660_close(file_descriptor);

    if (close_status == 0xFF) // Assuming 0xFF indicates an error
    {
        println("Error: File could not be closed!", ERROR_COLOR);
        return 0xFF;
    }

    return 0;
}
