/* DESCRIPTION: E93 IS09660 File System Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2024 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with GPLv2 License. See LICENSE file for details.
 */

#include "fs.h"
#include "iso9660.h"
#include "../cpu/drvutils.h"
#include "../drivers/ide.h"

// Helper function finds a free file handle slot
static int alloc_file_handle()
{
    for (int i = 0; i < 127; ++i)
    {
        if (!open_files[i].in_use)
        {
            return i;
        }
    }
    return -1;
}

// Helper: Normalize ISO9660 filename to 8.3 format
static void normalize_iso9660_name(uint8_t * in, uint8_t in_len, uint8_t * out, uint8_t * out_len)
{
    int i;
    // Uppercase and copy up to '.' or ';' or max 31 chars
    for (i = 0; i < in_len && i < 31; i++)
    {
        uint8_t c = in[i];
        if (c >= 'a' && c <= 'z')
        {
            c = c - 'a' + 'A';
        }
        if (c == ';')
        {
            break; // Don't copy version from input
        }
        out[i] = c;
    }
    // Append ;1 if not present
    if (i == 0 || (i > 2 && out[i-2] != ';'))
    {
        out[i++] = ';';
        out[i++] = '1';
    }
    *out_len = i;
}

// Helper: Find a file or directory in a given directory sector by name
static int find_in_directory(uint32_t dir_lba, uint32_t dir_size, uint8_t *name, uint8_t name_len, iso9660_dir_record_t *out_rec)
{
    uint32_t bytes_read = 0;
    static uint8_t dir_sector[ISO9660_SECTOR_SIZE];
    uint8_t normalized[32];
    uint8_t normalized_len;

    normalize_iso9660_name(name, name_len, normalized, &normalized_len);

    while (bytes_read < dir_size)
    {
        ide_read_sectors(1, 1, dir_lba + (bytes_read / ISO9660_SECTOR_SIZE), 0, (uint32_t)dir_sector);
        uint32_t offset = 0;
        while (offset < ISO9660_SECTOR_SIZE)
        {
            iso9660_dir_record_t *rec = (iso9660_dir_record_t *)(dir_sector + offset);

            if (rec->length == 0)
            {
                break;
            }
            if (rec->file_identifier_length == normalized_len &&
                memcmp(rec->file_identifier, normalized, normalized_len) == 0)
            {
                if (out_rec)
                {
                    memcpy((uint8_t *)out_rec, (uint8_t *)rec, sizeof(iso9660_dir_record_t));
                }
                return 1;
            }
            offset += rec->length;
        }
        bytes_read += ISO9660_SECTOR_SIZE;
    }
    return 0;
}

// Helper: Get next path component and advance pointer
static uint8_t * next_path_component(uint8_t * path, uint8_t * out_len)
{
    while (*path == '/' || *path == '\\')
    {
        path++; // skip leading slashes
    }

    if (*path == 0)
    {
        *out_len = 0; return NULL;
    }

    uint8_t * start = path;

    while (*path && *path != '/' && *path != '\\')
    {
        path++;
    }

    *out_len = path - start;

    return start;
}

uint8_t iso9660_open(uint8_t filename[])
{
    static uint8_t sector[ISO9660_SECTOR_SIZE];

    // Read sector 16 (Primary Volume Descriptor)
    ide_read_sectors(1, 1, 16, 0, (uint32_t)sector);

    iso9660_pvd_t * pvd = (iso9660_pvd_t *)sector;
    if (pvd->type != ISO9660_VD_PRIMARY)
    {
        // Not a primary volume descriptor
        return 0xFF; // Fail
    }

    // Root dir record is at pvd->root_directory_record[0..33]
    iso9660_dir_record_t root_dir;
    memcpy((uint8_t *)&root_dir, (uint8_t *)pvd->root_directory_record, sizeof(iso9660_dir_record_t));
    uint32_t dir_lba = root_dir.extent_location_le;
    uint32_t dir_size = root_dir.data_length_le;
    uint8_t * path = filename;
    uint8_t comp_len;
    iso9660_dir_record_t cur_dir = root_dir;

    int max_depth = 32; // Prevent infinite loop in case of malformed path
    int depth = 0;
    while (depth++ < max_depth)
    {
        uint8_t *comp = next_path_component(path, &comp_len);
        if (!comp || comp_len == 0)
        {
            // Path ended, open this file/dir
            int handle = alloc_file_handle();
            if (handle < 0) return 0xFF;
            open_files[handle].in_use = 1;
            open_files[handle].extent_lba = cur_dir.extent_location_le;
            open_files[handle].size = cur_dir.data_length_le;
            open_files[handle].offset = 0;
            return handle;
        }
        // Search for this component in current directory
        iso9660_dir_record_t found;
        if (!find_in_directory(cur_dir.extent_location_le, cur_dir.data_length_le, comp, comp_len, &found))
        {
            return 0xFF;
        }
        // If this is the last component, open file
        path = comp + comp_len;
        // If not last, must be a directory
        if (next_path_component(path, &comp_len) && !(found.file_flags & ISO9660_FILE_FLAG_DIRECTORY)) {
            return 0xFF;
        }
        cur_dir = found;
    }
    // If we exit the loop, something went wrong
    return 0xFF;

    UNUSED(dir_lba);
    UNUSED(dir_size);
}

uint8_t iso9660_read(uint8_t file_descriptor, uint32_t offset, uint32_t size, uint8_t buffer[])
{
    if (file_descriptor >= 127 || !open_files[file_descriptor].in_use)
    {
        return 0xFF;
    }

    iso9660_file_handle_t * fh = &open_files[file_descriptor];

    if (offset >= fh->size)
    {
        return 0; // No data to read
    }

    // Clamp size if it goes beyond EOF
    if (offset + size > fh->size)
    {
        size = fh->size - offset;
    }

    uint32_t first_lba = fh->extent_lba + (offset / ISO9660_SECTOR_SIZE);
    uint32_t first_offset = offset % ISO9660_SECTOR_SIZE;
    uint32_t bytes_left = size;
    uint8_t sector[ISO9660_SECTOR_SIZE];
    uint32_t buf_pos = 0;

    while (bytes_left > 0)
    {
        ide_read_sectors(0, 1, first_lba, 0, (uint32_t)sector);

        uint32_t copy_offset = (buf_pos == 0) ? first_offset : 0;
        uint32_t copy_len = ISO9660_SECTOR_SIZE - copy_offset;
        if (copy_len > bytes_left)
            copy_len = bytes_left;

        memcpy(buffer + buf_pos, sector + copy_offset, copy_len);

        buf_pos += copy_len;
        bytes_left -= copy_len;
        first_lba++;
    }

    return size; // Return actual bytes read
}

uint8_t iso9660_close(uint8_t file_descriptor)
{
    if (file_descriptor >= 127 || !open_files[file_descriptor].in_use)
    {
        return 0xFF;
    }

    open_files[file_descriptor].in_use = 0;

    return 0;
}

