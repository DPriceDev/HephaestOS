; Copyright (C) 2021 David Price - All Rights Reserved
; This file is part of HephaistOS.
;
; HephaistOS is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
;
; HephaistOS is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with HephaistOS.  If not, see <https://www.gnu.org/licenses/>.

;%include         "boot_config.asm"     need to include into nasm -p

bits            32

global loader:function (end - loader)
global stack_ptr

extern kernelMain, init, setupPaging
extern pageDirectory, kernelPageTable
extern kernelStart, kernelEnd, stackStart

; ------------------------------------------------------------- ;
; Multi-boot Header
; Variables
MODULEALIGN     equ             1 << 0
MEMINFO         equ             1 << 1
FLAGS           equ             MODULEALIGN | MEMINFO
MAGIC           equ             0x1BADB002
CHECKSUM        equ             -(MAGIC + FLAGS)

; header
section .multiboot
align 4
MultiBootHeader:
                dd              MAGIC                           ; dd defines Magic as a double word
                dd              FLAGS
                dd              CHECKSUM

section .text

section .bss

; ------------------------------------------------------------- ;
; Boot data section

section .boot
virtualBase     equ             0xC0000000

loader:
                mov             esi, eax
                mov             edi, ebx
                mov             esp, stackStart - virtualBase                ; set esp (register for stack pointer) as the stack pointer.

; initialize paging
                push            kernelEnd
                push            0
                push            virtualBase
                push            kernelPageTable
                push            pageDirectory
                call            setupPaging - virtualBase

                mov             esp, stackStart                             ; Set the stack pointer to the start of the stack.

                push            kernelEnd
                push            kernelStart
                push            virtualBase
                push            kernelPageTable + virtualBase
                push            pageDirectory + virtualBase
                push            stackStart
                ; todo Also need to map the vga buffer? maybe do that later on?
                push            esi                             ; push the magic number to the stack (2nd arg)
                push            edi                             ; push the multiboot info pointer to the stack (1st arg)
                lea             eax, init
                ; todo need to figure out if we want to call and return to halt loop, or jmp and never return
                push            eax
                jmp             eax
                ;call            eax

; ------------------------------------------------------------- ;
; Halts the CPU
halt:
                hlt
                jmp             halt
end: