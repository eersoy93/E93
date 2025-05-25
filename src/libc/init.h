/* DESCRIPTION: E93 C Library Shell Init Function Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with GPLv2 License. See LICENSE file for details.
 */

#ifndef INIT_H
#define INIT_H

#include <stdint.h>

#define CLI_MODE 0
#define GUI_MODE 1

void init(uint8_t mode);

#endif