ENTRY (loader)
SECTIONS
{
  . = 1M;
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
    *(.data)
  }

  .bss BLOCK(4k) : ALIGN(4k) {
    *(COMMON)
    *(.bss)
  }
}