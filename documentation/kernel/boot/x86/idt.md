[Back to Boot](boot.md)
# Interrupts

## 1 Description
Interrupts are a set of hardware and software signals that will stop the current flow of the
program to allow a usually small piece of code (ISR - Interrupt Service Routine) to run in response 
to the interrupt. This allows hardware signals to trigger software responses.

## 2 Contents
- [1 Description](#1-description)
- [2 Contents](#2-contents)
- [3 Interrupt Descriptor Table](#3-Interrupt-Descriptor-Table-(IDT))
  - [3.1 Interrupt gate types](#31-Interrupt-gate-types)
- [4 Programmable Interrupt Controller](#4-Programmable-Interrupt-Controller-(PIC))
- [5 Interrupt Handler](#5-Interrupt Handler)
  - [5.1 Interrupts](#51-Interrupts)
- [6 Exception Handler](#6-Exception Handler)
  - [6.1 Exceptions](#61-Exceptions)
- [7 Troubleshooting](#7-Troubleshooting)
- [8 Reference](#8-Reference)

## 3 Interrupt Descriptor Table (IDT)
A table containing gates that describe a set of interrupts the system handles.

### 3.1 Interrupt gate types
- Interrupt Gate - Used for interrupts.
- Trap Gate - Used for exceptions, stays active when interrupts are disabled.
- Task Gate - Used for hardware task switching

## 4 Programmable Interrupt Controller (PIC)
The PIC provides the hardware system interrupts for the CPU.
There are two chips, main and secondary, which are connected together. The second chip
is connected via interrupt 2 and triggered by the main chip through this; this appears
to be referred to as **cascade**.
The PIC has to be reprogrammed as the interrupts 7 to 15 are overlapping the exceptions
0 to 8, and so these are mapped to 32 to 40 instead.

The process of re-mapping entails sending a number of commands to the command and data ports
on the PIC, as well as the offset for the main and secondary chips, as seen 
[here](../../../../src/kernel/boot/idt/pic/programmable_interrupt_controller.cpp).

Also, once an interrupt is fired, and then handled, an **end of interrupt** command is to
be sent to the main chip. If the interrupt code is higher than 8, then the interrupt
was handled on the secondary chip, and the **end of interrupt** command is sent to that chip
also.

- APIOC/AIOC appears to be relevant on more advanced CPUs.

## 5 Interrupt Handler
The interrupt handlers are mapped from 0 to 15 (interrupts start at zero but are remapped in the pic).
A specific method is called for a given exception, which is defined in [assembly](../../../../src/kernel/boot/idt/interrupts/interrupt_handler.asm).
The assembly file is set up to define the exceptions with a macro. The macro calls a common assembler 
method which pushes all the relevant registers to the stack to be passed as parameters to a C/C++ method.

The C/C++ method accepts the  register parameters in an [InterruptInfo](../../../../src/kernel/boot/idt/interrupts/interrupt_handler.h) struct.
Currently, the exception handler will print the interrupt code and associated description to the screen
and then return to the previous executing code.

### 5.1 Interrupts

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

## 6 Exception Handler
The exception handlers are mapped from 0 to 31 of interrupt descriptor table. A specific
method is called for a given exception, which is defined in [assembler](../../../../src/kernel/boot/idt/exceptions/exception_handler.asm).
The assembler file is set up to define the exceptions with a macro, either including or excluding an
error code. The macro calls a common assembler method which pushes all of the relevant registers to the 
stack to be passed as parameters to a C/C++ method.

The C/C++ method accepts the  register parameters in an [ExceptionInfo](../../../../src/kernel/boot/idt/interrupts/interrupt_handler.h) struct.
Currently, the exception handler will print the exception code and associated description to the screen
and loop indefinitely, blocking execution.

### 6.1 Exceptions
| Code   | Name                         |
| :----: | :----                        |
| 0      | Division By Zero             |
| 1      | Debug                        |
| 2      | Non Maskable Interrupt       |
| 3      | Breakpoint                   |
| 4      | Into Detected Overflow       |
| 5      | Out of Bounds                |
| 6      | Invalid Opcode               |
| 7      | No Coprocessor               |
| 8      | Double Fault                 |
| 9      | Coprocessor Segment Overrun  |
| 10     | Bad TSS                      |
| 11     | Segment Not Present          |
| 12     | Stack Fault                  |
| 13     | General Protection Fault     |
| 14     | Page Fault                   |
| 15     | Unknown Interrupt            |
| 16     | Coprocessor Fault            |
| 17     | Alignment Check              |
| 18     | Machine Check                |
| 19-31  | Reserved                     |

## 7 Troubleshooting
N/A

## 8 Reference
- PIC: https://wiki.osdev.org/8259_PIC
- Interrupts: https://wiki.osdev.org/Interrupts
- Exceptions: https://wiki.osdev.org/Exceptions