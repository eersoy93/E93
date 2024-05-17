/* DESCRIPTION: E93 PCI Driver Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef PCI_H
#define PCI_H

#include <stddef.h>
#include <stdint.h>

struct pci_device_type_common
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
};

struct pci_device_type_0
{
    struct pci_device_type_common pci_device_info_common_0;
    uint16_t BAR_O_high;
    uint16_t BAR_O_low;
    uint16_t BAR_1_high;
    uint16_t BAR_1_low;
    uint16_t BAR_2_high;
    uint16_t BAR_2_low;
    uint16_t BAR_3_high;
    uint16_t BAR_3_low;
    uint16_t BAR_4_high;
    uint16_t BAR_4_low;
    uint16_t BAR_5_high;
    uint16_t BAR_5_low;
    uint16_t cardbus_cis_pointer_high;
    uint16_t cardbus_cis_pointer_low;
    uint16_t subsystem_id;
    uint16_t subsystem_vendor_id;
    uint16_t expansion_ROM_base_address_high;
    uint16_t expansion_ROM_base_address_low;
    uint8_t capabilities_pointer;
    uint8_t max_latency;
    uint8_t min_grant;
    uint8_t interrupt_pin;
    uint8_t interrupt_line;
};

struct pci_device_type_1
{
    struct pci_device_type_common pci_device_info_common_1;
    uint16_t BAR_0_high;
    uint16_t BAR_0_low;
    uint16_t BAR_1_high;
    uint16_t BAR_1_low;
    uint8_t secondary_latency_timer;
    uint8_t subordinate_bus_number;
    uint8_t secondary_bus_number;
    uint8_t primary_bus_number;
    uint16_t secondary_status;
    uint8_t io_limit;
    uint8_t io_base;
    uint16_t memory_limit;
    uint16_t memory_base;
    uint16_t prefetchable_memory_limit;
    uint16_t prefetchable_memory_base;
    uint16_t prefetchable_base_upper_32_bits_high;
    uint16_t prefetchable_base_upper_32_bits_low;
    uint16_t prefetchable_limit_upper_32_bits_high;
    uint16_t prefetchable_limit_upper_32_bits_low;
    uint16_t io_limit_upper_16_bits;
    uint16_t io_base_upper_16_bits;
    uint8_t capability_pointer;
    uint16_t expansion_ROM_base_address_high;
    uint16_t expansion_ROM_base_address_low;
    uint16_t bridge_control;
    uint8_t interrupt_pin;
    uint8_t interrupt_line;
};

struct pci_device_type_2
{
    struct pci_device_type_common pci_device_info_common_2;
    uint16_t cardbus_socket_base_address_high;
    uint16_t cardbus_socket_base_address_low;
    uint16_t secondary_status;
    uint8_t offset_of_capabilities_list;
    uint8_t cardbus_latency_timer;
    uint8_t subordinate_bus_number;
    uint8_t cardbus_bus_number;
    uint8_t pci_bus_number;
    uint16_t memory_base_address_0_high;
    uint16_t memory_base_address_0_low;
    uint16_t memory_limit_0_high;
    uint16_t memory_limit_0_low;
    uint16_t memory_base_address_1_high;
    uint16_t memory_base_address_1_low;
    uint16_t memory_limit_1_high;
    uint16_t memory_limit_1_low;
    uint16_t io_base_address_0_high;
    uint16_t io_base_address_0_low;
    uint16_t io_limit_0_high;
    uint16_t io_limit_0_low;
    uint16_t io_base_address_1_high;
    uint16_t io_base_address_1_low;
    uint16_t io_limit_1_high;
    uint16_t io_limit_1_low;
    uint16_t bridge_control;
    uint8_t interrupt_pin;
    uint8_t interrupt_line;
    uint16_t subsystem_vendor_id;
    uint16_t subsystem_device_id;
    uint16_t legacy_base_address_high;
    uint16_t legacy_base_address_low;
};

uint16_t pci_config_read_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);

uint16_t pci_get_vendor_id(uint8_t bus, uint8_t slot);
uint16_t pci_get_device_id(uint8_t bus, uint8_t slot);
uint16_t pci_get_status_register(uint8_t bus, uint8_t slot);
uint16_t pci_get_command_register(uint8_t bus, uint8_t slot);
uint8_t pci_get_class_code(uint8_t bus, uint8_t slot);
uint8_t pci_get_subclass_code(uint8_t bus, uint8_t slot);
uint8_t pci_get_prog_if(uint8_t bus, uint8_t slot);
uint8_t pci_get_revision_id(uint8_t bus, uint8_t slot);
uint8_t pci_get_bist(uint8_t bus, uint8_t slot);
uint8_t pci_get_header_type(uint8_t bus, uint8_t slot);
uint8_t pci_get_latency_timer(uint8_t bus, uint8_t slot);
uint8_t pci_get_cache_line_size(uint8_t bus, uint8_t slot);

struct pci_device_type_common pci_get_information_common(uint8_t bus, uint8_t slot);
struct pci_device_type_0 pci_get_information_0(uint8_t bus, uint8_t slot);
struct pci_device_type_1 pci_get_information_1(uint8_t bus, uint8_t slot);
struct pci_device_type_2 pci_get_information_2(uint8_t bus, uint8_t slot);

#endif
