add_library(KLibC INTERFACE)
target_link_libraries(KLibC INTERFACE sharedLibC gcc)
target_include_directories(KLibC INTERFACE include)