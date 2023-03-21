add_library(KLibC INTERFACE)
target_link_libraries(KLibC INTERFACE os_options sharedLibC gcc)
target_include_directories(KLibC INTERFACE include)