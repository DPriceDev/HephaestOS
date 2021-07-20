
if(CONAN_CATCH2_ROOT_DEBUG)
    include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else()
    include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif()

add_library(hephaist_os_catch_main STATIC catch_test_runner.cpp)
target_link_libraries(hephaist_os_catch_main
        PRIVATE
        project_options
        project_warnings
        CONAN_PKG::catch2)

add_executable(hephaist_os_unit_tests kernel/klibc/stdio/sprintf_test.cpp)

target_link_libraries(hephaist_os_unit_tests
        PRIVATE
        hephaist_os_catch_main
        project_options
        project_warnings
        CONAN_PKG::catch2)

target_include_directories(hephaist_os_unit_tests
        PRIVATE
        ../src)

catch_discover_tests(
        hephaist_os_unit_tests
        TEST_PREFIX
        "unittests."
        REPORTER
        xml
        OUTPUT_DIR
        .
        OUTPUT_PREFIX
        "unittests."
        OUTPUT_SUFFIX
        .xml)