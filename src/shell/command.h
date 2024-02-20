/* DESCRIPTION: E93 Shell Commands Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <stddef.h>
#include <stdint.h>

struct command
{
    uint8_t command_no;
    char * command_name;
    char * command_help;
    void (* command_function)(void);
};

void commands_help(void);
void command_execute(char * input_command);

#endif
