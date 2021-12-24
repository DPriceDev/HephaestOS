# Boot

## 1 Description

## 2 Contents
- [1 Description](#1-description)
- [2 Contents](#2-contents)
- [3 Index](#3-Index)
- [4 How it currently works](#4-How-it-currently-works)
- [5 Flow](#5-flow)
- [6 Troubleshooting](#6-troubleshooting)
- [7 Reference](#7-references)

## 3 Index
- [Global Descriptor Table](gdt.md)
- [Interrupt Descriptor Table](idt.md)
- [Task State Segment](Tss.md)

## 4 How it currently works
The entry point is in the loader.

## 5 Flow
- 32 bit start
- load GDT
- load TSS
- load IDT
- Go To Main

## 6 Troubleshooting
- An invalid opcode ([Exception 6](idt.md)) can be thrown if the .text block in the
  [Linker Script](../../../../src/linker.ld) has a block/align size too small to fit all the bootloader into it.
  
- If " not accessible or not code segment" is returned, or the os crashes on an infinite loop, could
potentially be that the stack size is too small.

## 7 References