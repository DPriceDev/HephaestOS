[Back to Boot](boot.md)
# Task State Segment (TSS)

## 1 Description

## 2 Contents
- [1 Description](#1-description)
- [2 Contents](#2-contents)
- [3 Troubleshooting](#3-Troubleshooting)
- [4 Reference](#4-Reference)


## 3 Troubleshooting
- Limit in GDT Descriptor has to be 103 or more. 104 works as the default.
- Requires Code segments to be non-conforming to allow switching back from ring 3 to ring 0 and
updating the CPL (cs) and RPL (ss) to be 0 instead of 3.

## 4 Reference
- PIC: https://wiki.osdev.org/8259_PIC
- Interrupts: https://wiki.osdev.org/Interrupts
- Exceptions: https://wiki.osdev.org/Exceptions