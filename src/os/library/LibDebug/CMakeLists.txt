add_library(
        KLibDebug

        lib/debug.asm
        lib/serial_port.cpp
)

target_link_libraries(KLibDebug PUBLIC os_options KLibC KLibCpp KLibHal gcc)

target_include_directories(KLibDebug PUBLIC include)