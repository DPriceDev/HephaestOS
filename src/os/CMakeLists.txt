
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> -felf32 -g -F dwarf -o <OBJECT> <SOURCE>")

add_library(os_options INTERFACE)
target_link_libraries(os_options INTERFACE project_options project_warnings)
target_compile_options(os_options INTERFACE -g3 -ffreestanding -nostdlib -fno-rtti -fno-exceptions -fmodules-ts -lgcc -fcommon -fpie)
target_link_options(os_options INTERFACE -ffreestanding -nostdlib -fcommon)

add_subdirectory(kernel)
add_subdirectory(boot)
add_subdirectory(library)
add_subdirectory(hal)