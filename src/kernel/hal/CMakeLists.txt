add_library(KLibHal io/io.asm paging/page.h paging/page.cpp)
target_include_directories(KLibHal PUBLIC io)