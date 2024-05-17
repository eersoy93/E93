/* DESCRIPTION: E93 PCI Driver Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "pci.h"

#include "../cpu/drvutils.h"
#include "../cpu/ports.h"

uint16_t pci_config_read_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
{
    uint32_t lbus = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;

    uint32_t address = (uint32_t)((lbus << 16) | (lslot << 11) |
                                  (lfunc << 8) | (offset & 0xfc) |
                                  ((uint32_t)0x80000000));

    port_dword_out(0xcf8, address);
    uint32_t temp = (uint16_t)((port_dword_in(0xcfc) >> ((offset & 2) * 8)) & 0xffff);
    return temp;
}

uint16_t pci_get_vendor_id(uint8_t bus, uint8_t slot)
{
    uint16_t vendor_id = pci_config_read_word(bus, slot, 0, 0);

    return vendor_id;
}

uint16_t pci_get_device_id(uint8_t bus, uint8_t slot)
{
    uint16_t device_id = pci_config_read_word(bus, slot, 0, 2);

    return device_id;
}

uint16_t pci_get_status_register(uint8_t bus, uint8_t slot)
{
    uint16_t status = pci_config_read_word(bus, slot, 0, 6);

    return status;
}

uint16_t pci_get_command_register(uint8_t bus, uint8_t slot)
{
    uint16_t command = pci_config_read_word(bus, slot, 0, 4);

    return command;
}

uint8_t pci_get_class_code(uint8_t bus, uint8_t slot)
{
    uint8_t class_code = (pci_config_read_word(bus, slot, 0, 0xa) >> 8) & 0xff;

    return class_code;
}

uint8_t pci_get_subclass_code(uint8_t bus, uint8_t slot)
{
    uint8_t subclass_code = pci_config_read_word(bus, slot, 0, 0xa) & 0xff;

    return subclass_code;
}

uint8_t pci_get_prog_if(uint8_t bus, uint8_t slot)
{
    uint8_t prog_if = (pci_config_read_word(bus, slot, 0, 8) >> 8) & 0xff;

    return prog_if;
}

uint8_t pci_get_revision_id(uint8_t bus, uint8_t slot)
{
    uint8_t revision_id = pci_config_read_word(bus, slot, 0, 8) & 0xff;

    return revision_id;
}

uint8_t pci_get_bist(uint8_t bus, uint8_t slot)
{
    uint8_t bist = (pci_config_read_word(bus, slot, 0, 0xe) >> 8) & 0xff;

    return bist;
}

uint8_t pci_get_header_type(uint8_t bus, uint8_t slot)
{
    uint8_t header_type = pci_config_read_word(bus, slot, 0, 0xe) & 0xff;

    return header_type;
}

uint8_t pci_get_latency_timer(uint8_t bus, uint8_t slot)
{
    uint8_t latency_timer = (pci_config_read_word(bus, slot, 0, 0xc) >> 8) & 0xff;

    return latency_timer;
}

uint8_t pci_get_cache_line_size(uint8_t bus, uint8_t slot)
{
    uint8_t cache_line_size = pci_config_read_word(bus, slot, 0, 0xc) & 0xff;

    return cache_line_size;
}

struct pci_device_type_common pci_get_information_common(uint8_t bus, uint8_t slot)
{
    uint16_t vendor_id = pci_get_vendor_id(bus, slot);

    if (vendor_id != 0xffff)
    {
        uint16_t device_id = pci_get_device_id(bus, slot);
        uint16_t status = pci_get_status_register(bus, slot);
        uint16_t command = pci_get_command_register(bus, slot);

        uint8_t class_id = pci_get_class_code(bus, slot);
        uint8_t subclass_id = pci_get_subclass_code(bus, slot);

        uint8_t prog_if = pci_get_prog_if(bus, slot);
        uint8_t revision_id = pci_get_revision_id(bus, slot);

        uint8_t bist = pci_get_bist(bus, slot);
        uint8_t header_type = pci_get_header_type(bus, slot);

        uint8_t latency_timer = pci_get_latency_timer(bus, slot);
        uint8_t cache_line_size = pci_get_cache_line_size(bus, slot);

        struct pci_device_type_common pci_device =
        {
            device_id,
            vendor_id,
            status,
            command,
            class_id,
            subclass_id,
            prog_if,
            revision_id,
            bist,
            header_type,
            latency_timer,
            cache_line_size
        };

        return pci_device;
    }
    else
    {
        return (struct pci_device_type_common){0};
    }
}

struct pci_device_type_0 pci_get_information_0(uint8_t bus, uint8_t slot)
{
    uint16_t vendor_id = pci_get_vendor_id(bus, slot);

    if (vendor_id != 0xffff)
    {
        struct pci_device_type_common pci_device_common = pci_get_information_common(bus, slot);

        if (pci_device_common.header_type == 0)
        {
            uint16_t BAR0_low = pci_config_read_word(bus, slot, 0, 0x10);
            uint16_t BAR0_high = pci_config_read_word(bus, slot, 0, 0x12);

            uint16_t BAR1_low = pci_config_read_word(bus, slot, 0, 0x14);
            uint16_t BAR1_high = pci_config_read_word(bus, slot, 0, 0x16);

            uint16_t BAR2_low = pci_config_read_word(bus, slot, 0, 0x18);
            uint16_t BAR2_high = pci_config_read_word(bus, slot, 0, 0x1a);

            uint16_t BAR3_low = pci_config_read_word(bus, slot, 0, 0x1c);
            uint16_t BAR3_high = pci_config_read_word(bus, slot, 0, 0x1e);

            uint16_t BAR4_low = pci_config_read_word(bus, slot, 0, 0x20);
            uint16_t BAR4_high = pci_config_read_word(bus, slot, 0, 0x22);

            uint16_t BAR5_low = pci_config_read_word(bus, slot, 0, 0x24);
            uint16_t BAR5_high = pci_config_read_word(bus, slot, 0, 0x26);

            uint16_t cardbus_cis_pointer_low = pci_config_read_word(bus, slot, 0, 0x28);
            uint16_t cardbus_cis_pointer_high = pci_config_read_word(bus, slot, 0, 0x2a);

            uint16_t subsystem_vendor_id = pci_config_read_word(bus, slot, 0, 0x2c);
            uint16_t subsystem_id = pci_config_read_word(bus, slot, 0, 0x2e);

            uint16_t expansion_rom_base_address_low = pci_config_read_word(bus, slot, 0, 0x30);
            uint16_t expansion_rom_base_address_high = pci_config_read_word(bus, slot, 0, 0x32);

            uint8_t capabilities_pointer = pci_config_read_word(bus, slot, 0, 0x34) & 0xff;

            uint8_t max_latency = (pci_config_read_word(bus, slot, 0, 0x3e) >> 8) & 0xff;
            uint8_t min_grant = pci_config_read_word(bus, slot, 0, 0x3e) & 0xff;
            uint8_t interrupt_pin = (pci_config_read_word(bus, slot, 0, 0x3c) >> 8) & 0xff;
            uint8_t interrupt_line = pci_config_read_word(bus, slot, 0, 0x3c) & 0xff;

            struct pci_device_type_0 pci_device =
            {
                pci_device_common,
                BAR0_low,
                BAR0_high,
                BAR1_low,
                BAR1_high,
                BAR2_low,
                BAR2_high,
                BAR3_low,
                BAR3_high,
                BAR4_low,
                BAR4_high,
                BAR5_low,
                BAR5_high,
                cardbus_cis_pointer_low,
                cardbus_cis_pointer_high,
                subsystem_vendor_id,
                subsystem_id,
                expansion_rom_base_address_low,
                expansion_rom_base_address_high,
                capabilities_pointer,
                max_latency,
                min_grant,
                interrupt_pin,
                interrupt_line
            };

            return pci_device;
        }
        else
        {
            return (struct pci_device_type_0){0};
        }
    }
    else
    {
        return (struct pci_device_type_0){0};
    }
}

struct pci_device_type_1 pci_get_information_1(uint8_t bus, uint8_t slot)
{
    uint16_t vendor_id = pci_get_vendor_id(bus, slot);

    if (vendor_id != 0xffff)
    {
        struct pci_device_type_common pci_device_common = pci_get_information_common(bus, slot);

        if (pci_device_common.header_type == 1)
        {
            uint16_t BAR0_high = pci_config_read_word(bus, slot, 0, 0x12);
            uint16_t BAR0_low = pci_config_read_word(bus, slot, 0, 0x10);

            uint16_t BAR1_high = pci_config_read_word(bus, slot, 0, 0x16);
            uint16_t BAR1_low = pci_config_read_word(bus, slot, 0, 0x14);

            uint8_t secondary_latency_timer = pci_config_read_word(bus, slot, 0, 0x1b) & 0xff;
            uint8_t subordinate_bus_number = (pci_config_read_word(bus, slot, 0, 0x1a) >> 8) & 0xff;
            uint8_t secondary_bus_number = (pci_config_read_word(bus, slot, 0, 0x18) >> 8) & 0xff;
            uint8_t primary_bus_number = pci_config_read_word(bus, slot, 0, 0x18) & 0xff;

            uint16_t secondary_status = pci_config_read_word(bus, slot, 0, 0x1e);
            uint8_t io_limit = (pci_config_read_word(bus, slot, 0, 0x1c) >> 8) & 0xff;
            uint8_t io_base = pci_config_read_word(bus, slot, 0, 0x1c) & 0xff;

            uint16_t memory_limit = pci_config_read_word(bus, slot, 0, 0x22);
            uint16_t memory_base = pci_config_read_word(bus, slot, 0, 0x20);

            uint16_t prefetchable_memory_limit = pci_config_read_word(bus, slot, 0, 0x26);
            uint16_t prefetchable_memory_base = pci_config_read_word(bus, slot, 0, 0x24);

            uint16_t prefetchable_base_upper_32_bits_high = pci_config_read_word(bus, slot, 0, 0x2a);
            uint16_t prefetchable_base_upper_32_bits_low = pci_config_read_word(bus, slot, 0, 0x28);

            uint16_t prefetchable_limit_upper_32_bits_high = pci_config_read_word(bus, slot, 0, 0x2e);
            uint16_t prefetchable_limit_upper_32_bits_low = pci_config_read_word(bus, slot, 0, 0x2c);

            uint16_t io_base_upper_16_bits = pci_config_read_word(bus, slot, 0, 0x32);
            uint16_t io_limit_upper_16_bits = pci_config_read_word(bus, slot, 0, 0x30);

            uint8_t capability_pointer = pci_config_read_word(bus, slot, 0, 0x34) & 0xff;

            uint16_t expansion_ROM_base_address_high = pci_config_read_word(bus, slot, 0, 0x3a);
            uint16_t expansion_ROM_base_address_low = pci_config_read_word(bus, slot, 0, 0x38);

            uint16_t bridge_control = pci_config_read_word(bus, slot, 0, 0x3e);
            uint8_t interrupt_pin = (pci_config_read_word(bus, slot, 0, 0x3c) >> 8) & 0xff;
            uint8_t interrupt_line = pci_config_read_word(bus, slot, 0, 0x3c) & 0xff;

            struct pci_device_type_1 pci_device =
            {
                pci_device_common,
                BAR0_high,
                BAR0_low,
                BAR1_high,
                BAR1_low,
                secondary_latency_timer,
                subordinate_bus_number,
                secondary_bus_number,
                primary_bus_number,
                secondary_status,
                io_limit,
                io_base,
                memory_limit,
                memory_base,
                prefetchable_memory_limit,
                prefetchable_memory_base,
                prefetchable_base_upper_32_bits_high,
                prefetchable_base_upper_32_bits_low,
                prefetchable_limit_upper_32_bits_high,
                prefetchable_limit_upper_32_bits_low,
                io_limit_upper_16_bits,
                io_base_upper_16_bits,
                capability_pointer,
                expansion_ROM_base_address_high,
                expansion_ROM_base_address_low,
                bridge_control,
                interrupt_pin,
                interrupt_line
            };

            return pci_device;
        }
        else
        {
            return (struct pci_device_type_1){0};
        }
    }
    else
    {
        return (struct pci_device_type_1){0};
    }
}

struct pci_device_type_2 pci_get_information_2(uint8_t bus, uint8_t slot)
{
    uint16_t vendor_id = pci_get_vendor_id(bus, slot);

    if (vendor_id != 0xffff)
    {
        struct pci_device_type_common pci_device_common = pci_get_information_common(bus, slot);

        if (pci_device_common.header_type == 1)
        {
            uint16_t cardbus_socket_base_address_high = pci_config_read_word(bus, slot, 0, 0x12);
            uint16_t cardbus_socket_base_address_low = pci_config_read_word(bus, slot, 0, 0x10);

            uint16_t secondary_status = pci_config_read_word(bus, slot, 0, 0x16);
            uint8_t offset_of_capabilities_list = pci_config_read_word(bus, slot, 0, 0x14) & 0xff;

            uint8_t cardbus_latency_timer = (pci_config_read_word(bus, slot, 0, 0x1a) >> 8) & 0xff;
            uint8_t subordinate_bus_number = pci_config_read_word(bus, slot, 0, 0x1a) & 0xff;
            uint8_t cardbus_bus_number = (pci_config_read_word(bus, slot, 0, 0x18) >> 8) & 0xff;
            uint8_t pci_bus_number = pci_config_read_word(bus, slot, 0, 0x18) & 0xff;

            uint16_t memory_base_address_0_high = pci_config_read_word(bus, slot, 0, 0x1e);
            uint16_t memory_base_address_0_low = pci_config_read_word(bus, slot, 0, 0x1c);

            uint16_t memory_limit_0_high = pci_config_read_word(bus, slot, 0, 0x22);
            uint16_t memory_limit_0_low = pci_config_read_word(bus, slot, 0, 0x20);

            uint16_t memory_base_address_1_high = pci_config_read_word(bus, slot, 0, 0x26);
            uint16_t memory_base_address_1_low = pci_config_read_word(bus, slot, 0, 0x24);

            uint16_t memory_limit_1_high = pci_config_read_word(bus, slot, 0, 0x2a);
            uint16_t memory_limit_1_low = pci_config_read_word(bus, slot, 0, 0x28);

            uint16_t io_base_address_0_high = pci_config_read_word(bus, slot, 0, 0x2e);
            uint16_t io_base_address_0_low = pci_config_read_word(bus, slot, 0, 0x2c);

            uint16_t io_limit_0_high = pci_config_read_word(bus, slot, 0, 0x32);
            uint16_t io_limit_0_low = pci_config_read_word(bus, slot, 0, 0x30);

            uint16_t io_base_address_1_high = pci_config_read_word(bus, slot, 0, 0x36);
            uint16_t io_base_address_1_low = pci_config_read_word(bus, slot, 0, 0x34);

            uint16_t io_limit_1_high = pci_config_read_word(bus, slot, 0, 0x3a);
            uint16_t io_limit_1_low = pci_config_read_word(bus, slot, 0, 0x38);

            uint16_t bridge_control = pci_config_read_word(bus, slot, 0, 0x3e);
            uint8_t interrupt_pin = (pci_config_read_word(bus, slot, 0, 0x3c) >> 8) & 0xff;
            uint8_t interrupt_line = pci_config_read_word(bus, slot, 0, 0x3c) & 0xff;

            uint16_t subsystem_vendor_id = pci_config_read_word(bus, slot, 0, 0x42);
            uint16_t subsystem_device_id = pci_config_read_word(bus, slot, 0, 0x40);

            uint16_t legacy_base_address_high = pci_config_read_word(bus, slot, 0, 0x46);
            uint16_t legacy_base_address_low = pci_config_read_word(bus, slot, 0, 0x44);

            struct pci_device_type_2 pci_device =
            {
                pci_device_common,
                cardbus_socket_base_address_high,
                cardbus_socket_base_address_low,
                secondary_status,
                offset_of_capabilities_list,
                cardbus_latency_timer,
                subordinate_bus_number,
                cardbus_bus_number,
                pci_bus_number,
                memory_base_address_0_high,
                memory_base_address_0_low,
                memory_limit_0_high,
                memory_limit_0_low,
                memory_base_address_1_high,
                memory_base_address_1_low,
                memory_limit_1_high,
                memory_limit_1_low,
                io_base_address_0_high,
                io_base_address_0_low,
                io_limit_0_high,
                io_limit_0_low,
                io_base_address_1_high,
                io_base_address_1_low,
                io_limit_1_high,
                io_limit_1_low,
                bridge_control,
                interrupt_pin,
                interrupt_line,
                subsystem_vendor_id,
                subsystem_device_id,
                legacy_base_address_high,
                legacy_base_address_low
            };

            return pci_device;
        }
        else
        {
            return (struct pci_device_type_2){0};
        }
    }
    else
    {
        return (struct pci_device_type_2){0};
    }
}
