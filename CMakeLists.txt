cmake_minimum_required(VERSION 3.17)

enable_language(ASM_NASM)

project(HephaistOS LANGUAGES ASM_NASM CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32-i386)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m elf_i386")

set(LINK ${CMAKE_HOME_DIRECTORY}/src/kernel/boot/linker.ld)
set(CMAKE_CXX_LINK_EXECUTABLE "ld -g -T${LINK} <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")

set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -f elf -g")
set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -f elf -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions")

add_executable(kernel.elf
        src/kernel/kernel.cpp
        src/kernel/boot/loader.asm
        src/kernel/boot/boot32.asm
        src/memory/memory.asm
        src/kernel/terminal/TextDisplay.cpp
        )
target_include_directories(kernel.elf PUBLIC src)

add_custom_command(
        TARGET kernel.elf POST_BUILD
        COMMAND objcopy --only-keep-debug ${CMAKE_BINARY_DIR}/kernel.elf ${CMAKE_BINARY_DIR}/kernel.sym)

add_custom_target(HephaistOS.iso
        DEPENDS kernel.elf
        COMMAND rm -r -f ${CMAKE_BINARY_DIR}/iso
        COMMAND mkdir ${CMAKE_BINARY_DIR}/iso
        COMMAND mkdir ${CMAKE_BINARY_DIR}/iso/boot
        COMMAND mkdir ${CMAKE_BINARY_DIR}/iso/boot/grub
        COMMAND echo ${CMAKE_BINARY_DIR}
        COMMAND cp ${CMAKE_BINARY_DIR}/kernel.elf ${CMAKE_BINARY_DIR}/iso/boot/
        COMMAND echo 'set timeout-0' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo 'set default-0' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo 'menuentry \"HephaistOS\"{' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo '  multiboot /boot/kernel.elf' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo ' boot' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND echo '}' >> ${CMAKE_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND grub-mkrescue --output=${CMAKE_BINARY_DIR}/HephaistOS.iso ${CMAKE_BINARY_DIR}/iso
        COMMAND rm -rf ${CMAKE_BINARY_DIR}/iso)
