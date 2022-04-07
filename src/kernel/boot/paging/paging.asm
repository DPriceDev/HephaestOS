
global loadPageDirectory
global enablePaging

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
                push            ebp
                mov             ebp, esp
                mov             eax, cr0
                or              eax, 0x80000000
                mov             cr0, eax
                mov             esp, ebp
                pop             ebp
                ret