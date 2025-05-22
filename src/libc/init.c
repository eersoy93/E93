/* DESCRIPTION: E93 C Library Shell Init Function Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "init.h"

#include "../cpu/isr.h"
#include "../drivers/ide.h"
#include "ending.h"
#include "io.h"
#include "string.h"
#include "video.h"
#include "vga_libc.h"

volatile uint8_t current_vga_mode;

void init(void)
{
    if (get_video_type() == VIDEO_TYPE_COLOR)
    {
        println((uint8_t *)"Your video card is colored!", OUTPUT_COLOR);

        current_vga_mode = 0x03;
        uint8_t current_vga_mode_str[5] = { 0 };
        int_to_ascii(current_vga_mode, current_vga_mode_str);
        print((uint8_t *)"Current VGA mode: ", OUTPUT_COLOR);
        println(current_vga_mode_str, OUTPUT_COLOR);
    }
    else
    {
        end();
    }

    isr_install();
    irq_install();
    ide_init(0x1F0, 0x3F6, 0x170, 0x376, 0x000);
    ide_print_devices();
}
