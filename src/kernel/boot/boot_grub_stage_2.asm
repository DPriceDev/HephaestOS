
extern kernelMain, init, setupPaging
extern gdtAddress, idtAddress
extern pageDirectory, kernelPageTable
extern kernelStart, kernelEnd
extern virtualBase

global higherBoot

section .text

.text
higherBoot:
;               initialize idt and gdt (when entering straight in from grub)
                xchg            bx, bx
                push            kernelEnd
                push            kernelStart
                push            virtualBase
                push            kernelPageTable
                push            pageDirectory
;                push            stack_start
                push            eax                             ; push the magic number to the stack (2nd arg)
                push            ebx                             ; push the multiboot info pointer to the stack (1st arg)
                xchg            bx, bx
                call            init

                xchg            bx, bx
                mov             ax, 0x10
                mov             ds, ax
                mov             es, ax
                mov             fs, ax
                mov             gs, ax
                mov             ss, ax

                sti
                call            kernelMain                      ; call the main kernal method.
                cli

; ------------------------------------------------------------- ;
; Halts the CPU
halt:
                hlt
                jmp             halt
end: