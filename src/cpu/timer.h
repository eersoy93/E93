/* DESCRIPTION: E93 CPU Timer Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void set_PIT_2(uint32_t frequency);
void init_timer(uint32_t frequency);
void wait_timer(uint32_t ticks);

#endif
