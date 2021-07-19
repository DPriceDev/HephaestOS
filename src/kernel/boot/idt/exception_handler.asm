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

extern handleException

; Macro to define an exception that passes an error code.
%macro exceptionCodeRequest 1
                global          fireException%1                 ; Make the exception accessible to the C++ table
                push            %1                              ; Push the desired exception code to the stack (parameter)
                jmp             commonExceptionHandler
%endmacro

; Macro to define an exception that does not recieve an error code.
%macro exceptionRequest 1
                global          fireException%1                 ; Make the exception accessible to the C++ table
                push            0                               ; Push a default error code.
                push            %1                              ; Push the desired exception code to the stack (parameter)
                jmp             commonExceptionHandler
%endmacro

; This common handler pushes all registers to the stack to pass to the c++ handler.
; It also switches to ring 0.
commonExceptionHandler:
                pusha                                           ; Push all registers AX, ECX, EDX, EBX, EBP, ESP, EBP, ESI, and EDI
                push            ds                              ; Push the segment registers DS, ES, FS, GS to the stack
                push            es
                push            fs
                push            gs

                mov             ax, 0x10                        ; If the exception is from a different ring, switch to data segment ring 0
                mov             ds, ax
                mov             es, ax
                mov             fs, ax
                mov             gs, ax
                mov             ss, ax

                call            handleException                 ; Call the "handle exception" method

                pop             gs                              ; Pop the save segment registers to restore the data segment and ring level
                pop             fs
                pop             es
                pop             ds
                popa                                            ; If the exception is from a different ring, switch to data segment ring 0
                add             esp, 4                          ; clear the exception code.

                iret

; Exception request definitons, each one defines its global function
fireException0:                 exceptionRequest        0       ; Division By Zero
fireException1:                 exceptionRequest        1       ; Debug
fireException2:                 exceptionRequest        2       ; Non Maskable Interrupt
fireException3:                 exceptionRequest        3       ; Breakpoint
fireException4:                 exceptionRequest        4       ; Into Detected Overflow
fireException5:                 exceptionRequest        5       ; Out of Bounds
fireException6:                 exceptionRequest        6       ; Invalid Opcode
fireException7:                 exceptionRequest        7       ; No Coprocessor
fireException8:                 exceptionCodeRequest    8       ; Double Fault
fireException9:                 exceptionRequest        9       ; Coprocessor Segment Overrun
fireException10:                exceptionCodeRequest    10      ; Bad TSS
fireException11:                exceptionCodeRequest    11      ; Segment Not Present
fireException12:                exceptionCodeRequest    12      ; Stack Fault
fireException13:                exceptionCodeRequest    13      ; General Protection Fault
fireException14:                exceptionCodeRequest    14      ; Page Fault
fireException15:                exceptionRequest        15      ; Unknown Interrupt
fireException16:                exceptionRequest        16      ; Coprocessor Fault
fireException17:                exceptionCodeRequest    17      ; Alignment Check
fireException18:                exceptionRequest        18      ; Machine Check
fireException19:                exceptionRequest        19      ; Reserved
fireException20:                exceptionRequest        20      ; Reserved
fireException21:                exceptionRequest        21      ; Reserved
fireException22:                exceptionRequest        22      ; Reserved
fireException23:                exceptionRequest        23      ; Reserved
fireException24:                exceptionRequest        24      ; Reserved
fireException25:                exceptionRequest        25      ; Reserved
fireException26:                exceptionRequest        26      ; Reserved
fireException27:                exceptionRequest        27      ; Reserved
fireException28:                exceptionRequest        28      ; Reserved
fireException29:                exceptionRequest        29      ; Reserved
fireException30:                exceptionCodeRequest    30      ; Reserved
fireException31:                exceptionRequest        31      ; Reserved