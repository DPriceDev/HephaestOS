set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32-i386)

set(LINK ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld)
set(CMAKE_CXX_LINK_EXECUTABLE "ld -g -T${LINK} <CMAKE_CXX_LINK_FLAGS> -m elf_i386 <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")

set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> -felf32 -g -o <OBJECT> <SOURCE>")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -m32 -fno-use-cxa-atexit -ffreestanding -nostdlib -fno-builtin -fno-rtti -fno-exceptions")

add_executable(kernel.elf
        kernel/kernel.cpp
        kernel/boot/loader.asm
        kernel/terminal/Terminal.cpp
        kernel/drivers/video_buffer_display.cpp
        kernel/boot/init.cpp
        kernel/klibc/pure_function.cpp)
target_link_libraries(kernel.elf PRIVATE project_options project_warnings)
target_include_directories(kernel.elf PUBLIC .)

add_custom_command(
        TARGET kernel.elf POST_BUILD
        COMMAND objcopy --only-keep-debug ${CMAKE_CURRENT_BINARY_DIR}/kernel.elf ${CMAKE_BINARY_DIR}/kernel.sym)

add_custom_target(HephaistOS.iso
        DEPENDS kernel.elf
        COMMAND rm -r -f ${CMAKE_BINARY_DIR}/iso
        COMMAND mkdir ${CMAKE_BINARY_DIR}/iso
        COMMAND mkdir ${CMAKE_BINARY_DIR}/iso/boot
        COMMAND mkdir ${CMAKE_BINARY_DIR}/iso/boot/grub
        COMMAND echo ${CMAKE_BINARY_DIR}
        COMMAND cp ${CMAKE_BINARY_DIR}/kernel.elf ${CMAKE_BINARY_DIR}/iso/boot/
        COMMAND echo 'set timeout-1' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo 'set default-0' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo 'menuentry \"HephaistOS\"{' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo ' multiboot /boot/kernel.elf' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo ' boot' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo '}' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND grub-mkrescue --output=${CMAKE_BINARY_DIR}/HephaistOS.iso ${CMAKE_BINARY_DIR}/iso
        COMMAND rm -rf ${CMAKE_BINARY_DIR}/iso)