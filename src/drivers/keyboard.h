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

const uint8_t *scancode_name[] = { (uint8_t *)"ERROR",
                                   (uint8_t *)"Esc",
                                   (uint8_t *)"1",
                                   (uint8_t *)"2",
                                   (uint8_t *)"3",
                                   (uint8_t *)"4",
                                   (uint8_t *)"5",
                                   (uint8_t *)"6", 
                                   (uint8_t *)"7",
                                   (uint8_t *)"8",
                                   (uint8_t *)"9",
                                   (uint8_t *)"0",
                                   (uint8_t *)"-",
                                   (uint8_t *)"=",
                                   (uint8_t *)"Backspace",
                                   (uint8_t *)"Tab",
                                   (uint8_t *)"Q",
                                   (uint8_t *)"W",
                                   (uint8_t *)"E",
                                   (uint8_t *)"R",
                                   (uint8_t *)"T",
                                   (uint8_t *)"Y",
                                   (uint8_t *)"U",
                                   (uint8_t *)"I",
                                   (uint8_t *)"O",
                                   (uint8_t *)"P",
                                   (uint8_t *)"[",
                                   (uint8_t *)"]",
                                   (uint8_t *)"Enter",
                                   (uint8_t *)"Left Ctrl",
                                   (uint8_t *)"A",
                                   (uint8_t *)"S",
                                   (uint8_t *)"D",
                                   (uint8_t *)"F",
                                   (uint8_t *)"G",
                                   (uint8_t *)"H",
                                   (uint8_t *)"J",
                                   (uint8_t *)"K",
                                   (uint8_t *)"L",
                                   (uint8_t *)";",
                                   (uint8_t *)"'",
                                   (uint8_t *)"`",
                                   (uint8_t *)"Left Shift",
                                   (uint8_t *)"\\",
                                   (uint8_t *)"Z",
                                   (uint8_t *)"X",
                                   (uint8_t *)"C",
                                   (uint8_t *)"V",
                                   (uint8_t *)"B",
                                   (uint8_t *)"N",
                                   (uint8_t *)"M",
                                   (uint8_t *)",",
                                   (uint8_t *)".",
                                   (uint8_t *)"/",
                                   (uint8_t *)"Right Shift",
                                   (uint8_t *)"Keypad *",
                                   (uint8_t *)"Left Alt",
                                   (uint8_t *)"Spacebar"
};

const uint8_t scancode_ascii[] = { (uint8_t)'?',
                                   (uint8_t)'?',
                                   (uint8_t)'1',
                                   (uint8_t)'2',
                                   (uint8_t)'3',
                                   (uint8_t)'4',
                                   (uint8_t)'5',
                                   (uint8_t)'6',
                                   (uint8_t)'7',
                                   (uint8_t)'8',
                                   (uint8_t)'9',
                                   (uint8_t)'0',
                                   (uint8_t)'-',
                                   (uint8_t)'=',
                                   (uint8_t)'?',
                                   (uint8_t)'?',
                                   (uint8_t)'Q',
                                   (uint8_t)'W',
                                   (uint8_t)'E',
                                   (uint8_t)'R',
                                   (uint8_t)'T',
                                   (uint8_t)'Y',
                                   (uint8_t)'U',
                                   (uint8_t)'I',
                                   (uint8_t)'O',
                                   (uint8_t)'P',
                                   (uint8_t)'[',
                                   (uint8_t)']',
                                   (uint8_t)'?',
                                   (uint8_t)'?',
                                   (uint8_t)'A',
                                   (uint8_t)'S',
                                   (uint8_t)'D',
                                   (uint8_t)'F',
                                   (uint8_t)'G',
                                   (uint8_t)'H',
                                   (uint8_t)'J',
                                   (uint8_t)'K',
                                   (uint8_t)'L',
                                   (uint8_t)';',
                                   (uint8_t)'\'',
                                   (uint8_t)'`',
                                   (uint8_t)'?',
                                   (uint8_t)'\\',
                                   (uint8_t)'Z',
                                   (uint8_t)'X',
                                   (uint8_t)'C',
                                   (uint8_t)'V',
                                   (uint8_t)'B',
                                   (uint8_t)'N',
                                   (uint8_t)'M',
                                   (uint8_t)',',
                                   (uint8_t)'.',
                                   (uint8_t)'/',
                                   (uint8_t)'?',
                                   (uint8_t)'?',
                                   (uint8_t)'?',
                                   (uint8_t)' '
};

void keydown_handler(uint8_t scancode);
void keyup_handler(uint8_t scancode);

void init_keyboard(void);

#endif

