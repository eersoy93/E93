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

struct pci_device_type_0 pci_get_information_0(uint8_t bus, uint8_t slot)
{
    uint16_t vendor_id = pci_get_vendor_id(bus, slot);

    if (vendor_id != 0xffff)
    {
        uint16_t device_id = pci_get_device_id(bus, slot);
        uint16_t status = pci_config_read_word(bus, slot, 0, 6);
        uint16_t command = pci_config_read_word(bus, slot, 0, 4);

        uint8_t class_id = (pci_config_read_word(bus, slot, 0, 0xa) >> 8) & 0xff;
        uint8_t subclass_id = pci_config_read_word(bus, slot, 0, 0xa) & 0xff;

        uint8_t prog_if = (pci_config_read_word(bus, slot, 0, 8) >> 8) & 0xff;
        uint8_t revision_id = pci_config_read_word(bus, slot, 0, 8) & 0xff;


        uint8_t bist = (pci_config_read_word(bus, slot, 0, 0xe) >> 8) & 0xff;
        uint8_t header_type = pci_config_read_word(bus, slot, 0, 0xe) & 0xff;

        uint8_t latency_timer = (pci_config_read_word(bus, slot, 0, 0x0c) >> 8) & 0xff;
        uint8_t cache_line_size = pci_config_read_word(bus, slot, 0, 0x0c) & 0xff;

        if (header_type == 0)
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

            uint8_t interrupt_line = pci_config_read_word(bus, slot, 0, 0x3c) & 0xff;
            uint8_t interrupt_pin = (pci_config_read_word(bus, slot, 0, 0x3c) >> 8) & 0xff;
            uint8_t min_grant = pci_config_read_word(bus, slot, 0, 0x3e) & 0xff;
            uint8_t max_latency = (pci_config_read_word(bus, slot, 0, 0x3e) >> 8) & 0xff;

            struct pci_device_type_0 pci_device =
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
                cache_line_size,
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
                interrupt_line,
                interrupt_pin,
                min_grant,
                max_latency
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
