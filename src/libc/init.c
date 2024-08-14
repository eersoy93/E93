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
#include "video.h"

void init(void)
{
    if (get_video_type() == VIDEO_TYPE_COLOR)
    {
        println("Your video card is colored!", OUTPUT_COLOR);
    }
    else
    {
        end();
    }

    isr_install();
    irq_install();
    ide_init(0x1F0, 0x3F6, 0x170, 0x376, 0x000);
}
