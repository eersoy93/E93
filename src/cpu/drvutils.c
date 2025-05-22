/* DESCRIPTION: E93 Driver Utility Definitions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "drvutils.h"

void int_to_ascii(int32_t n, uint8_t str[])
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

void reverse(uint8_t str[])
{
    uint32_t c, i, j;

    for (i = 0, j = strlen(str) - 1; i < j; i++, j--)
    {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

uint16_t strlen(uint8_t str[])
{
    uint16_t i = 0;
    while (str[i] != '\0')
    {
        ++i;
    }
    return i;
}

uint8_t * strchr(uint8_t str[], int32_t c)
{
    while (*str != '\0')
    {
        if (*str == c)
        {
            return (uint8_t *)str;
        }

        str++;
    }

    return NULL;
}

uint8_t * strtok(uint8_t str[], uint8_t delim[])
{
    static uint8_t *last;
    if (str == NULL)
    {
        str = last;
    }
    if (str == NULL)
    {
        return NULL;
    }

    // Skip leading delimiters
    while (*str && strchr(delim, *str))
    {
        str++;
    }

    if (*str == '\0')
    {
        last = NULL;
        return NULL;
    }

    uint8_t * token = str;

    // Find the end of the token
    while (*str && !strchr(delim, *str))
    {
        str++;
    }

    if (*str)
    {
        *str = '\0';
        last = str + 1;
    }
    else
    {
        last = NULL;
    }

    return token;
}

int32_t strcmp(uint8_t str_1[], uint8_t str_2[])
{
    uint32_t i = 0;
    for (i = 0; str_1[i] == str_2[i]; i++)
    {
        if (str_1[i] == '\0')
        {
            return 0;
        }
    }
    return str_1[i] - str_2[i];
}

void memcpy(uint8_t * source, uint8_t * destination, uint32_t n_bytes)
{
    uint32_t i = 0;
    for (i = 0; i < n_bytes; i++)
    {
        *(destination + i) = *(source + i);
    }
}
