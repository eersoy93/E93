/* DESCRIPTION: E93 C Library PCI Functions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "pci_libc.h"

#include "../drivers/pci.h"
#include "string.h"

char * get_pci_vendor_str(uint8_t bus, uint8_t slot)
{
    uint16_t vendor_id = pci_get_vendor_id(bus, slot);

    if (vendor_id != 0xffff)
    {
        switch (vendor_id)
        {
            case 0x8086:
            {
                return "Intel Corporation";
            }
            default:
            {
                return "Unknown Vendor";
            }
        }
    }
    else
    {
        return "No Device";
    }
}

char * get_pci_vendor_and_device_str(uint8_t bus, uint8_t slot)
{
    uint16_t vendor_id = pci_get_vendor_id(bus, slot);
    uint16_t device_id = pci_get_device_id(bus, slot);

    if (vendor_id != 0xffff && device_id != 0xffff)
    {
        switch (vendor_id)
        {
            case 0x8086:
            {
                switch (device_id)
                {
                    case 0x1237:
                    {
                        return "Intel Corporation 440FX - 82441FX PMC [Natoma]";
                    }
                    default:
                    {
                        return "Unknown Vendor and Device";
                    }
                }
            }
            default:
            {
                return "Unknown Vendor and Device";
            }
        }
    }
    else
    {
        return "No Device";
    }
}

char * get_pci_vendor_hex_str(uint8_t bus, uint8_t slot)
{
    uint16_t vendor_id = pci_get_vendor_id(bus, slot);

    if (vendor_id != 0xffff)
    {
        char * hex_str = "0x";
        char * hex_str_vendor_id = "";

        hex_to_ascii(vendor_id, hex_str_vendor_id);

        append_str(hex_str, hex_str_vendor_id);

        return hex_str;
    }
    else
    {
        return "No Device";
    }
}

char * get_pci_device_hex_str(uint8_t bus, uint8_t slot)
{
    uint16_t device_id = pci_get_device_id(bus, slot);

    if (device_id != 0xffff)
    {
        char * hex_str = "0x";
        char * hex_str_device_id = "";

        hex_to_ascii(device_id, hex_str_device_id);

        append_str(hex_str, hex_str_device_id);

        return hex_str;
    }
    else
    {
        return "No Device";
    }
}
