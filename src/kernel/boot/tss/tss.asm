

global flushTss

flushTss:
	            mov             ax, (5 * 8) | 0                 ; fifth 8-byte selector, symbolically OR-ed with 0 to set the RPL (requested privilege level).
	            ltr             ax
	            ret

global jumpUserMode
extern testUserFunction
jumpUserMode:
                cli
                mov             ax, (4 * 8) | 3                 ; ring 3 data with bottom 2 bits set for ring 3
                mov             ds, ax
                mov             es, ax
                mov             fs, ax
                mov             gs, ax                          ; SS is handled by iret

                ; set up the stack frame iret expects
                mov             eax, esp
                push            (4 * 8) | 3                     ; data selector
                push            eax                             ; current esp
                pushfd                                          ; eflags
                or              dword [esp], 0x200              ; Set IF true in eflags, this enables interrupts on an IRET

                push            (3 * 8) | 3                     ; code selector (ring 3 code with bottom 2 bits set for ring 3)
                push            testUserFunction                ; instruction address to return to
                iret