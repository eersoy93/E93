/* DESCRIPTION: E93 C Library Input/Output Functions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "io.h"

#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
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
    for(int i = 0; i < strlen(key_buffer); i++)
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
