/* DESCRIPTION: E93 C Library Shell Init Function Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with GPLv2 License. See LICENSE file for details.
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

void init(uint8_t mode)
{
    if (get_video_type() == VIDEO_TYPE_COLOR)
    {
        println((uint8_t *)"Your video card is colored!", OUTPUT_COLOR);

        if (mode == CLI_MODE)
        {
            current_vga_mode = 0x03;
            uint8_t current_vga_mode_str[4] = { 0 };
            int_to_ascii(current_vga_mode, current_vga_mode_str);

            print((uint8_t *)"Current VGA mode: ", OUTPUT_COLOR);
            println(current_vga_mode_str, OUTPUT_COLOR);

            isr_install();
            irq_install();
            ide_print_devices();
        }
        else if (mode == GUI_MODE)
        {
            current_vga_mode = 0x12;
            uint8_t current_vga_mode_str[4] = { 0 };
            int_to_ascii(current_vga_mode, current_vga_mode_str);

            print((uint8_t *)"Current VGA mode: ", OUTPUT_COLOR);
            println(current_vga_mode_str, OUTPUT_COLOR);

            isr_install();
            irq_install();
            ide_print_devices();
        }
        else
        {
            println((uint8_t *)"Invalid mode parameter specified!", ERROR_COLOR);

            end();
        }
    }
    else
    {
        end();
    }

    
}
