/* DESCRIPTION: E93 C Library Video Definitions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "video.h"

#include "../drivers/screen.h"

enum video_types get_video_type(void)
{
    if (get_video_colored_type() == 0x00)
    {
        return VIDEO_TYPE_NONE;
    }
    else if (get_video_colored_type() == 0x20)
    {
        return VIDEO_TYPE_COLOR;
    }
    else if (get_video_colored_type() == 0x30)
    {
        return VIDEO_TYPE_MONO;
    }
    else
    {
        return VIDEO_TYPE_UNKNOWN;
    }
}
