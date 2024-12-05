ENTRY(shell_entry)
SECTIONS
{
    /* Load the kernel at 1 MB */
    . = 0x00100000;

    /* Place the Multiboot header at the very beginning */
    .multiboot ALIGN(4) : {
        KEEP(*(.multiboot))
    }

    /* Include the .text section */
    .text ALIGN(4) : {
        *(.text)
    }

    /* Read-only data */
    .rodata ALIGN(4) : {
        *(.rodata)
    }

    /* Data */
    .data ALIGN(4) : {
        *(.data)
    }

    /* BSS */
    .bss ALIGN(4) : {
        *(.bss)
        *(COMMON)
    }
}
