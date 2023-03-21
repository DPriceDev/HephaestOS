
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32-i386)

set(LINK ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld)
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} -T${LINK})
# todo: move to target compile options, also add to all klibs
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> -felf32 -g -F dwarf -o <OBJECT> <SOURCE>")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -ffreestanding -nostdlib -lgcc -fno-rtti -fno-exceptions -fmodules-ts")

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
        modules/module_loader.cpp modules/module_loader.h)

target_link_libraries(boot.elf PRIVATE project_options) # project_warnings)

target_link_libraries(boot.elf PUBLIC KLibC KLibCpp KLibDebug KLibHal gcc)

target_include_directories(boot.elf PUBLIC .)