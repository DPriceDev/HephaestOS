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

global readFromPort, writeToPort ;, waitForIO

readFromPort:
                mov             edx, [esp+4]
                in              al, dx
                ret

writeToPort:
                mov             edx, [esp+4]
                mov             eax, [esp+8]
                out             dx, al
                ret