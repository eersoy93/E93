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

uint16_t pci_check_vendor(uint8_t bus, uint8_t slot)
{
    uint16_t vendor = 0x0000;
    uint16_t device = 0x0000;

    if ((vendor = pci_config_read_word(bus, slot, 0, 0)) != 0xffff)
    {
        device = pci_config_read_word(bus, slot, 0, 2);
        UNUSED(device);
    }

    return vendor;
}

void pci_check_device(uint8_t bus, uint8_t slot, uint16_t vendor)
{
    uint16_t device = pci_config_read_word(bus, slot, 0, 2);

    if (vendor != 0xffff)
    {
        uint8_t pci_class_id = pci_config_read_word(bus, slot, 0, 0xa) & 0xff;
        uint8_t pci_subclass_id = pci_config_read_word(bus, slot, 0, 0xa) >> 8;

        uint8_t pci_prog_if = pci_config_read_word(bus, slot, 0, 0x9) & 0xff;

        uint8_t pci_header_type = pci_config_read_word(bus, slot, 0, 0xe) & 0xff;

        if (pci_header_type == 0)
        {
            uint8_t irq = pci_config_read_word(bus, slot, 0, 0x3c) & 0xff;

            struct pci_device_type pci_device =
            {
                .bus = bus,
                .slot = slot,
                .vendor = vendor,
                .device = device,
                .pci_class_id = pci_class_id,
                .pci_subclass_id = pci_subclass_id,
                .pci_prog_if = pci_prog_if,
                .irq = irq
            };

            UNUSED(pci_device);
        }
    }
}

void pci_check_all_devices(void)
{
    for (uint8_t bus = 0; bus < 8; bus++)
    {
        for (uint8_t slot = 0; slot < 32; slot++)
        {
            uint16_t vendor = pci_check_vendor(bus, slot);

            pci_check_device(bus, slot, vendor);
        }
    }
}
