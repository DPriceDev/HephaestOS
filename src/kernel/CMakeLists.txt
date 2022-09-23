
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32-i386)

set(LINK ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld)
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} -T${LINK})
# todo: move to target compile options, also add to all klibs
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> -felf32 -g -F dwarf -o <OBJECT> <SOURCE>")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -ffreestanding -nostdlib -fno-rtti -fno-exceptions -fmodules-ts -lgcc -nostdlib -fcommon -std=c++20")

set(LINK_LIBRARIES -nostdlib)

message(linker: ${CMAKE_CXX_LINK_EXECUTABLE})

SET(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_CXX_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES> -ffreestanding -nostdlib -fcommon")

add_subdirectory(library)

add_executable(
        kernel.elf

        kernel.cpp
        boot/boot_grub_32.asm
        boot/boot_config.asm
        boot/idt/interrupt_descriptor_table.asm
        boot/idt/interrupts/interrupt_handler.asm
        boot/idt/exceptions/exception_handler.asm
        boot/gdt/global_descriptor_table.asm
        boot/tss/task_state_segment.asm
        terminal/Terminal.cpp
        drivers/video_buffer_display.cpp
        boot/init.cpp
        library/LibCpp/lib/pure_function.cpp
        boot/gdt/global_descriptor_table.cpp
        boot/idt/interrupt_descriptor_table.cpp
        boot/idt/interrupts/interrupt_handler.cpp
        boot/idt/pic/programmable_interrupt_controller.cpp
        boot/tss/task_state_segment.cpp
        boot/gdt/global_descriptor.cpp
        boot/idt/interrupt_descriptor.cpp
        boot/idt/exceptions/exception_handler.cpp
        boot/grub/memory_map.cpp
        boot/paging/paging.asm
        boot/paging/paging.cpp
        boot/serial/serial_port.cpp
        boot/io/io.asm
        boot/GlobalConstructors.cpp boot/memory/BootMemoryAllocator.cpp boot/memory/BootMemoryAllocator.h)

target_link_libraries(kernel.elf PRIVATE project_options) # project_warnings)
target_link_libraries(kernel.elf PUBLIC KLibC KLibCpp KLibDebug gcc)

target_include_directories(kernel.elf PUBLIC .)

add_dependencies(kernel.elf CopySysRoot)