/* DESCRIPTION: E93 PC Speaker Driver Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with GPLv2 License. See LICENSE file for details.
 */

#ifndef SPEAKER_H
#define SPEAKER_H

#include <stdint.h>

void play_sound(uint32_t frequency);
void nosound(void);

#endif
