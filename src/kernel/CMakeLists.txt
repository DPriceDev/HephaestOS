
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
)

target_link_libraries(kernel.elf PRIVATE project_options) # project_warnings)
target_link_libraries(kernel.elf PUBLIC KLibC KLibCpp KLibDebug gcc)

target_include_directories(kernel.elf PUBLIC .)

add_dependencies(kernel.elf CopySysRoot)