ENTRY (loader)

virtualBase = 0xC0300000;

SECTIONS
{
    . += virtualBase;

    .text ALIGN(4k): AT(ADDR(.text) - virtualBase) {
        *(.text)
    }

    .rodata ALIGN(4k): AT(ADDR(.rodata) - virtualBase) {
        *(.rodata)
    }

    .data ALIGN(4k): AT(ADDR(.data) - virtualBase)  {
        *(.data)
    }

    .bss ALIGN(4k) : AT(ADDR(.bss) - virtualBase) {
        *(COMMON)
        *(.bss)
    }
}