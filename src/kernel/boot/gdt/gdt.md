[Back to Boot](../boot.md)
## Segments and Descriptors

### Data and Code Segments

### Global Descriptor Table

Todo...

### Global Descriptor

### Troubleshooting

- If the GDT is not flushed, interrupts will throw a "Cannot access code segment" error.
- The 'Access' and 'Flags' structs need to be in the correct bit order!
- For Data segments, the 'isConforming' Bit should be false, as the stack is required to grow down.
  This will generate a "read beyond limit" or "SS.Limit..." exception otherwise.

### Reference
