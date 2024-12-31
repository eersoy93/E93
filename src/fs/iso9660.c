/* DESCRIPTION: E93 IS09660 File System Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "iso9660.h"
#include "../cpu/drvutils.h"
#include "../drivers/ide.h"

uint8_t iso9660_open(char filename[])
{
    UNUSED(filename);
    return 0;
}

uint8_t iso9660_read(uint8_t file_descriptor, uint32_t offset, uint32_t size, char buffer[])
{
    UNUSED(file_descriptor);
    UNUSED(offset);
    UNUSED(size);
    UNUSED(buffer);
    return 0;
}

uint8_t iso9660_close(uint8_t file_descriptor)
{
    UNUSED(file_descriptor);
    return 0;
}
