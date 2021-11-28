cmake_minimum_required(VERSION 3.17)

enable_language(ASM_NASM)
project(HephaistOS LANGUAGES ASM_NASM CXX VERSION 1.0.0)
include(cmake/StandardProjectSettings.cmake)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

add_library(project_warnings INTERFACE)

include(cmake/Cache.cmake)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

include(cmake/Doxygen.cmake)
#enable_doxygen()

include(cmake/StaticAnalyzers.cmake)

option(ENABLE_TESTING "Enable Test Builds" ON)

set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")

set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES})

include(cmake/Conan.cmake)
run_conan()

add_subdirectory(src)

if(ENABLE_TESTING)
    enable_testing()
    message("Building HephaistOS Tests.")
    add_subdirectory(unit-tests PRIVATE)
endif()
