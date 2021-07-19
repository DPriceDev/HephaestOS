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
extern handleException

%macro exceptionCodeRequest 1
                global          fireException%1
                push            %1
                jmp             commonExceptionHandler
%endmacro

%macro exceptionRequest 1
                global          fireException%1
                push            0
                push            %1
                jmp             commonExceptionHandler
%endmacro


%macro interruptRequest 1
                global          fireInterruptRequest%1
                push            %1
                jmp             commonInterruptHandler
%endmacro

commonInterruptHandler:
                pusha                                           ; push all registers AX, ECX, EDX, EBX, EBP, ESP, EBP, ESI, and EDI
                push            ds
                push            es
                push            fs
                push            gs
                mov             ax, 0x10
                mov             ds, ax
                mov             es, ax
                mov             fs, ax
                mov             gs, ax
                mov             ss, ax
                call            handleInterrupt                 ; Call the "handle interrupt" method

                pop             gs
                pop             fs
                pop             es
                pop             ds
                popa                                            ; pop all registers AX, ECX, EDX, EBX, EBP, ESP, EBP, ESI, and EDI (reversed)
                add             esp, 4                          ; clear
                iret

commonExceptionHandler:
                pusha                                           ; push all registers AX, ECX, EDX, EBX, EBP, ESP, EBP, ESI, and EDI
                push            ds
                push            es
                push            fs
                push            gs
                mov             ax, 0x10
                mov             ds, ax
                mov             es, ax
                mov             fs, ax
                mov             gs, ax
                mov             ss, ax
                call            handleException                 ; Call the "handle exception" method
                pop             gs
                pop             fs
                pop             es
                pop             ds
                popa                                            ; pop all registers AX, ECX, EDX, EBX, EBP, ESP, EBP, ESI, and EDI (reversed)
                add             esp, 4                          ; clear
                iret

fireException0:                 exceptionRequest 0              ;
fireException1:                 exceptionRequest 1              ;
fireException2:                 exceptionRequest 2              ;
fireException3:                 exceptionRequest 3              ;
fireException4:                 exceptionRequest 4              ;
fireException5:                 exceptionRequest 5              ;
fireException6:                 exceptionRequest 6              ;
fireException7:                 exceptionRequest 7              ;
fireException8:                 exceptionCodeRequest 8          ;
fireException9:                 exceptionRequest 9              ;
fireException10:                exceptionCodeRequest 10         ;
fireException11:                exceptionCodeRequest 11         ;
fireException12:                exceptionCodeRequest 12         ;
fireException13:                exceptionCodeRequest 13         ;
fireException14:                exceptionCodeRequest 14         ;
fireException15:                exceptionRequest 15             ;
fireException16:                exceptionRequest 16             ;
fireException17:                exceptionCodeRequest 17         ;
fireException18:                exceptionRequest 18             ;
fireException19:                exceptionRequest 19             ;
fireException20:                exceptionRequest 20             ;
fireException21:                exceptionRequest 21             ;
fireException22:                exceptionRequest 22             ;
fireException23:                exceptionRequest 23             ;
fireException24:                exceptionRequest 24             ;
fireException25:                exceptionRequest 25             ;
fireException26:                exceptionRequest 26             ;
fireException27:                exceptionRequest 27             ;
fireException28:                exceptionRequest 28             ;
fireException29:                exceptionRequest 29             ;
fireException30:                exceptionCodeRequest 30         ;
fireException31:                exceptionRequest 31             ;

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