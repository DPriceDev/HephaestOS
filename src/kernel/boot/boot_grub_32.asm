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

extern kernelMain, init, callConstructors
extern gdtAddress, idtAddress

stackSize:      equ             32798                           ; setup the stack size to be 16KB

; ------------------------------------------------------------- ;
; BSS Memory Section
section .bss
align           16
stack_end:
resb            stackSize
stack_start:

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
section .text

loader:
                mov             esp, stack_start                ; set esp (register for stack pointer) as the stack pointer.

;               initialize idt and gdt (when entering straight in from grub)
                push            stack_start
                call            callConstructors
                push            eax                             ; push the magic number to the stack (2nd arg)
                push            ebx                             ; push the multiboot info pointer to the stack (1st arg)
                call            init

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
