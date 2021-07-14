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

bits            32

global gdtFlush

; todo: Comment
gdtFlush:
                mov             eax, [esp+4]                    ; Get the pointer to the GDT, passed as a parameter.
                lgdt            [eax]                           ; Load the new GDT pointer
;                jmp             0x08:.flush                     ; 0x08 is the offset to our code segment: Far jump!
;.flush:
;                mov             ax, 0x10                        ; 0x10 is the offset in the GDT to our data segment
;                mov             ds, ax                          ; Load all data segment selectors
;                mov             es, ax
;                mov             fs, ax
;                mov             gs, ax
;                mov             ss, ax

                ret