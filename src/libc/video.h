/* DESCRIPTION: E93 C Library Video Definitions Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef VIDEO_H
#define VIDEO_H

#include <stdint.h>

enum video_types {
    VIDEO_TYPE_NONE = 0,
    VIDEO_TYPE_COLOR = 1,
    VIDEO_TYPE_MONO = 2,
    VIDEO_TYPE_UNKNOWN = 3,
};

enum video_types get_video_type(void);

#endif
