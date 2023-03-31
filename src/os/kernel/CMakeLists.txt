add_executable(
        kernel.elf

        kernel_main.asm
        kernel.cpp
        thread/ThreadTable.cpp thread/ThreadIDProvider.cpp)

target_link_libraries(kernel.elf PRIVATE os_options) # project_warnings)
target_link_libraries(kernel.elf PUBLIC KLibC KLibCpp KLibDebug KLibHal gcc)

target_link_options(kernel.elf PRIVATE -T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld)

target_include_directories(kernel.elf PUBLIC .)

add_dependencies(kernel.elf CopySysRoot)