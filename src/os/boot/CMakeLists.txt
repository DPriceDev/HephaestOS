
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


        paging/paging.asm
        global_constructors.cpp
)

target_sources(boot.elf PUBLIC
        FILE_SET CXX_MODULES
        FILES
        boot.cxx
        elf/elf.cxx
        elf/elf_loader.cxx
        gdt/global_descriptor.cxx
        gdt/global_descriptor_table.cxx
        idt/exceptions/exception_handler.cxx
        idt/interrupt_descriptor_table.cxx
        idt/interrupt_descriptor.cxx
        idt/interrupts/interrupt_handler.cxx
        idt/pic/programmable_interrupt_controller.cxx
        idt/model/handler_registers.cxx
        grub/multiboot_info.cxx
        memory/boot_allocator.cxx
        modules/loader.cxx
        paging/paging.cxx
        paging/model/page_directory_entry.cxx
        paging/model/page_table_entry.cxx
        tss/task_state_segment.cxx
)

target_link_libraries(boot.elf PRIVATE os_options) # project_warnings)
target_link_libraries(boot.elf PUBLIC KLibC KLibCpp KLibDebug KLibHal gcc)

target_link_options(boot.elf PRIVATE -T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld)

target_include_directories(boot.elf PUBLIC .)