/* DESCRIPTION: E93 Driver Utility Definitions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "drvutils.h"

void int_to_ascii(int32_t n, char str[])
{
    int32_t i = 0;
    int32_t sign = n;

    if (sign < 0)
    {
        n = -n;
    }

    do
    {
        str[i++] = n % 10 + '0';
    } while((n /= 10) > 0);

    if (sign < 0)
    {
        str[i++] = '-';
    }

    str[i] = '\0';

    reverse(str);
}

void reverse(char str[])
{
    uint32_t c, i, j;

    for (i = 0, j = strlen(str) - 1; i < j; i++, j--)
    {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

uint16_t strlen(char str[])
{
    uint16_t i = 0;
    while (str[i] != '\0')
    {
        ++i;
    }
    return i;
}

void memory_copy(uint8_t * source, uint8_t * destination, uint32_t n_bytes)
{
    uint32_t i = 0;
    for (i = 0; i < n_bytes; i++)
    {
        *(destination + i) = *(source + i);
    }
}
