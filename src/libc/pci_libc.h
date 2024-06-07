/* DESCRIPTION: E93 C Library PCI Functions Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef PCI_LIBC_H
#define PCI_LIBC_H

#include <stdint.h>

char * get_pci_vendor_str(uint8_t bus, uint8_t slot);
char * get_pci_vendor_and_device_str(uint8_t bus, uint8_t slot);

char * get_pci_vendor_hex_str(uint8_t bus, uint8_t slot);
char * get_pci_device_hex_str(uint8_t bus, uint8_t slot);

uint16_t get_pci_devices_count(void);

void list_pci_devices(void);

#endif
