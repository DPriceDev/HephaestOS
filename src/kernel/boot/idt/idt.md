[Back to Boot](../boot.md)
## Interrupts

### Interrupt Descriptor Table (IDT)

### Programmable Interrupt Controller (PIC)

### Interrupt Handler

#### Interrupts

| IRQ   | Name                                      | Description                                       |
| :----: | :----                                    | :----                                             |
| 0      | Programmable Interrupt Timer Interrupt   |                                                   |
| 1      | Keyboard Interrupt                       |                                                   |
| 2      | Cascade                                  | (used internally by the two PICs. never raised)   |
| 3      | COM2                                     | (if enabled)                                      |
| 4      | COM1                                     | (if enabled)                                      |
| 5      | LPT2                                     | (if enabled)                                      |
| 6      | Floppy Disk                              |                                                   |
| 7      | LPT1 / Unreliable "spurious" interrupt   | (usually)                                         |
| 8      | CMOS real-time clock (if enabled)        |                                                   |
| 9      | Free for peripherals / legacy SCSI / NIC |                                                   |
| 10     | Free for peripherals / SCSI / NIC        |                                                   |
| 11     | Free for peripherals / SCSI / NIC        |                                                   |
| 12     | PS2 Mouse                                |                                                   |
| 13     | FPU / Coprocessor / Inter-processor      |                                                   |
| 14     | Primary ATA Hard Disk                    |                                                   |
| 15     | Secondary ATA Hard Disk                  |                                                   |

### Exception Handler

#### Exceptions
| Code   | Name                         |          Description      |
| :----: | :----                        | :----                     |
| 0      | Division By Zero             |                           |
| 1      | Debug                        |                           |
| 2      | Non Maskable Interrupt       |                           |
| 3      | Breakpoint                   |                           |
| 4      | Into Detected Overflow       |                           |
| 5      | Out of Bounds                |                           |
| 6      | Invalid Opcode               |                           |
| 7      | No Coprocessor               |                           |
| 8      | Double Fault                 |                           |
| 9      | Coprocessor Segment Overrun  |                           |
| 10     | Bad TSS                      |                           |
| 11     | Segment Not Present          |                           |
| 12     | Stack Fault                  |                           |
| 13     | General Protection Fault     |                           |
| 14     | Page Fault                   |                           |
| 15     | Unknown Interrupt            |                           |
| 16     | Coprocessor Fault            |                           |
| 17     | Alignment Check              |                           |
| 18     | Machine Check                |                           |
| 19-31  | Reserved                     |                           |

### Troubleshooting

### Reference
- Interrupts: https://wiki.osdev.org/Interrupts
- Exceptions: https://wiki.osdev.org/Exceptions