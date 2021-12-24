set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32-i386)

set(LINK ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld)
set(CMAKE_CXX_LINK_EXECUTABLE "ld -T${LINK} <CMAKE_CXX_LINK_FLAGS> -m elf_i386 <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> -felf32 -g -F dwarf -o <OBJECT> <SOURCE>")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -m32 -fno-use-cxa-atexit -ffreestanding -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-stack-protector -fmodules-ts")

add_executable(kernel.elf
        kernel/kernel.cpp
        kernel/boot/boot_grub_32.asm
        kernel/boot/boot_config.asm
        kernel/boot/idt/interrupt_descriptor_table.asm
        kernel/boot/idt/interrupts/interrupt_handler.asm
        kernel/boot/idt/exceptions/exception_handler.asm
        kernel/boot/gdt/global_descriptor_table.asm
        kernel/boot/paging/paging.cpp
        kernel/boot/paging/paging.asm
        kernel/boot/tss/task_state_segment.asm
        kernel/terminal/Terminal.cpp
        kernel/drivers/video_buffer_display.cpp
        kernel/boot/init.cpp
        kernel/lib/libcpp/pure_function.cpp
        kernel/boot/gdt/global_descriptor_table.cpp
        kernel/boot/idt/interrupt_descriptor_table.cpp
        kernel/boot/idt/interrupts/interrupt_handler.cpp
        kernel/boot/idt/pic/programmable_interrupt_controller.cpp
        kernel/boot/tss/task_state_segment.cpp kernel/boot/gdt/global_descriptor.cpp kernel/boot/idt/interrupt_descriptor.cpp kernel/boot/idt/exceptions/exception_handler.cpp kernel/boot/idt/exceptions/exception_handler.h kernel/boot/idt/model/handler_registers.h)

target_link_libraries(kernel.elf PRIVATE project_options) # project_warnings)
target_include_directories(kernel.elf PUBLIC .)

#add_custom_command(
#        TARGET kernel.elf POST_BUILD
#        COMMAND objcopy --only-keep-debug ${CMAKE_CURRENT_BINARY_DIR}/kernel.elf ${CMAKE_BINARY_DIR}/kernel.sym)

add_custom_target(HephaistOS.iso
        DEPENDS ${CMAKE_BINARY_DIR}/bin/kernel.elf
        COMMAND rm -r -f ${CMAKE_BINARY_DIR}/iso
        COMMAND mkdir ${CMAKE_BINARY_DIR}/iso
        COMMAND mkdir ${CMAKE_BINARY_DIR}/iso/boot
        COMMAND mkdir ${CMAKE_BINARY_DIR}/iso/boot/grub
        COMMAND echo ${CMAKE_BINARY_DIR}
        COMMAND cp ${CMAKE_BINARY_DIR}/bin/kernel.elf ${CMAKE_BINARY_DIR}/iso/boot/
        COMMAND echo 'set timeout-1' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo 'set default-0' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo 'menuentry \"HephaistOS\"{' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo ' multiboot /boot/kernel.elf' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo ' boot' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo '}' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND grub-mkrescue --output=${CMAKE_BINARY_DIR}/HephaistOS.iso ${CMAKE_BINARY_DIR}/iso
        COMMAND rm -rf ${CMAKE_BINARY_DIR}/iso)