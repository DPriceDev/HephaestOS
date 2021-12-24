
#add_library(kernel_boot
#        boot_grub_32.asm
#        boot_config.asm
#        idt/interrupt_descriptor_table.asm
#        idt/interrupt_handler.asm
#        idt/exception_handler.asm
#        gdt/global_descriptor_table.asm
#        tss/task_state_segment.asm
#        init.cpp
#        gdt/global_descriptor_table.cpp
#        idt/interrupt_descriptor_table.cpp
#        idt/interrupt_handler.cpp
#        idt/programmable_interrupt_controller.cpp
#)
#
#target_include_directories(kernel_boot PUBLIC .)