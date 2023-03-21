add_library(
        KLibDebug

        lib/debug.asm
        lib/serial_port.cpp
)

target_link_libraries(KLibDebug PUBLIC KLibC KLibCpp KLibHal gcc)

target_include_directories(KLibDebug PUBLIC include)