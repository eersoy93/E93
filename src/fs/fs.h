/* DESCRIPTION: E93 IS09660 File System Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2025 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef FS_H
#define FS_H

#include <stdint.h>

typedef struct
{
    uint8_t in_use;
    uint32_t extent_lba;    // Logical block address of file start
    uint32_t size;          // File size in bytes
    uint32_t offset;        // Current offset in the file
} iso9660_file_handle_t;

static iso9660_file_handle_t open_files[127];

#endif