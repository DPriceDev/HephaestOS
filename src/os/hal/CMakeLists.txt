add_library(KLibHal io/io.asm paging/page.cpp)

target_include_directories(KLibHal PUBLIC io)
target_link_libraries(KLibHal PRIVATE os_options)