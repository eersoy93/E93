/* DESCRIPTION: E93 C Library String Functions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "string.h"

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

void hex_to_ascii(uint32_t n, char str[])
{
    append(str, '0');
    append(str, 'x');

    char zeroes = 0;
    uint32_t temp = 0;
    for(uint32_t i = 28; i > 0; i -= 4)
    {
        temp = (n >> i) & 0xF;

        if (temp == 0 && zeroes == 0)
        {
            continue;
        }
        zeroes = 1;

        if (temp >= 0xA)
        {
            append(str, temp - 0xA + 'A');
        }
        else
        {
            append(str, temp + '0');
        }
    }

    temp = n & 0xF;
    if (temp >= 0xA)
    {
        append(str, temp - 0xA + 'A');
    }
    else
    {
        append(str, temp + '0');
    }
}

void reverse(char s[])
{
    uint32_t c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

uint16_t strlen(char s[])
{
    uint16_t i = 0;
    while (s[i] != '\0')
    {
        ++i;
    }
    return i;
}

void append(char str[], char n)
{
    uint32_t len = strlen(str);
    str[len] = n;
    str[len + 1] = '\0';
}

void strcat(char str_1[], char str_2[])
{
    uint16_t len_1 = strlen(str_1);
    uint16_t len_2 = strlen(str_2);
    uint16_t i = 0;

    while (i < len_2)
    {
        str_1[len_1 + i] = str_2[i];
        i++;
    }

    str_1[len_1 + i] = '\0';
}

void backspace(char str[])
{
    uint32_t len = strlen(str);
    str[len - 1] = '\0';
}

uint32_t strcmp(char str_1[], char str_2[])
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

void strcpy(char str_1[], char str_2[])
{
    uint32_t i = 0;
    while (str_2[i] != '\0')
    {
        str_1[i] = str_2[i];
        i++;
    }
    str_1[i] = '\0';
}

char * strstr(const char * str, const char * substr)
{
    if (!*substr)
    {
        return (char *)str;
    }

    const char *p1 = str;
    const char *p2 = substr;

    while (*str)
    {
        p1 = str;
        p2 = substr;

        while (*p1 && *p2 && (*p1 == *p2))
        {
            p1++;
            p2++;
        }

        if (!*p2)
        {
            return (char *)str;
        }

        str++;
    }

    return 0;
}

int atoi(const char * str)
{
    int result = 0;
    int sign = 1;
    char ch = 0;

    while (*str == ' ' || *str == '\t' || *str == '\n' ||
           *str == '\v' || *str == '\f' || *str == '\r')
    {
        str++;
    }

    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
    {
        str++;
    }

    while ((ch = *str++) != '\0')
    {
        if (ch >= '0' && ch <= '9')
        {
            result = result * 10 + (ch - '0');
        }
        else
        {
            break;
        }
    }

    return sign * result;
}
