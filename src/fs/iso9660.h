/* DESCRIPTION: E93 IS09660 File System Header File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with GPLv2 License. See LICENSE file for details.
 */

#ifndef ISO9660_H
#define ISO9660_H

#include <stdint.h>

// Volume Descriptor
typedef struct {
    uint8_t type;
    int8_t id[5];
    uint8_t version;
    uint8_t data[2041];
} iso9660_vd_t;

// Volume Descriptor Types
#define ISO9660_VD_BOOT_RECORD    0x00
#define ISO9660_VD_PRIMARY        0x01
#define ISO9660_VD_SUPPLEMENTARY  0x02
#define ISO9660_VD_PARTITION      0x03
#define ISO9660_VD_TERMINATOR     0xFF

// Boot Record Volume Descriptor
typedef struct {
    uint8_t type;
    int8_t id[5];
    uint8_t version;
    uint8_t boot_system_identifier[32];
    uint8_t boot_identifier[32];
    uint8_t boot_system_use[1977];
} iso9660_boot_record_t;

// Primary Volume Descriptor
typedef struct {
    uint8_t type;
    int8_t id[5];
    uint8_t version;
    uint8_t unused_1;
    int8_t system_id[32];
    int8_t volume_id[32];
    uint8_t unused_2[8];
    uint32_t volume_space_size_le;
    uint32_t volume_space_size_be;
    uint8_t unused_3[32];
    uint16_t volume_set_size_le;
    uint16_t volume_set_size_be;
    uint16_t volume_sequence_number_le;
    uint16_t volume_sequence_number_be;
    uint16_t logical_block_size_le;
    uint16_t logical_block_size_be;
    uint32_t path_table_size_le;
    uint32_t path_table_size_be;
    uint32_t type_l_path_table;
    uint32_t optional_type_l_path_table;
    uint32_t type_m_path_table;
    uint32_t optional_type_m_path_table;
    uint8_t root_directory_record[34];
    int8_t volume_set_id[128];
    int8_t publisher_id[128];
    int8_t data_preparer_id[128];
    int8_t application_id[128];
    int8_t copyright_file_id[38];
    int8_t abstract_file_id[36];
    int8_t bibliographic_file_id[37];
    int8_t creation_date_and_time[17];
    int8_t modification_date_and_time[17];
    int8_t expiration_date_and_time[17];
    int8_t effective_date_and_time[17];
    uint8_t file_structure_version;
    uint8_t unused_4;
    uint8_t application_use[512];
    uint8_t reserved_by_iso[653];
} iso9660_pvd_t;

// Volume Descriptor Set Terminator
typedef struct {
    uint8_t type;
    int8_t id[5];
    uint8_t version;
    uint8_t unused[2041];
} iso9660_vdst_t;

// The Path Table
typedef struct {
    uint8_t directory_record_length;
    uint8_t extended_attribute_record_length;
    uint32_t extent_location_le;
    uint32_t extent_location_be;
    uint16_t parent_directory_number_le;
    uint16_t parent_directory_number_be;
    uint8_t directory_identifier_length[32];  // Variable length
    int8_t directory_identifier[1];
} iso9660_path_table_t;

// Date and Time Structure
typedef struct {
    uint8_t years_since_1900;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    int8_t time_zone_offset;
} iso9660_datetime_t;

// Directory Record
typedef struct {
    uint8_t length;
    uint8_t extended_attribute_record_length;
    uint32_t extent_location_le;
    uint32_t extent_location_be;
    uint32_t data_length_le;
    uint32_t data_length_be;
    iso9660_datetime_t recording_date_and_time;
    uint8_t file_flags;
    uint8_t file_unit_size;
    uint8_t interleave_gap_size;
    uint16_t volume_sequence_number_le;
    uint16_t volume_sequence_number_be;
    uint8_t file_identifier_length;
    uint8_t file_identifier[32]; // Variable length
} iso9660_dir_record_t;

// File Flags (bit flags as per ISO9660 specification)
#define ISO9660_FILE_FLAG_HIDDEN             (1 << 0)
#define ISO9660_FILE_FLAG_DIRECTORY          (1 << 1)
#define ISO9660_FILE_FLAG_ASSOCIATED_FILE    (1 << 2)
#define ISO9660_FILE_FLAG_RECORD             (1 << 3)
#define ISO9660_FILE_FLAG_PROTECTION         (1 << 4)
#define ISO9660_FILE_FLAG_RESERVED_1         (1 << 5)
#define ISO9660_FILE_FLAG_RESERVED_2         (1 << 6)
#define ISO9660_FILE_FLAG_MULTI_EXTENT       (1 << 7)

// ISO9660 File System Constants
#define ISO9660_SECTOR_SIZE 2048

uint8_t iso9660_open(uint8_t filename[]);
uint8_t iso9660_read(uint8_t file_descriptor, uint32_t offset, uint32_t size, uint8_t buffer[]);
uint8_t iso9660_close(uint8_t file_descriptor);

#endif
