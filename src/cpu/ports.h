/* DESCRIPTION: E93 Port Driver Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef PORTS_H
#define PORTS_H

// Port Driver Declarations

unsigned char port_byte_in(unsigned short port);
void port_byte_out(unsigned short port, unsigned char data);

unsigned short port_word_in(unsigned short port);
void port_word_out(unsigned short port, unsigned short data);

#endif
