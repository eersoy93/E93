/* DESCRIPTION: E93 Keyboard Driver Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

#define BACKSPACE 0x0E
#define ENTER 0x1C

#define SCANCODE_MAX 57

volatile uint8_t current_scancode;

enum current_modes
{
    KEYDOWN = 0,
    KEYUP = 1
};

volatile enum current_modes current_mode;

const char * scancode_name[] = {"ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
                                "7", "8", "9", "0", "-", "=", "Backspace",
                                "Tab", "Q", "W", "E", "R", "T", "Y", "U", "I",
                                "O", "P", "[", "]", "Enter", "Left Ctrl",
                                "A", "S", "D", "F", "G", "H", "J", "K", "L",
                                ";", "'", "`", "Left Shift", "\\", "Z", "X",
                                "C", "V", "B", "N", "M", ",", ".", "/",
                                "Right Shift", "Keypad *", "Left Alt",
                                "Spacebar"};

const char scancode_ascii[] = {'?', '?', '1', '2', '3', '4', '5', '6',     
                               '7', '8', '9', '0', '-', '=', '?',
                               '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I',
                               'O', 'P', '[', ']', '?', '?',
                               'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
                               ';', '\'', '`', '?', '\\', 'Z', 'X',
                               'C', 'V', 'B', 'N', 'M', ',', '.', '/',
                               '?', '?', '?',
                               ' '};

void keydown_handler(uint8_t scancode);
void keyup_handler(uint8_t scancode);

void init_keyboard(void);

#endif

