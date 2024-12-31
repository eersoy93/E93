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

int32_t strcmp(char str_1[], char str_2[])
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

char * strstr(char str[], char substr[])
{
    if (!(substr[0]))
    {
        return (char *)str;
    }

    for (int32_t i = 0; i < strlen(str); i++)
    {
        if (str[i] == substr[0])
        {
            int32_t j = 0;
            while (str[i + j] == substr[j])
            {
                j++;

                if (substr[j] == '\0')
                {
                    return (char *)&str[i];
                }
            }
        }
    }

    return 0;
}

char * strchr(char str[], int c)
{
    while (*str != '\0')
    {
        if (*str == (char)c)
        {
            return str;
        }

        str++;
    }

    return NULL;
}

char * strtok(char str[], char delim[])
{
    static char * last;

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

    char * token_start = str;

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

    return token_start;
}

int atoi(char str[])
{
    uint32_t result = 0;
    uint32_t sign = 1;
    uint8_t ch = 0;
    uint32_t i = 0;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
           str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
    {
        i++;
    }

    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (str[i] == '+')
    {
        i++;
    }

    while ((ch = str[i++]) != '\0')
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
