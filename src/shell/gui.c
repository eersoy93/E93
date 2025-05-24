/* DESCRIPTION: E93 Shell GUI Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2025 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "gui.h"
#include "../libc/vga_libc.h"

void gui_init(void)
{
    switch_vga_mode(0x12);

    clear_screen();

    draw_string(0, 0, (uint8_t *)"GUI mode not yet implemented!", VGA_BLACK, VGA_WHITE);
}
