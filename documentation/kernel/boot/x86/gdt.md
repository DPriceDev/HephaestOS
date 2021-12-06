[Back to Boot](boot.md)

# Global Descriptors
- todo

## 1 Description
- todo

## 2 Contents
- [1 Description](#1-description)
- [2 Contents](#2-contents)
- [3 Segments and Descriptors](#3-Segments-and-Descriptors)
- [4 Data and Code Segments](#4-Data-and-Code-Segments)
- [5 Global Descriptor Table](#5-Global-Descriptor-Table)
  - [5.1 Global Descriptor](#51-Global-Descriptor)
- [6 Troubleshooting](#6-Troubleshooting)
- [7 Reference](#7-Reference)

## 3 Segments and Descriptors
- todo

## 4 Data and Code Segments
- todo

## 5 Global Descriptor Table
- todo

## 5.1 Global Descriptor
- todo

## 6 Troubleshooting
- If the GDT is not flushed, interrupts will throw a "Cannot access code segment" error.
- The 'Access' and 'Flags' structs need to be in the correct bit order!
- For Data segments, the 'isConforming' Bit should be false, as the stack is required to grow down.
  This will generate a "read beyond limit" or "SS.Limit..." exception otherwise.

## 7 Reference
- Segmentation https://wiki.osdev.org/Segmentation
- GDT https://wiki.osdev.org/Global_Descriptor_Table
- Tutorial https://wiki.osdev.org/GDT_Tutorial
