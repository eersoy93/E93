/* DESCRIPTION: E93 C Library IDE Functions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "ide_libc.h"

#include "../drivers/ide.h"
#include "io.h"
#include "string.h"

struct ide_device get_ide_device_information(uint8_t device_number)
{
    return IDEDevices[device_number];
}

void print_ide_device_information(uint8_t device_number)
{
    struct ide_device ide_device_got = get_ide_device_information(device_number);

    if (ide_device_got.Reserved == 1)
    {
        char ide_device_got_number_str[2] = {0};
        int_to_ascii(device_number, ide_device_got_number_str);

        print("Device: ", OUTPUT_COLOR);
        println(ide_device_got_number_str, OUTPUT_COLOR);

        print("Type: ", OUTPUT_COLOR);
        if (ide_device_got.Type == IDE_ATA)
        {
            println("ATA", OUTPUT_COLOR);
        }
        else if (ide_device_got.Type == IDE_ATAPI)
        {
            println("ATAPI", OUTPUT_COLOR);
        }
        else
        {
            println("Unknown", OUTPUT_COLOR);
        }

        print("Model: ", OUTPUT_COLOR);
        println(ide_device_got.Model, OUTPUT_COLOR);

        char ide_device_got_size_str[12] = "";
        int_to_ascii(ide_device_got.Size, ide_device_got_size_str);

        if (ide_device_got.Type == IDE_ATA)
        {
            print("Size: ", OUTPUT_COLOR);
            print(ide_device_got_size_str, OUTPUT_COLOR);
            println(" sectors", OUTPUT_COLOR);
        }

        println("", OUTPUT_COLOR);
    }
}

void list_ide_devices(void)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        print_ide_device_information(i);
    }
}
