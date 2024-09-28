/* DESCRIPTION: E93 C Library IDE Functions Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef IDE_LIBC_H
#define IDE_LIBC_H

#include <stdint.h>

struct ide_device get_ide_device_information(uint8_t device_number);

void print_ide_device_information(uint8_t device_number);

void list_ide_devices(void);

#endif
