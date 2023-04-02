if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> -felf32 -g -F dwarf -o <OBJECT> <SOURCE>")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> -felf32 -O3 -o <OBJECT> <SOURCE>")
endif ()

add_library(user_options INTERFACE)
target_link_libraries(user_options INTERFACE project_options project_warnings)
target_compile_options(user_options INTERFACE -ffreestanding -nostdlib -fno-rtti -fno-exceptions -fmodules-ts -lgcc -fpie)

set(MY_DEBUG_OPTIONS -g3)
set(MY_RELEASE_OPTIONS -s -o3)
target_compile_options(user_options INTERFACE "$<$<CONFIG:DEBUG>:${MY_DEBUG_OPTIONS}>")
target_compile_options(user_options INTERFACE "$<$<CONFIG:RELEASE>:${MY_RELEASE_OPTIONS}>")

target_link_options(user_options INTERFACE -ffreestanding -nostdlib)

add_subdirectory(library)
add_subdirectory(initialTask)