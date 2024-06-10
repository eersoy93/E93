/* DESCRIPTION: E93 IDE Driver Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "../cpu/drvutils.h"
#include "../cpu/ports.h"
#include "pci.h"

#include "ide.h"

uint8_t ide_read(uint8_t channel, uint8_t reg)
{
    uint8_t result = 0;

    if (reg > 0x07 && reg < 0x0C)
    {
        ide_write(channel, ATA_REG_CONTROL, 0x80 | IDEChannels[channel].nIEN);
    }
    if (reg < 0x08)
    {
        result = port_byte_in(IDEChannels[channel].base + reg - 0x00);
    }
    else if (reg < 0x0C)
    {
        result = port_byte_in(IDEChannels[channel].base + reg - 0x06);
    }
    else if (reg < 0x0E)
    {
        result = port_byte_in(IDEChannels[channel].ctrl + reg - 0x0A);
    }
    else if (reg < 0x16)
    {
        result = port_byte_in(IDEChannels[channel].bmide + reg - 0x0E);
    }
    if (reg > 0x07 && reg < 0x0C)
    {
        ide_write(channel, ATA_REG_CONTROL, IDEChannels[channel].nIEN);
    }

    return result;
}

void ide_write(uint8_t channel, uint8_t reg, uint8_t data)
{
    if (reg > 0x07 && reg < 0x0C)
    {
        ide_write(channel, ATA_REG_CONTROL, 0x80 | IDEChannels[channel].nIEN);
    }
    if (reg < 0x08)
    {
        port_byte_out(IDEChannels[channel].base + reg - 0x00, data);
    }
    else if (reg < 0x0C)
    {
        port_byte_out(IDEChannels[channel].base + reg - 0x06, data);
    }
    else if (reg < 0x0E)
    {
        port_byte_out(IDEChannels[channel].ctrl + reg - 0x0A, data);
    }
    else if (reg < 0x16)
    {
        port_byte_out(IDEChannels[channel].bmide + reg - 0x0E, data);
    }
    if (reg > 0x07 && reg < 0x0C)
    {
        ide_write(channel, ATA_REG_CONTROL, IDEChannels[channel].nIEN);
    }
}

void ide_read_buffer(uint8_t channel, uint8_t reg, uint32_t buffer, uint32_t quads)
{
    if (reg > 0x07 && reg < 0x0C)
    {
        ide_write(channel, ATA_REG_CONTROL, 0x80 | IDEChannels[channel].nIEN);
    }

    __asm__ volatile("pushw %%es; movw %%ds, %%ax; movw %%ax, %%es" : : : "ax");

    if (reg < 0x08)
    {
        uint32_t * buf = (uint32_t *)buffer;
        for (uint32_t i = 0; i < quads; i++)
        {
            buf[i] = port_dword_in(IDEChannels[channel].base + reg - 0x00);
        }
    }
    else if (reg < 0x0C)
    {
        uint32_t * buf = (uint32_t *)buffer;
        for (uint32_t i = 0; i < quads; i++)
        {
            buf[i] = port_dword_in(IDEChannels[channel].base + reg - 0x06);
        }
    }
    else if (reg < 0x0E)
    {
        uint32_t * buf = (uint32_t *)buffer;
        for (uint32_t i = 0; i < quads; i++)
        {
            buf[i] = port_dword_in(IDEChannels[channel].ctrl + reg - 0x0A);
        }
    }
    else if (reg < 0x16)
    {
        uint32_t * buf = (uint32_t *)buffer;
        for (uint32_t i = 0; i < quads; i++)
        {
            buf[i] = port_dword_in(IDEChannels[channel].bmide + reg - 0x0E);
        }
    }

    __asm__ volatile("popw %%es" : : : "ax");

    if (reg > 0x07 && reg < 0x0C)
    {
        ide_write(channel, ATA_REG_CONTROL, IDEChannels[channel].nIEN);
    }
}

void ide_init(uint32_t BAR0, uint32_t BAR1, uint32_t BAR2, uint32_t BAR3, uint32_t BAR4)
{
    UNUSED(BAR0);
    UNUSED(BAR1);
    UNUSED(BAR2);
    UNUSED(BAR3);
    UNUSED(BAR4);
}
