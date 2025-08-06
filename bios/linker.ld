ENTRY(autumnkernelmain)

SECTIONS {
    . = 1M;

    .multiboot :
    {
        KEEP(*(.multiboot))
    }

    .text :
    {
        *(.text*)
    }

    .data :
    {
        *(.data*)
    }

    .bss :
    {
        *(.bss*)
        *(COMMON)
    }
}
