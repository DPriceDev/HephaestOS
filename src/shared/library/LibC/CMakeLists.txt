add_library(sharedLibC lib/string.cpp lib/stdio/sprintf.cpp)
target_include_directories(sharedLibC PUBLIC include)
target_link_libraries(sharedLibC INTERFACE project_options)