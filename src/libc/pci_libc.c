/* DESCRIPTION: E93 C Library PCI Functions Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "pci_libc.h"

#include "../drivers/pci.h"
#include "io.h"
#include "string.h"

uint8_t * get_pci_vendor_str(uint8_t bus, uint8_t slot)
{
    uint16_t vendor_id = pci_get_vendor_id(bus, slot);

    if (vendor_id != 0xffff)
    {
        switch (vendor_id)
        {
            case 0x1234:
            {
                return (uint8_t *)"QEMU";
            }
            case 0x8086:
            {
                return (uint8_t *)"Intel Corporation";
            }
            default:
            {
                return (uint8_t *)"Unknown Vendor";
            }
        }
    }
    else
    {
        return (uint8_t *)"No Device";
    }
}

uint8_t * get_pci_vendor_and_device_str(uint8_t bus, uint8_t slot)
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
                        return (uint8_t *)"QEMU Virtual Video Controller (-vga=std)";
                    }
                    default:
                    {
                        return (uint8_t *)"Unknown Vendor and Device";
                    }
                }
            }
            case 0x8086:
            {
                switch (device_id)
                {
                    case 0x100E:
                    {
                        return (uint8_t *)"Intel Corporation 82540EM Gigabit Ethernet Controller";
                    }
                    case 0x1237:
                    {
                        return (uint8_t *)"Intel Corporation 440FX - 82441FX PMC [Natoma]";
                    }
                    case 0x7000:
                    {
                        return (uint8_t *)"Intel Corporation 82371SB PIIX3 ISA [Natoma/Triton II]";
                    }
                    case 0x7030:
                    {
                        return (uint8_t *)"Intel Corporation 430VX - 82437VX TVX [Triton VX]";
                    }
                    default:
                    {
                        return (uint8_t *)"Unknown Vendor and Device";
                    }
                }
            }
            default:
            {
                return (uint8_t *)"Unknown Vendor and Device";
            }
        }
    }
    else
    {
        return (uint8_t *)"No Device";
    }
}

void get_pci_vendor_hex_str(uint8_t bus, uint8_t slot, uint8_t * vendor_id_str)
{
    uint16_t vendor_id = pci_get_vendor_id(bus, slot);

    hex_to_ascii(vendor_id, vendor_id_str);

    append(vendor_id_str, '\0');
}

void get_pci_device_hex_str(uint8_t bus, uint8_t slot, uint8_t * device_id_str)
{
    uint16_t device_id = pci_get_device_id(bus, slot);

    hex_to_ascii(device_id, device_id_str);

    append(device_id_str, '\0');
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

                uint8_t vendor_hex_str[7] = "";
                uint8_t device_hex_str[7] = "";

                hex_to_ascii(vendor_id, vendor_hex_str);
                hex_to_ascii(device_id, device_hex_str);

                uint8_t * vendor_and_device_str = get_pci_vendor_and_device_str(bus, slot);

                uint8_t line_to_print[256] = "";
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

    uint8_t line_to_print_2[20] = "PCI Devices Count: ";

    uint8_t pci_devices_count_str[5] = "";

    int_to_ascii(pci_devices_count, pci_devices_count_str);
    strcat(line_to_print_2, pci_devices_count_str);

    println((uint8_t *)"", OUTPUT_COLOR);
    println(line_to_print_2, OUTPUT_COLOR);
}
