/* DESCRIPTION: E93 PC Speaker Driver Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "speaker.h"

#include "../cpu/ports.h"
#include "../cpu/timer.h"

void play_sound(uint32_t frequency)
{
    set_PIT_2(frequency);

    uint8_t tmp = port_byte_in(0x61);
    if (tmp != (tmp | 3))
    {
        port_byte_out(0x61, tmp | 3);
    }
}

void nosound(void)
{
    uint8_t tmp = port_byte_in(0x61) & 0xFC;
    port_byte_out(0x61, tmp);
}
