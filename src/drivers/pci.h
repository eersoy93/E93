/* DESCRIPTION: E93 PCI Driver Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef PCI_H
#define PCI_H

#include <stddef.h>
#include <stdint.h>

struct pci_device_type_0
{
    uint16_t device_id;
    uint16_t vendor_id;
    uint16_t status;
    uint16_t command;
    uint8_t class_id;
    uint8_t subclass_id;
    uint8_t prog_if;
    uint8_t revision_id;
    uint8_t bist;
    uint8_t header_type;
    uint8_t latency_timer;
    uint8_t cache_line_size;
    uint16_t BAR_O_low;
    uint16_t BAR_O_high;
    uint16_t BAR_1_low;
    uint16_t BAR_1_high;
    uint16_t BAR_2_low;
    uint16_t BAR_2_high;
    uint16_t BAR_3_low;
    uint16_t BAR_3_high;
    uint16_t BAR_4_low;
    uint16_t BAR_4_high;
    uint16_t BAR_5_low;
    uint16_t BAR_5_high;
    uint16_t cardbus_cis_pointer_low;
    uint16_t cardbus_cis_pointer_high;
    uint16_t subsystem_vendor_id;
    uint16_t subsystem_id;
    uint16_t expansion_ROM_base_address_low;
    uint16_t expansion_ROM_base_address_high;
    uint8_t capabilities_pointer;
    uint8_t interrupt_line;
    uint8_t interrupt_pin;
    uint8_t min_grant;
    uint8_t max_latency;
};

uint16_t pci_config_read_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);

uint16_t pci_get_vendor_id(uint8_t bus, uint8_t slot);
uint16_t pci_get_device_id(uint8_t bus, uint8_t slot);

struct pci_device_type_0 pci_get_information_0(uint8_t bus, uint8_t slot);

#endif
