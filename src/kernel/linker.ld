ENTRY (loader)

virtualBase = 0xC0000000;

SECTIONS
{
    /* Start data at 1mb */
    . = 1M;
    kernelStart = .;

    /* Section that contains the multiboot header */
    .multiboot BLOCK(4k): ALIGN (4k) {
        *(.multiboot)
    }

  .data BLOCK(4k): ALIGN (4k)  {
        startCtors = .;
        *(SORT(.ctors*))
        endCtors = .;

        *(.data)
  }
    /* Section that contains the boot code and paging constants */
    .boot BLOCK(4k): ALIGN (4k) {
        *(boot)

        /* Paging directory and kernel table with 4096 bytes each */
        pageDirectory = .;
        . += 0x1000;
        kernelPageTable = .;
        . += 0x1000;
    }

    /* Offset address for next sections by the virtual base */
    . += virtualBase;

    /* Section contains kernel code, with a virtual address offset by virtualBase
     * and the physical address the virtual address - virtualBase */
    .text ALIGN (4k): AT(ADDR(.text) - virtualBase) {
        *(.text)
    }

    .data ALIGN (4k): AT(ADDR(.data) - virtualBase)  {
        *(.data)
    }

    .rodata ALIGN (4k): AT(ADDR(.rodata) - virtualBase) {
        *(.rodata*)
    }

    .bss ALIGN (4k): AT(ADDR(.bss) - virtualBase) {
        *(COMMON)
        *(.bss)
        stackEnd = .;
        . += 0x8000;
        stackStart = .;
    }

    /* Symbol for the end of the kernel at its physical address */
    kernelEnd = . - virtualBase;
}