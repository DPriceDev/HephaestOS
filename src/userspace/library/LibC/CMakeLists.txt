add_library(LibC
        lib/crt0.cpp
)
target_link_libraries(LibC INTERFACE user_options sharedLibC gcc)
target_include_directories(LibC INTERFACE include)