
add_executable(
        boot.elf

        boot_main.asm
        boot_higher.asm
        idt/interrupt_descriptor_table.asm
        idt/interrupts/interrupt_handler.asm
        idt/exceptions/exception_handler.asm
        gdt/global_descriptor_table.asm
        tss/task_state_segment.asm
        init.cpp

        gdt/global_descriptor_table.cpp
        idt/interrupt_descriptor_table.cpp
        idt/interrupts/interrupt_handler.cpp
        idt/pic/programmable_interrupt_controller.cpp
        tss/task_state_segment.cpp
        gdt/global_descriptor.cpp
        idt/interrupt_descriptor.cpp
        idt/exceptions/exception_handler.cpp

        paging/paging.asm
        paging/paging.cpp
        GlobalConstructors.cpp
        memory/boot_allocator.cpp
        elf/boot_elf_loader.cpp
        modules/module_loader.cpp
        elf/elf.h)

target_link_libraries(boot.elf PRIVATE os_options) # project_warnings)
target_link_libraries(boot.elf PUBLIC KLibC KLibCpp KLibDebug KLibHal gcc)

target_link_options(boot.elf PRIVATE -T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld)

target_include_directories(boot.elf PUBLIC .)