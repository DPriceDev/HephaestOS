cmake_minimum_required(VERSION 3.20...3.26)
if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_language(ASM_NASM)
project(HephaistOS LANGUAGES ASM_NASM CXX VERSION 1.0.0)

include(FetchContent)
FetchContent_Declare(_project_options URL https://github.com/aminya/project_options/archive/refs/tags/v0.26.3.zip)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

set(ENABLE_DOXYGEN OFF) # todo: look into what this generates
set(ENABLE_CLANG_TIDY OFF) # todo: run through these errors
set(ENABLE_CPPCHECK OFF) # todo: run through these errors

project_options(
        ENABLE_CACHE
        ${ENABLE_CPPCHECK}
        ${ENABLE_CLANG_TIDY}
#        ENABLE_INTERPROCEDURAL_OPTIMIZATION
        ${ENABLE_DOXYGEN}
        WARNINGS_AS_ERRORS
)

target_compile_features(project_options INTERFACE cxx_std_20)
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
#    message("Building HephaistOS Tests.")
#    add_subdirectory(unit-tests PRIVATE)
#endif()
