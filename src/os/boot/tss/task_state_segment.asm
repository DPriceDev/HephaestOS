; Copyright (C) 2021 David Price - All Rights Reserved
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
global loadTaskRegister
global jumpUserMode

;
extern testUserFunction

;
loadTaskRegister:
                mov             ax, word [esp+4]                    ; get segment passed to method and move it to ax.
                or              ax, word [esp+8]                    ; or the segment with the privilege to set the RPL (requested privilege level)

	            ltr             ax
	            ret