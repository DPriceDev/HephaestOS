add_library(KLibCpp lib/pure_function.cpp)
target_include_directories(KLibCpp PRIVATE include)
target_link_libraries(KLibCpp PUBLIC sharedLibCpp)