/* DESCRIPTION: E93 IDE Driver Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#include "../cpu/drvutils.h"
#include "../cpu/ports.h"
#include "../cpu/timer.h"
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
        port_byte_out(IDEChannels[channel].ctrl + reg - 0x0C, data);
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

    asm volatile("pushw %es; pushw %ax; movw %ds, %ax; movw %ax, %es; popw %ax;");

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

    asm volatile("popw %es");

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


    while (ide_read(channel, ATA_REG_STATUS) & ATA_SR_BSY);

    if (advanced_check)
    {
        uint8_t state = ide_read(channel, ATA_REG_STATUS);

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
    uint8_t count = 0;

    // Detect IDE Channels
    IDEChannels[ATA_PRIMARY].base = (BAR0 & 0xFFFFFFFC) + 0x1F0 * (!BAR0);
    IDEChannels[ATA_PRIMARY].ctrl = (BAR1 & 0xFFFFFFFC) + 0x3F6 * (!BAR1);
    IDEChannels[ATA_SECONDARY].base = (BAR2 & 0xFFFFFFFC) + 0x170 * (!BAR2);
    IDEChannels[ATA_SECONDARY].ctrl = (BAR3 & 0xFFFFFFFC) + 0x376 * (!BAR3);
    IDEChannels[ATA_PRIMARY].bmide = (BAR4 & 0xFFFFFFFC) + 0;
    IDEChannels[ATA_SECONDARY].bmide = (BAR4 & 0xFFFFFFFC) + 8;

    // Disable IRQs
    ide_write(ATA_PRIMARY, ATA_REG_CONTROL, 2);
    ide_write(ATA_SECONDARY, ATA_REG_CONTROL, 2);

    // Detect IDE Devices
    for (uint8_t i = 0; i < 2; i++)
    {
        for (uint8_t j = 0; j < 2; j++)
        {
            uint8_t err = 0;
            uint8_t type = IDE_ATA;
            uint8_t status = 0;

            IDEDevices[count].Reserved = 0;

            // Select Drive
            ide_write(i, ATA_REG_HDDEVSEL, 0xA0 | (j << 4));
            wait_timer(5);

            // Send ATA Identify Command
            ide_write(i, ATA_REG_COMMAND, ATA_CMD_IDENTIFY);
            wait_timer(5);

            // Polling
            if (ide_read(i, ATA_REG_STATUS) == 0)
            {
                continue;
            }

            while (1)
            {
                status = ide_read(i, ATA_REG_STATUS);
                if ((status & ATA_SR_ERR))
                {
                    err = 1;
                    break;
                }
                if (!(status & ATA_SR_BSY) && (status & ATA_SR_DRQ))
                {
                    break;
                }
            }

            // Check if device is ATAPI
            if (err != 0)
            {
                uint8_t cl = ide_read(i, ATA_REG_LBA1);
                uint8_t ch = ide_read(i, ATA_REG_LBA2);

                if (cl == 0x14 && ch == 0xEB)
                {
                    type = IDE_ATAPI;
                }
                else if (cl == 0x69 && ch == 0x96)
                {
                    type = IDE_ATAPI;
                }
                else
                {
                    continue;
                }

                ide_write(i, ATA_REG_COMMAND, ATA_CMD_IDENTIFY_PACKET);
                wait_timer(5);
            }

            // Read Identification Space of the Device
            ide_read_buffer(i, ATA_REG_DATA, (uint32_t)ide_buffer, 128);

            // Read Device Parameters
            IDEDevices[count].Reserved = 1;
            IDEDevices[count].Type = type;
            IDEDevices[count].Channel = i;
            IDEDevices[count].Drive = j;
            IDEDevices[count].Signature = *((uint16_t *)(ide_buffer + ATA_IDENT_DEVICETYPE));
            IDEDevices[count].Capabilities = *((uint16_t *)(ide_buffer + ATA_IDENT_CAPABILITIES));
            IDEDevices[count].CommandSets = *((uint32_t *)(ide_buffer + ATA_IDENT_COMMANDSETS));

            // Get Size
            if (IDEDevices[count].CommandSets & (1 << 26))
            {
                IDEDevices[count].Size = *((uint32_t *)(ide_buffer + ATA_IDENT_MAX_LBA_EXT));
            }
            else
            {
                IDEDevices[count].Size = *((uint32_t *)(ide_buffer + ATA_IDENT_MAX_LBA));
            }

            // Get Model
            for (int k = 0; k < 40; k += 2)
            {
                IDEDevices[count].Model[k] = ide_buffer[ATA_IDENT_MODEL + k + 1];
                IDEDevices[count].Model[k + 1] = ide_buffer[ATA_IDENT_MODEL + k];
            }
            IDEDevices[count].Model[40] = 0;

            count++;
        }
    }

    // Print IDE Devices
    for (int i = 0; i < 4; i++)
    {
        if (IDEDevices[i].Reserved == 1)
        {
            printl_color("IDE Device:\n", OUTPUT_COLOR);

            char ide_device_number_str[2] = { 0 };
            int_to_ascii(i, ide_device_number_str);

            printl_color("- Device: ", OUTPUT_COLOR);
            printl_color(ide_device_number_str, OUTPUT_COLOR);
            printl_color("\n", OUTPUT_COLOR);

            printl_color("- Type: ", OUTPUT_COLOR);
            if (IDEDevices[i].Type == IDE_ATA)
            {
                printl_color("ATA\n", OUTPUT_COLOR);
            }
            else if (IDEDevices[i].Type == IDE_ATAPI)
            {
                printl_color("ATAPI\n", OUTPUT_COLOR);
            }
            else
            {
                printl_color("Unknown\n", OUTPUT_COLOR);
            }

            printl_color("- Model: ", OUTPUT_COLOR);
            printl_color(IDEDevices[i].Model, OUTPUT_COLOR);
            printl_color("\n", OUTPUT_COLOR);

            char ide_device_size_str[12] = "";
            int_to_ascii(IDEDevices[i].Size, ide_device_size_str);

            printl_color("- Size: ", OUTPUT_COLOR);
            printl_color(ide_device_size_str, OUTPUT_COLOR);
            printl_color(" sectors\n", OUTPUT_COLOR);
            printl_color("\n", OUTPUT_COLOR);
        }
    }
}

uint8_t ide_ata_access(uint8_t direction, uint8_t drive, uint32_t lba, uint8_t numsects, uint16_t selector, uint32_t edi)
{
    uint8_t lba_mode = 0;
    uint8_t dma = 0;
    uint8_t cmd = 0;
    uint8_t lba_io[6] = { 0 };
    uint32_t channel = IDEDevices[drive].Channel;
    uint32_t slavebit = IDEDevices[drive].Drive;
    uint32_t bus = IDEChannels[channel].base;
    uint32_t words = 256;
    uint16_t cyl = 0;
    uint8_t head = 0;
    uint8_t sector = 0;
    uint8_t error = 0;

    ide_write(channel, ATA_REG_CONTROL, IDEChannels[channel].nIEN = (ide_irq_invoked = 0x00) + 0x02);

    // Select the LBA mode (LBA28, LBA48 or CHS)
    if (lba >= 0x10000000)
    {
        lba_mode  = 2;
        lba_io[0] = (lba & 0x000000FF) >> 0;
        lba_io[1] = (lba & 0x0000FF00) >> 8;
        lba_io[2] = (lba & 0x00FF0000) >> 16;
        lba_io[3] = (lba & 0xFF000000) >> 24;
        lba_io[4] = 0;
        lba_io[5] = 0;
        head      = 0;
    }
    else if (IDEDevices[drive].Capabilities & 0x200)
    {
        lba_mode  = 1;
        lba_io[0] = (lba & 0x000000FF) >> 0;
        lba_io[1] = (lba & 0x0000FF00) >> 8;
        lba_io[2] = (lba & 0x00FF0000) >> 16;
        lba_io[3] = 0;
        lba_io[4] = 0;
        lba_io[5] = 0;
        head      = (lba & 0x0F000000) >> 24;
    }
    else {
        lba_mode  = 0;
        sector    = (lba % 63) + 1;
        cyl       = (lba + 1 - sector) / (16 * 63);
        lba_io[0] = sector;
        lba_io[1] = (cyl >> 0) & 0xFF;
        lba_io[2] = (cyl >> 8) & 0xFF;
        lba_io[3] = 0;
        lba_io[4] = 0;
        lba_io[5] = 0;
        head      = (lba + 1 - sector) % (16 * 63) / (63);
    }

    // Waitif the drive is busy
    while (ide_read(channel, ATA_REG_STATUS) & ATA_SR_BSY);

    // Select drive from the controller
    if (lba_mode == 0)
    {
        ide_write(channel, ATA_REG_HDDEVSEL, 0xA0 | (slavebit << 4) | head);
    }
    else
    {
        ide_write(channel, ATA_REG_HDDEVSEL, 0xE0 | (slavebit << 4) | head);
    }

    // Write parameters
    if (lba_mode == 2)
    {
        ide_write(channel, ATA_REG_SECCOUNT1, 0);
        ide_write(channel, ATA_REG_LBA3, lba_io[3]);
        ide_write(channel, ATA_REG_LBA4, lba_io[4]);
        ide_write(channel, ATA_REG_LBA5, lba_io[5]);
    }
    else
    {
        ide_write(channel, ATA_REG_SECCOUNT0, numsects);
        ide_write(channel, ATA_REG_LBA0, lba_io[0]);
        ide_write(channel, ATA_REG_LBA1, lba_io[1]);
        ide_write(channel, ATA_REG_LBA2, lba_io[2]);
    }

    // Select the command and send to the drive
    if (lba_mode == 0 && dma == 0 && direction == 0)
    {
        cmd = ATA_CMD_READ_PIO;
    }
    if (lba_mode == 1 && dma == 0 && direction == 0)
    {
        cmd = ATA_CMD_READ_PIO;
    }
    if (lba_mode == 2 && dma == 0 && direction == 0)
    {
        cmd = ATA_CMD_READ_PIO_EXT;
    }
    if (lba_mode == 0 && dma == 1 && direction == 0)
    {
        cmd = ATA_CMD_WRITE_DMA;
    }
    if (lba_mode == 1 && dma == 1 && direction == 0)
    {
        cmd = ATA_CMD_WRITE_DMA;
    }
    if (lba_mode == 2 && dma == 1 && direction == 0)
    {
        cmd = ATA_CMD_WRITE_DMA_EXT;
    }
    if (lba_mode == 0 && dma == 0 && direction == 1)
    {
        cmd = ATA_CMD_WRITE_PIO;
    }
    if (lba_mode == 1 && dma == 0 && direction == 1)
    {
        cmd = ATA_CMD_WRITE_PIO;
    }
    if (lba_mode == 2 && dma == 0 && direction == 1)
    {
        cmd = ATA_CMD_WRITE_PIO_EXT;
    }
    if (lba_mode == 0 && dma == 1 && direction == 1)
    {
        cmd = ATA_CMD_WRITE_DMA;
    }
    if (lba_mode == 1 && dma == 1 && direction == 1)
    {
        cmd = ATA_CMD_WRITE_DMA;
    }
    if (lba_mode == 2 && dma == 1 && direction == 1)
    {
        cmd = ATA_CMD_WRITE_DMA_EXT;
    }
    ide_write(channel, ATA_REG_COMMAND, cmd);

    if (dma)
    {
        if (direction == 0)
        {
            // DMA Read
            ide_write(channel, ATA_REG_CONTROL, 0);
        }
        else
        {
            // DMA Write
            ide_write(channel, ATA_REG_CONTROL, 0x8);
        }
    }
    else {
        if (direction == 0)
        {
            // PIO Read
            for (int i = 0; i < numsects; i++)
            {
                if ((error = ide_polling(channel, 1)))
                {
                    return error;
                }
                asm("pushw %es");
                asm("mov %%ax, %%es" : : "a"(selector));
                asm("rep insw" : : "c"(words), "d"(bus), "D"(edi));
                asm("popw %es");
                edi += (words * 2);
            }
        }
        else
        {
            // PIO Write
            for (int i = 0; i < numsects; i++)
            {
                ide_polling(channel, 0);
                asm("pushw %ds");
                asm("mov %%ax, %%ds" : : "a"(selector));
                asm("rep outsw" : : "c"(words), "d"(bus), "S"(edi));
                asm("popw %ds");
                edi += (words * 2);
            }
            ide_write(channel, ATA_REG_COMMAND, (char []){ ATA_CMD_CACHE_FLUSH, ATA_CMD_CACHE_FLUSH, ATA_CMD_CACHE_FLUSH_EXT }[lba_mode]);
            ide_polling(channel, 0);
        }
    }

    return 0;
}

void ide_wait_irq(void)
{
    while (!ide_irq_invoked);
    ide_irq_invoked = 0;
}

void ide_irq_handler(void)
{
    ide_irq_invoked = 1;
}

uint8_t ide_atapi_read(uint8_t drive, uint32_t lba, uint8_t numsects, uint16_t selector, uint32_t edi)
{
    unsigned int channel  = IDEDevices[drive].Channel;
    unsigned int slavebit = IDEDevices[drive].Drive;
    unsigned int bus      = IDEChannels[channel].base;
    unsigned int words    = 1024;
    uint8_t error         = 0;

    // Enable IRQs
    ide_write(channel, ATA_REG_CONTROL, IDEChannels[channel].nIEN = (ide_irq_invoked = 0x00));

    // Setup SCSI packet
    atapi_packet[0] = ATAPI_CMD_READ;
    atapi_packet[1] = 0x00;
    atapi_packet[2] = (lba >> 24) & 0xFF;
    atapi_packet[3] = (lba >> 16) & 0xFF;
    atapi_packet[4] = (lba >> 8) & 0xFF;
    atapi_packet[5] = (lba >> 0) & 0xFF;
    atapi_packet[6] = 0x00;
    atapi_packet[7] = 0x00;
    atapi_packet[8] = 0x00;
    atapi_packet[9] = numsects;
    atapi_packet[10] = 0x00;
    atapi_packet[11] = 0x00;

    // Select the drive
    ide_write(channel, ATA_REG_HDDEVSEL, slavebit << 4);

    // Delay 400 nanoseconds for select to complete
    for (int i = 0; i < 4; i++)
    {
        ide_read(channel, ATA_REG_ALTSTATUS);
    }

    // Inform the controller that we use PIO mode
    ide_write(channel, ATA_REG_FEATURES, 0);

    // Tell the controller the size of buffer
    ide_write(channel, ATA_REG_LBA1, (words * 2) & 0xFF);
    ide_write(channel, ATA_REG_LBA2, (words * 2) >> 8);

    // Send the packet command
    ide_write(channel, ATA_REG_COMMAND, ATA_CMD_PACKET);

    // Wait for the drive to be ready
    if ((error = ide_polling(channel, 1)))
    {
        return error;
    }

    // Send the packet data
    asm("rep outsw" : : "c"(6), "d"(bus), "S"(atapi_packet));

    // Receive data
    for (int i = 0; i < numsects; i++)
    {
        ide_wait_irq();
        if ((error = ide_polling(channel, 1)))
        {
            return error;
        }
        asm("pushw %es");
        asm("mov %%ax, %%es" : : "a"(selector));
        asm("rep insw" : : "c"(words), "d"(bus), "D"(edi));
        asm("popw %es");
        edi += (words * 2);
    }

    // Waiting for an IRQ
    ide_wait_irq();

    // Waiting for BSY and DRQ to clear
    while (ide_read(channel, ATA_REG_STATUS) & (ATA_SR_BSY | ATA_SR_DRQ));

    return 0;
}

void ide_read_sectors(uint8_t drive, uint8_t numsects, uint32_t lba, uint16_t es, uint32_t edi)
{
    if (drive > 3 || IDEDevices[drive].Reserved == 0)  // Check if the drive presents
    {
        error_package = 1;
    }
    else if (((lba + numsects) > IDEDevices[drive].Size) && (IDEDevices[drive].Type == IDE_ATA))  // Check if inputs are valid
    {
        error_package = 2;
    }
    else  // Read in PIO mode through polling an IRQs
    {
        uint8_t error = 0;
        if (IDEDevices[drive].Type == IDE_ATA)
        {
            error = ide_ata_access(ATA_READ, drive, lba, numsects, es, edi);
        }
        else if (IDEDevices[drive].Type == IDE_ATAPI)
        {
            for (int i = 0; i < numsects; i++)
            {
                error = ide_atapi_read(drive, lba + i, 1, es, edi + (i * 2048));
            }
        }
        error_package = ide_print_error(drive, error);
    }
}

void ide_write_sectors(uint8_t drive, uint8_t numsects, uint32_t lba, uint16_t es, uint32_t edi)
{
    if (drive > 3 || IDEDevices[drive].Reserved == 0)  // Check if the drive presents
    {
        error_package = 1;
    }
    else if (((lba + numsects) > IDEDevices[drive].Size) && (IDEDevices[drive].Type == IDE_ATA))  // Check if inputs are valid
    {
        error_package = 2;
    }
    else  // Write in PIO mode through polling an IRQs
    {
        uint8_t error = 0;
        if (IDEDevices[drive].Type == IDE_ATA)
        {
            error = ide_ata_access(ATA_WRITE, drive, lba, numsects, es, edi);
        }
        else if (IDEDevices[drive].Type == IDE_ATAPI)
        {
            error_package = 4;  // Write-protected
        }
        error_package = ide_print_error(drive, error);
    }
}

void ide_atapi_eject(uint8_t drive)
{
    uint32_t channel = IDEDevices[drive].Channel;
    uint32_t slavebit = IDEDevices[drive].Drive;
    uint32_t bus = IDEChannels[channel].base;
    uint32_t words = 2048;
    uint8_t error = 0;

    ide_irq_invoked = 0;

    if (drive > 3 || IDEDevices[drive].Reserved == 0)  // Check if the drive presents
    {
        error_package = 1;
    }
    else if (IDEDevices[drive].Type == IDE_ATA)  // Check the drive isn't ATAPI
    {
        error_package = 20;
    }
    else {  // Eject the drive
        // Enable IRQs
        ide_write(channel, ATA_REG_CONTROL, IDEChannels[channel].nIEN = (ide_irq_invoked = 0x00));

        // Select SCSI packet
        atapi_packet[0] = ATAPI_CMD_EJECT;
        atapi_packet[1] = 0x00;
        atapi_packet[2] = 0x00;
        atapi_packet[3] = 0x00;
        atapi_packet[4] = 0x02;
        atapi_packet[5] = 0x00;
        atapi_packet[6] = 0x00;
        atapi_packet[7] = 0x00;
        atapi_packet[8] = 0x00;
        atapi_packet[9] = 0x00;
        atapi_packet[10] = 0x00;
        atapi_packet[11] = 0x00;

        // Select the drive
        ide_write(channel, ATA_REG_HDDEVSEL, slavebit << 4);

        // Delay 400 nanosecond for select to complete
        for (int i = 0; i < 4; i++)
        {
            ide_read(channel, ATA_REG_ALTSTATUS);
        }

        // Send the packet command
        ide_write(channel, ATA_REG_COMMAND, ATA_CMD_PACKET);

        if ((error = ide_polling(channel, 1)))  // Waiting the driver to finish or invoke an error
        {
            error_package = error;
        }
        else {  // Send the packet data
            asm("rep outsw" : : "c"(6), "d"(bus), "S"(atapi_packet));
            ide_wait_irq();
            error = ide_polling(channel, 1);
            if ((error == 3))
            {
                error = 0;
            }
        }

        error_package = ide_print_error(drive, error);

        UNUSED(words);
    }
}

uint32_t ide_atapi_read_capacity(uint8_t drive)
{
    uint32_t channel = IDEDevices[drive].Channel;
    uint32_t slavebit = IDEDevices[drive].Drive;
    uint32_t lba = 0;
    uint32_t bus = IDEChannels[channel].base;
    uint32_t words = 2048;
    uint8_t error = 0;

    ide_irq_invoked = 0;

    if (drive > 3 || IDEDevices[drive].Reserved == 0)  // Check if the drive presents
    {
        printl_color("Drive not present!\n", ERROR_COLOR);
        error_package = 1;
    }
    else if (IDEDevices[drive].Type == IDE_ATA)  // Check the drive isn't ATAPI
    {
        printl_color("Drive is not ATAPI!\n", ERROR_COLOR);
        error_package = 20;
    }
    else
    {   // Read the capacity of the drive
        // Enable IRQs
        ide_write(channel, ATA_REG_CONTROL, IDEChannels[channel].nIEN = (ide_irq_invoked = 0x00));

        // Make ATAPI packet
        atapi_packet[0]  = ATAPI_CMD_READ_CAPACITY;
        atapi_packet[1]  = 0x00;
        atapi_packet[2]  = (lba >> 24) & 0xFF;
        atapi_packet[3]  = (lba >> 16) & 0xFF;
        atapi_packet[4]  = (lba >> 8) & 0xFF;
        atapi_packet[5]  = (lba >> 0) & 0xFF;
        atapi_packet[6]  = 0x00;
        atapi_packet[7]  = 0x00;
        atapi_packet[8]  = 0x00;
        atapi_packet[9]  = 0x00;
        atapi_packet[10] = 0x00;
        atapi_packet[11] = 0x00;

        // Select the drive
        ide_write(channel, ATA_REG_HDDEVSEL, slavebit << 4);

        // Delay 400 nanosecond for select to complete
        for (int i = 0; i < 4; i++)
        {
            ide_read(channel, ATA_REG_ALTSTATUS);
        }

        // Set FEATURES register to zero
        ide_write(channel, ATA_REG_FEATURES, 0);

        // Set LBA1 and LBA2 registers to 0x08
        ide_write(channel, ATA_REG_LBA1, 0x08);
        ide_write(channel, ATA_REG_LBA2, 0x08);

        // Send the packet command
        ide_write(channel, ATA_REG_COMMAND, ATA_CMD_PACKET);

        // Waiting the driver to finish or invoke an error
        if ((error = ide_polling(channel, 1)))
        {
            printl_color("Error occured!\n", ERROR_COLOR);
            error_package = error;
        }
        else
        {   // Send the packet data
            asm("rep outsw" : : "c"(6), "d"(bus), "S"(atapi_packet));
            ide_wait_irq();
            error = ide_polling(channel, 1);
            if ((error == 3))
            {
                error = 0;
            }
        }

        error_package = ide_print_error(drive, error);

        // Read the data
        ide_read_buffer(channel, ATA_REG_DATA, (uint32_t)ide_buffer, words);

        // Return the capacity
        return *((uint32_t *)(ide_buffer + 0));
    }

    return 0;
}
