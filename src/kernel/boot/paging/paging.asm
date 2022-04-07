
global loadPageDirectory
global enablePaging

; todo comment
loadPageDirectory:
                push            ebp
                mov             ebp, esp
                mov             eax, [esp + 8]
                mov             cr3, eax
                mov             esp, ebp
                pop             ebp
                ret

; todo comment
enablePaging:
                ;push            ebp
                ;mov             ebp, esp
                mov             eax, cr0
                or              eax, 0x80000000
                xchg bx, bx
                mov             cr0, eax
                xchg bx, bx
                ;mov             esp, ebp
                ;nop
                ;pop             ebp
                nop
                ret