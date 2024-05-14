/* DESCRIPTION: E93 PCI Driver Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef PCI_H
#define PCI_H

#include <stddef.h>
#include <stdint.h>

struct pci_device_type
{
    uint8_t bus;
    uint8_t slot;
    uint16_t vendor;
    uint16_t device;
    uint8_t pci_class_id;
    uint8_t pci_subclass_id;
    uint8_t pci_prog_if;
    uint8_t pci_header_type;
    uint8_t irq;
};

uint16_t pci_config_read_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
uint16_t pci_check_vendor(uint8_t bus, uint8_t slot);

#endif
