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

;
extern handleInterrupt

; Macro to define an interrupt request for the given integer.
%macro interruptRequest 1
                global          fireInterruptRequest%1
                push            %1
                jmp             commonInterruptHandler
%endmacro

; This common handler pushes all registers to the stack to pass to the c++ handler.
; It also switches to ring 0.
commonInterruptHandler:
                pushad                                          ; Push all registers EAX, ECX, EDX, EBX, ESP, EBP, ESI, and EDI
                xor             eax, eax                        ; Push the segment registers DS, ES, FS, GS to the stack
                mov             ax, ds
                push            eax
                mov             ax, es
                push            eax
                mov             ax, fs
                push            eax
                mov             ax, gs
                push            eax

                mov             ax, 0x10                        ; If the exception is from a different priv level, switch to data segment ring 0
                mov             ds, ax
                mov             es, ax
                mov             fs, ax
                mov             gs, ax
                mov             ss, ax

                call            handleInterrupt                 ; Call the "handle interrupt" method

                pop             gs                              ; Pop the save segment registers to restore the data segment and priv level level
                pop             fs
                pop             es
                pop             ds
                popad                                           ; Return previous register AX, ECX, EDX, EBX, EBP, ESP, EBP, ESI, and EDI
                add             esp, 4                          ; clear the interrupt code.

                iretd

;
fireInterruptRequest0:          interruptRequest 0              ;
fireInterruptRequest1:          interruptRequest 1              ;
fireInterruptRequest2:          interruptRequest 2              ;
fireInterruptRequest3:          interruptRequest 3              ;
fireInterruptRequest4:          interruptRequest 4              ;
fireInterruptRequest5:          interruptRequest 5              ;
fireInterruptRequest6:          interruptRequest 6              ;
fireInterruptRequest7:          interruptRequest 7              ;
fireInterruptRequest8:          interruptRequest 8              ;
fireInterruptRequest9:          interruptRequest 9              ;
fireInterruptRequest10:         interruptRequest 10             ;
fireInterruptRequest11:         interruptRequest 11             ;
fireInterruptRequest12:         interruptRequest 12             ;
fireInterruptRequest13:         interruptRequest 13             ;
fireInterruptRequest14:         interruptRequest 14             ;
fireInterruptRequest15:         interruptRequest 15             ;