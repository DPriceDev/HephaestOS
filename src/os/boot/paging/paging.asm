; Copyright (C) 2022 David Price - All Rights Reserved
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

global loadPageDirectory
global enablePaging
global jumpToHigherKernel

; Takes a pointer to a Page directory and loads it into the cr3 register.
; This register is used to locate the page directory when paging is enabled.
loadPageDirectory:
                push            ebp
                mov             ebp, esp
                mov             eax, [esp + 8]
                mov             cr3, eax
                mov             esp, ebp
                pop             ebp
                ret

; enables paging in the app by retrieving the cr0 control register and setting
; the paging bit to true and saving it back to cr0.
enablePaging:
                mov             eax, cr0
                or              eax, 0x80000000
                mov             cr0, eax
                ret