ENTRY (loader)
SECTIONS
{
  . = 1M;
  .multiboot BLOCK(4k): ALIGN (4k) {
    *(.multiboot)
  }
  .text BLOCK(16k): ALIGN (16k) {
    *(.text)
  }

  .rodata BLOCK(8k): ALIGN (8k) {
    *(.rodata)
  }

  .data BLOCK(8k): ALIGN (8k)  {
    *(.data)
  }

  .bss BLOCK(8k) : ALIGN(8k) {
    *(COMMON)
    *(.bss)
  }
}