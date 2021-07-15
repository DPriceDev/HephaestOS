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

extern handleInterrupt

%macro interruptRequest 1
                global fireInterruptRequest%1
                push            %1
                jmp             commonInterruptHandler
%endmacro

commonInterruptHandler:
                pusha                                           ; push all registers AX, ECX, EDX, EBX, EBP, ESP, EBP, ESI, and EDI
                call            handleInterrupt                 ; Call the "handle interrupt" method
                popa                                            ; pop all registers AX, ECX, EDX, EBX, EBP, ESP, EBP, ESI, and EDI (reversed)
                add             esp, 4                          ; clear
                iretd


fireInterruptRequest0:          interruptRequest 0              ;
fireInterruptRequest1:          interruptRequest 1              ;
fireInterruptRequest2:          interruptRequest 2              ;
fireInterruptRequest3:          interruptRequest 3              ;
fireInterruptRequest4:          interruptRequest 4              ;
fireInterruptRequest5:          interruptRequest 5              ;
fireInterruptRequest6:          interruptRequest 6              ;
fireInterruptRequest7:          interruptRequest 7              ;
fireInterruptRequest8:          interruptRequest 8              ;

