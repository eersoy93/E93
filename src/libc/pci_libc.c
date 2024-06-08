/* DESCRIPTION: E93 C Library PCI Functions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "pci_libc.h"

#include "../drivers/pci.h"
#include "io.h"
#include "string.h"

char * get_pci_vendor_str(uint8_t bus, uint8_t slot)
{
    uint16_t vendor_id = pci_get_vendor_id(bus, slot);

    if (vendor_id != 0xffff)
    {
        switch (vendor_id)
        {
            case 0x1234:
            {
                return "QEMU";
            }
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
            case 0x1234:
            {
                switch (device_id)
                {
                    case 0x1111:
                    {
                        return "QEMU Virtual Video Controller (-vga=std)";
                    }
                    default:
                    {
                        return "Unknown Vendor and Device";
                    }
                }
            }
            case 0x8086:
            {
                switch (device_id)
                {
                    case 0x100E:
                    {
                        return "Intel Corporation 82540EM Gigabit Ethernet Controller";
                    }
                    case 0x1237:
                    {
                        return "Intel Corporation 440FX - 82441FX PMC [Natoma]";
                    }
                    case 0x7000:
                    {
                        return "Intel Corporation 82371SB PIIX3 ISA [Natoma/Triton II]";
                    }
                    case 0x7030:
                    {
                        return "Intel Corporation 430VX - 82437VX TVX [Triton VX]";
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

uint16_t get_pci_devices_count(void)
{
    uint16_t count = 0;

    for (uint8_t bus = 0; bus < 255; bus++)
    {
        for (uint8_t slot = 0; slot < 32; slot++)
        {
            uint16_t vendor_id = pci_get_vendor_id(bus, slot);

            if (vendor_id != 0xffff)
            {
                count++;
            }
        }
    }

    return count;
}

void list_pci_devices(void)
{
    uint16_t pci_devices_count = 0;

    for (uint16_t bus = 0; bus < 256; bus++)
    {
        for (uint8_t slot = 0; slot < 32; slot++)
        {
            uint16_t vendor_id = pci_get_vendor_id(bus, slot);

            if (vendor_id != 0xffff)
            {
                uint16_t vendor_id = pci_get_vendor_id(bus, slot);
                uint16_t device_id = pci_get_device_id(bus, slot);

                char vendor_hex_str[7] = "";
                char device_hex_str[7] = "";

                hex_to_ascii(vendor_id, vendor_hex_str);
                hex_to_ascii(device_id, device_hex_str);

                char * vendor_and_device_str = get_pci_vendor_and_device_str(bus, slot);

                char line_to_print[256] = "";
                strcat(line_to_print, vendor_hex_str);
                append(line_to_print, ':');
                strcat(line_to_print, device_hex_str);
                append(line_to_print, ' ');
                strcat(line_to_print, vendor_and_device_str);

                println(line_to_print, OUTPUT_COLOR);

                pci_devices_count++;
            }
        }
    }

    char line_to_print_2[20] = "PCI Devices Count: ";

    char pci_devices_count_str[5] = "";

    int_to_ascii(pci_devices_count, pci_devices_count_str);
    strcat(line_to_print_2, pci_devices_count_str);

    println("", OUTPUT_COLOR);
    println(line_to_print_2, OUTPUT_COLOR);
}
