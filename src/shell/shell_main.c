/* DESCRIPTION: E93 Shell Main Source File
 * AUTHOR: Erdem Ersoy (eersoy93)
 * COPYRIGHT: Copyright (c) 2022-2025 Erdem Ersoy (eersoy93).
 * LICENSE: Licensed with GPLv2 License. See LICENSE file for details.
 */

#include "shell_main.h"

#include "command.h"
#include "gui.h"
#include "mb_header.h"
#include "mb_info.h"
#include "../libc/boolean.h"
#include "../libc/ending.h"
#include "../libc/function.h"
#include "../libc/init.h"
#include "../libc/io.h"
#include "../libc/memory.h"
#include "../libc/string.h"
#include "../libc/vga_libc.h"

void shell_main(uint32_t magic, struct multiboot_info * mb_info)
{
    uint8_t mode = 0;

    cls();

    if (magic != MULTIBOOT_VALID)
    {
        println((uint8_t *)"Invalid magic number!", ERROR_COLOR);

        end();
    }

    if (!(mb_info->flags & (1 << 2)))
    {
        println((uint8_t *)"Multiboot command line is not available!", ERROR_COLOR);

        end();
    }

    uint8_t * boot_cmdline = (uint8_t *)(mb_info->cmdline);
    uint8_t * mode_parameter = (uint8_t *)"mode=";
    uint8_t * mode_str = (uint8_t *)strstr(boot_cmdline, mode_parameter);

    if (mode_str != NULL)
    {
        mode_str += strlen(mode_parameter);
        mode = (uint8_t)atoi(mode_str);

        if (mode == CLI_MODE)
        {
            println((uint8_t *)"CLI mode enabled!", OUTPUT_COLOR);

            init(CLI_MODE);

            println((uint8_t *)"Welcome to E93!", OUTPUT_COLOR);
            println((uint8_t *)"Type HELP for help.", OUTPUT_COLOR);

            uint8_t buffer[0x1000] = {0};
            uint8_t fd = open_file((uint8_t *)"TEST.TXT");
            if (fd != 0xFF)
            {
                uint32_t bytes_read = read_file(fd, 0, 0x1000 - 1, buffer); // Use uint32_t for size
                if (bytes_read != 0xFF && bytes_read > 0)
                {
                    buffer[bytes_read] = 0; // Null terminate for safe printing
                    println(buffer, OUTPUT_COLOR);
                }
                else
                {
                    close_file(fd);
                    println((uint8_t *)"Failed to read file!", ERROR_COLOR);
                }
                close_file(fd);
            }
            else
            {
                println((uint8_t *)"Failed to open file!", ERROR_COLOR);
            }

            while(TRUE)
            {
                show_prompt();
                uint8_t * str = input();
                command_execute(str);
            }

            end();
        }
        else if (mode == GUI_MODE)
        {
            println((uint8_t *)"GUI mode enabled!", OUTPUT_COLOR);

            init(GUI_MODE);

            gui_init();

            end();
        }
        else
        {
            println((uint8_t *)"Invalid mode parameter specified!", ERROR_COLOR);

            end();
        }
    }
    else
    {
        println((uint8_t *)"Mode parameter not found in boot command line!", ERROR_COLOR);

        end();
    }
}

void show_prompt(void)
{
    print((uint8_t *)">", PROMPT_COLOR);
}
