cmake_minimum_required(VERSION 3.20...3.31)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

project(HephaestOS LANGUAGES ASM_NASM CXX VERSION 1.0.0)
enable_language(ASM_NASM)

include(FetchContent)
FetchContent_Declare(_project_options URL https://github.com/aminya/project_options/archive/refs/tags/v0.40.0.zip)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

set(ENABLE_DOXYGEN OFF) # todo: look into what this generates
set(ENABLE_CLANG_TIDY ON) # todo: run through these errors
set(ENABLE_CPPCHECK ON) # todo: run through these errors

project_options(
        ENABLE_CACHE
        ${ENABLE_CPPCHECK}
        ${ENABLE_CLANG_TIDY}
        # ENABLE_INTERPROCEDURAL_OPTIMIZATION
        # ENABLE_NATIVE_OPTIMIZATION
        ${ENABLE_DOXYGEN}
        WARNINGS_AS_ERRORS
)

target_compile_features(project_options INTERFACE cxx_std_23 c_std_23)
set_target_properties(project_options PROPERTIES NASM_OBJ_FORMAT elf32-i386)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -o <OBJECT> <SOURCE>")

add_subdirectory(src)
add_subdirectory(toolchain)

#option(ENABLE_TESTING "Enable Test Builds" ON)

#set(CONAN_EXTRA_REQUIRES "")
#set(CONAN_EXTRA_OPTIONS "")
#
#set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES})

#include(cmake/Conan.cmake)
#run_conan()

#if(ENABLE_TESTING)
#    enable_testing()
#    message("Building HephaestOS Tests.")
#    add_subdirectory(unit-tests PRIVATE)
#endif()
