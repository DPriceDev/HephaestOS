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

; Definitions of methods that can be called by external code.
global loadGdtTable

; Takes a pointer to a GDT size and address (in that order) and loads it into the gdt register,
; then calls the flush method to reload the GDT to update the CPU.
loadGdtTable:
                mov             eax, [esp+4]                    ; Get the pointer to the GDT, passed as a parameter.
                lgdt            [eax]                           ; Load the new GDT pointer
                call            flushGdtTable                   ;
                ret

; Called to enable the Global descriptor table loaded in the gdt register.
flushGdtTable:
                mov             ax, 0x10                        ; Move the kernel data segment into the ex register.
                mov             ds, ax                          ; Move the kernel data segment into the cpu segment registers.
                mov             es, ax
                mov             fs, ax
                mov             gs, ax
                mov             ss, ax
                jmp             0x08:.flush                     ; Far jump to the kernel code segment. This reloads the gdt.

; Far jump destination. Returns to the calling code.
.flush:
                ret