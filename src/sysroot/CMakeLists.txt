add_custom_target(CopySysRoot
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/shared/ ${CMAKE_BINARY_DIR}/src/sysroot
        #        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/userspace/ ${CMAKE_BINARY_DIR}/src/sysroot
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/src/sysroot/ ${CMAKE_BINARY_DIR}/src/sysroot
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_BINARY_DIR}/src/sysroot/library/LibC/include ${CMAKE_BINARY_DIR}/src/sysroot/usr/include
        )