# Boot

### Contents
- [Global Descriptor Table](gdt/gdt.md)
- [Interrupt Descriptor Table](idt/idt.md)

### How it currently works?
The entry point is in the loader.

### Troubleshooting
- An invalid opcode ([Exception 6](idt/idt.md)) can be thrown if the .text block in the
  [Linker Script](../../linker.ld) has a block/align size too small to fit all the bootloader into it.
  
- If " not accessible or not code segment" is returned, or the os crashes on an infinite loop, could
potentially be that the stack size is too small.