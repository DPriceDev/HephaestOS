ENTRY (loader)
SECTIONS
{
    . = 1M;
    kernelMemoryStart = .;

    .multiboot BLOCK(4k): ALIGN (4k) {
        *(.multiboot)
    }
    .text BLOCK(4k): ALIGN (4k) {
        *(.text)
    }

    .rodata BLOCK(4k): ALIGN (4k) {
        *(.rodata)
    }

    .data BLOCK(4k): ALIGN (4k)  {
        startCtors = .;
        *(SORT(.ctors*))
        endCtors = .;

        *(.data)
    }

    .bss BLOCK(4k) : ALIGN(4k) {
        *(COMMON)
        *(.bss)
    }
    kernelMemoryEnd = .;
}