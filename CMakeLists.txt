cmake_minimum_required(VERSION 3.15.0)

SET (CMAKE_CXX_COMPILER_WORKS 1)

cmake_policy(SET CMP0135 NEW)

enable_language(ASM_NASM)
project(HephaistOS LANGUAGES ASM_NASM CXX VERSION 1.0.0)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -o <OBJECT> <SOURCE>")

include(cmake/StandardProjectSettings.cmake)
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_23)
set_target_properties(project_options PROPERTIES NASM_OBJ_FORMAT elf32-i386)

add_library(project_warnings INTERFACE)

include(cmake/Cache.cmake)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

#include(cmake/Doxygen.cmake)
#enable_doxygen()
#SET(ENABLE_DOXYGEN TRUE)

include(cmake/StaticAnalyzers.cmake)

option(ENABLE_TESTING "Enable Test Builds" ON)

set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")

set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES})

#include(cmake/Conan.cmake)
#run_conan()

add_subdirectory(src)
add_subdirectory(toolchain)

#if(ENABLE_TESTING)
#    enable_testing()
#    message("Building HephaistOS Tests.")
#    add_subdirectory(unit-tests PRIVATE)
#endif()
