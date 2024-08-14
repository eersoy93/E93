/* DESCRIPTION: E93 IDE Driver Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with MIT License. See LICENSE file for details.
 */

#ifndef IDE_H
#define IDE_H

#include <stdint.h>

// ATA Command Registers

#define ATA_CMD_READ_PIO          0x20
#define ATA_CMD_READ_PIO_EXT      0x24
#define ATA_CMD_READ_DMA          0xC8
#define ATA_CMD_READ_DMA_EXT      0x25
#define ATA_CMD_WRITE_PIO         0x30
#define ATA_CMD_WRITE_PIO_EXT     0x34
#define ATA_CMD_WRITE_DMA         0xCA
#define ATA_CMD_WRITE_DMA_EXT     0x35
#define ATA_CMD_CACHE_FLUSH       0xE7
#define ATA_CMD_CACHE_FLUSH_EXT   0xEA
#define ATA_CMD_PACKET            0xA0
#define ATA_CMD_IDENTIFY_PACKET   0xA1
#define ATA_CMD_IDENTIFY          0xEC

#define ATAPI_CMD_READ            0xA8
#define ATAPI_CMD_EJECT           0x1B
#define ATAPI_CMD_READ_CAPACITY   0x25

#define ATA_IDENT_DEVICETYPE      0
#define ATA_IDENT_CYLINDERS       2
#define ATA_IDENT_HEADS           6
#define ATA_IDENT_SECTORS         12
#define ATA_IDENT_SERIAL          20
#define ATA_IDENT_MODEL           54
#define ATA_IDENT_CAPABILITIES    98
#define ATA_IDENT_FIELDVALID      106
#define ATA_IDENT_MAX_LBA         120
#define ATA_IDENT_COMMANDSETS     164
#define ATA_IDENT_MAX_LBA_EXT     200

#define IDE_ATA                   0x00
#define IDE_ATAPI                 0x01

#define ATA_MASTER                0x00
#define ATA_SLAVE                 0x01

#define ATA_PRIMARY               0x00
#define ATA_SECONDARY             0x01

#define ATA_READ                  0x00
#define ATA_WRITE                 0x01

#define ATA_REG_DATA              0x00
#define ATA_REG_ERROR             0x01
#define ATA_REG_FEATURES          0x01
#define ATA_REG_SECCOUNT0         0x02
#define ATA_REG_LBA0              0x03
#define ATA_REG_LBA1              0x04
#define ATA_REG_LBA2              0x05
#define ATA_REG_HDDEVSEL          0x06
#define ATA_REG_COMMAND           0x07
#define ATA_REG_STATUS            0x07
#define ATA_REG_SECCOUNT1         0x08
#define ATA_REG_LBA3              0x09
#define ATA_REG_LBA4              0x0A
#define ATA_REG_LBA5              0x0B
#define ATA_REG_CONTROL           0x0C
#define ATA_REG_ALTSTATUS         0x0C
#define ATA_REG_DEVADDRESS        0x0D


// ATA Error Registers
#define ATA_ER_BBK                0x80
#define ATA_ER_UNC                0x40
#define ATA_ER_MC                 0x20
#define ATA_ER_IDNF               0x10
#define ATA_ER_MCR                0x08
#define ATA_ER_ABRT               0x04
#define ATA_ER_TK0NF              0x02
#define ATA_ER_AMNF               0x01


// ATA Status Registers
#define ATA_SR_BSY                0x80
#define ATA_SR_DRDY               0x40
#define ATA_SR_DF                 0x20
#define ATA_SR_DSC                0x10
#define ATA_SR_DRQ                0x08
#define ATA_SR_CORR               0x04
#define ATA_SR_IDX                0x02
#define ATA_SR_ERR                0x01


// IDE Channel Register Struct
struct IDEChannelRegisters {
   uint16_t base;
   uint16_t ctrl;
   uint16_t bmide;
   uint8_t  nIEN;
} IDEChannels[2];


// IDE Device Information Struct
struct ide_device {
   uint8_t  Reserved;
   uint8_t  Channel;
   uint8_t  Drive;
   uint16_t Type;
   uint16_t Signature;
   uint16_t Capabilities;
   uint32_t CommandSets;
   uint32_t Size;
   char     Model[41];
} IDEDevices[4];


// IDE Variables

uint8_t ide_buffer[2048] = { 0 };

volatile uint8_t ide_irq_invoked = 0;

uint8_t atapi_packet[12] = {0xA8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

uint8_t error_package = 0;


// IDE Functions

uint8_t ide_read(uint8_t channel, uint8_t reg);
void ide_write(uint8_t channel, uint8_t reg, uint8_t data);

void ide_read_buffer(uint8_t channel, uint8_t reg, uint32_t buffer, uint32_t quads);

uint8_t ide_polling(uint8_t channel, uint8_t advanced_check);

uint8_t ide_print_error(uint32_t drive, uint8_t error);

void ide_init(uint32_t BAR0, uint32_t BAR1, uint32_t BAR2, uint32_t BAR3, uint32_t BAR4);

uint8_t ide_ata_access(uint8_t direction, uint8_t drive, uint32_t lba, uint8_t numsects, uint16_t selector, uint32_t edi);

void ide_wait_irq(void);
void ide_irq_handler(void);

uint8_t ide_atapi_read(uint8_t drive, uint32_t lba, uint8_t numsects, uint16_t selector, uint32_t edi);

void ide_read_sectors(uint8_t drive, uint8_t numsects, uint32_t lba, uint16_t es, uint32_t edi);
void ide_write_sectors(uint8_t drive, uint8_t numsects, uint32_t lba, uint16_t es, uint32_t edi);
void ide_atapi_eject(uint8_t drive);

uint32_t ide_atapi_read_capacity(uint8_t drive);

#endif