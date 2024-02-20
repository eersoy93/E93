/* DESCRIPTION: E93 C Library Sound Functions Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef SOUND_H
#define SOUND_H

#include <stdint.h>

void sound(uint32_t frequency, uint32_t duration);
void beep(void);

#endif
