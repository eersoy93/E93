/* DESCRIPTION: E93 Shell Paging Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "paging.h"

#include "shell_main.h"
#include "../libc/io.h"
#include "../libc/memory.h"
#include "../libc/string.h"

void allocate_page(void)
{
    uint32_t physical_address = 0;
    uint32_t page = kmalloc(1000, 1, &physical_address);

    uint8_t page_str[16] = "";
    hex_to_ascii(page, page_str);

    uint8_t physical_address_str[16] = "";
    hex_to_ascii(physical_address, physical_address_str);

    print((uint8_t *)"Memory has been allocated. ", OUTPUT_COLOR);
    print((uint8_t *)"Page: ", OUTPUT_COLOR);
    println(page_str, VARIABLE_COLOR);
    print((uint8_t *)"Physical Address: ", OUTPUT_COLOR);
    println(physical_address_str, VARIABLE_COLOR);
}