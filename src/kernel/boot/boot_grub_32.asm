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

extern kernelMain, init
extern gdtAddress, idtAddress
extern pageDirectory, kernelPageTable
extern kernelStart, kernelEnd

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

; ------------------------------------------------------------- ;
; Boot data section
section .boot

loader:
                mov             esp, stack_start - 0                ; set esp (register for stack pointer) as the stack pointer.

;               initialize idt and gdt (when entering straight in from grub)
                push            kernelEnd
                push            kernelStart
                push            kernelPageTable
                push            pageDirectory
                push            stack_start - 0
                push            eax                             ; push the magic number to the stack (2nd arg)
                push            ebx                             ; push the multiboot info pointer to the stack (1st arg)
                call            init - 0

                mov             ax, 0x10
                mov             ds, ax
                mov             es, ax
                mov             fs, ax
                mov             gs, ax
                mov             ss, ax

                sti
                call            kernelMain                      ; call the main kernal method.
                cli

; ------------------------------------------------------------- ;
; Halts the CPU
halt:
                hlt
                jmp             halt
end:

section .text

; ------------------------------------------------------------- ;
; BSS Memory Section
section .bss
stackSize:      equ             32798                           ; setup the stack size to be 16KB

align           16
stack_end:
resb            stackSize
stack_start: