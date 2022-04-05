add_library(KLibCpp lib/pure_function.cpp include/array.h)
target_include_directories(KLibCpp PUBLIC include)
target_link_libraries(KLibCpp PUBLIC sharedLibCpp)