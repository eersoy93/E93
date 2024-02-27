/* DESCRIPTION: E93 PCI Driver Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "pci.h"

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
    uint16_t vendor, device;

    if ((vendor = pci_config_read_word(bus, slot, 0, 0)) != 0xffff)
    {
        device = pci_config_read_word(bus, slot, 0, 2);
    }

    return vendor;
}
