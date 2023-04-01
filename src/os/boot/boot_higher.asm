; Copyright (C) 2023 David Price - All Rights Reserved
; This file is part of HephaestOS.
;
; HephaestOS is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
;
; HephaestOS is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with HephaestOS.  If not, see <https://www.gnu.org/licenses/>.

bits            32

global enterHigherKernel

extern kernelMain, init, callConstructors
extern pageDirectory, kernelPageTable
extern kernelStart, kernelEnd, stackStart

section .bss

; ------------------------------------------------------------- ;
; Boot data section

section .text
virtualBase     equ             0xC0000000

enterHigherKernel:
; Set the stack pointer to the start of the stack at the higher kernel address
                mov             esp, stackStart

; Initialize Global c++ Constructors
                call            callConstructors

; jump to c++ init function
                push            kernelEnd
                push            kernelStart
                push            virtualBase
                push            kernelPageTable + virtualBase
                push            pageDirectory + virtualBase
                push            stackStart

                push            esi                             ; push the magic number to the stack (2nd arg)
                add             edi, virtualBase
                push            edi                             ; push the multiboot info pointer to the stack (1st arg)
                call            init

; ------------------------------------------------------------- ;
; Halts the CPU
halt:
                hlt
                jmp             halt
end: