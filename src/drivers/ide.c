/* DESCRIPTION: E93 IDE Driver Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "../cpu/drvutils.h"
#include "../cpu/ports.h"
#include "screen.h"

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

uint8_t ide_polling(uint8_t channel, uint8_t advanced_check)
{
    for(int i = 0; i < 4; i++)
    {
        ide_read(channel, ATA_REG_ALTSTATUS);
    }


    while (ide_read(channel, ATA_REG_STATUS) & ATA_SR_BSY) {}

    if (advanced_check)
    {
        unsigned char state = ide_read(channel, ATA_REG_STATUS);

        if (state & ATA_SR_ERR)
        {
            return 2;
        }

        if (state & ATA_SR_DF)
        {
            return 1;
        }

        if ((state & ATA_SR_DRQ) == 0)
        {
            return 3;
        }
    }

    return 0;
}

uint8_t ide_print_error(uint32_t drive, uint8_t error)
{
    if (error == 0)
    {
        return error;
    }

    printl_color("IDE Error:\n", ERROR_COLOR);

    if (error == 1)
    {
        printl_color("- Device Fault!\n", ERROR_COLOR);
        error = 19;
    }
    else if (error == 2)
    {
        uint8_t status = ide_read(IDEDevices[drive].Channel, ATA_REG_ERROR);
        if (status & ATA_ER_AMNF)
        {
            printl_color("- No Address Mark Found!\n", ERROR_COLOR);
            error = 7;
        }
        if (status & ATA_ER_TK0NF)
        {
            printl_color("- No Media or Media Error!\n", ERROR_COLOR);
            error = 3;
        }
        if (status & ATA_ER_ABRT)
        {
            printl_color("- Command Aborted!\n", ERROR_COLOR);
            error = 20;
        }
        if (status & ATA_ER_MCR)
        {
            printl_color("- No Media or Media Error!\n", ERROR_COLOR);
            error = 3;

        }
        if (status & ATA_ER_IDNF)
        {
            printl_color("- ID mark not Found!\n", ERROR_COLOR);
            error = 21;
        }
        if (status & ATA_ER_MC)
        {
            printl_color("- No Media or Media Error!\n", ERROR_COLOR);
            error = 3;
        }
        if (status & ATA_ER_UNC)
        {
            printl_color("- Uncorrectable Data Error!\n", ERROR_COLOR);
            error = 22;
        }
        if (status & ATA_ER_BBK)
        {
            printl_color("- Bad Sectors!\n", ERROR_COLOR);
            error = 13;
        }
    }
    else if (error == 3)
    {
        printl_color("- Reads Nothing!\n", ERROR_COLOR);
        error = 23;
    }
    else if (error == 4)
    {
        printl_color("- Write Protected!\n", ERROR_COLOR);
        error = 8;
    }

    char ide_device_number_str[2] = { 0 };

    int_to_ascii(IDEDevices[drive].Size, ide_device_number_str);

    printl_color("\n", ERROR_COLOR);
    printl_color("- Error at device: ", ERROR_COLOR);
    printl_color(ide_device_number_str, ERROR_COLOR);

    printl_color("\n", ERROR_COLOR);
    printl_color("- Error at channel: ", ERROR_COLOR);
    if (IDEDevices[drive].Channel == 0)
    {
        printl_color("Primary\n", ERROR_COLOR);
    }
    else if (IDEDevices[drive].Channel == 1)
    {
        printl_color("Secondary\n", ERROR_COLOR);
    }
    else
    {
        printl_color("Unknown\n", ERROR_COLOR);
    }

    printl_color("\n", ERROR_COLOR);
    printl_color("- Error at drive: ", ERROR_COLOR);
    if (IDEDevices[drive].Drive == 0)
    {
        printl_color("Master\n", ERROR_COLOR);
    }
    else if (IDEDevices[drive].Drive == 1)
    {
        printl_color("Slave\n", ERROR_COLOR);
    }
    else
    {
        printl_color("Unknown\n", ERROR_COLOR);
    }

    printl_color("\n", ERROR_COLOR);

    return error;
}

void ide_init(uint32_t BAR0, uint32_t BAR1, uint32_t BAR2, uint32_t BAR3, uint32_t BAR4)
{
    UNUSED(BAR0);
    UNUSED(BAR1);
    UNUSED(BAR2);
    UNUSED(BAR3);
    UNUSED(BAR4);
}
