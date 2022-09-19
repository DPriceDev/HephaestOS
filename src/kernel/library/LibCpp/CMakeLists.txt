add_library(KLibCpp lib/pure_function.cpp lib/format.cpp)
target_include_directories(KLibCpp PUBLIC include)
target_link_libraries(KLibCpp PUBLIC sharedLibCpp)