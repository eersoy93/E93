/* DESCRIPTION: E93 C Library Sound Functions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "sound.h"

#include "../cpu/timer.h"
#include "../drivers/speaker.h"

void sound(uint32_t frequency, uint32_t duration)
{
    asm volatile("sti");
    play_sound(frequency);
    wait_timer(duration);
    nosound();
    set_PIT_2(50);
}

void beep(void)
{
    sound(1000, 5);
}
