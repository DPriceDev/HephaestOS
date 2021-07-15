# Boot

### How it currently works?
The entry point is in the loader.

### Global Descriptor Table

Todo...

#### Global Descriptor

- For Data segments, the 'isConforming' Bit should be false, as the stack is required to grow down. 
  This will generate a "read beyond limit" or "SS.Limit..." exception otherwise.
  
- The 'Access' and 'Flags' structs need to be in the correct bit order!

### Interrupt Descriptor Table

Todo...

#### Interrupt Descriptor

Todo...

### Troubleshooting

- If the GDT is not flushed, interrupts will throw a "Cannot access code segment" error.