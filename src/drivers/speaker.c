/* DESCRIPTION: E93 PC Speaker Driver Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "speaker.h"

static void play_sound(uint32_t frequency)
{
    set_PIT_2(frequency);

    uint8_t tmp = port_byte_in(0x61);
    if (tmp != (tmp | 3))
    {
        port_byte_out(0x61, tmp | 3);
    }
}

static void nosound(void)
{
    uint8_t tmp = port_byte_in(0x61) & 0xFC;
    port_byte_out(0x61, tmp);
}

void beep(void)
{
    asm volatile("sti");
    play_sound(1000);
    wait_timer(10);
    nosound();
    set_PIT_2(50);
}
