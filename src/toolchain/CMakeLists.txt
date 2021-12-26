
set(BINUTILS_VERSION 2.37)
set(GCC_VERSION 11.2.0)
set(TARGET i386-elf)

add_custom_target(buildToolChain DEPENDS output/bin/${TARGET}-g++ output/${TARGET}/bin/ld)

add_custom_command(
        OUTPUT output/bin/${TARGET}-g++ output/${TARGET}/bin/ld
        DEPENDS extracted/binutils-${BINUTILS_VERSION} extracted/gcc-${GCC_VERSION}
        USES_TERMINAL
        COMMAND cd ${CMAKE_SOURCE_DIR}/src/toolchain
        COMMAND ./buildToolChain.sh
)

add_custom_command(
        OUTPUT extracted/binutils-${BINUTILS_VERSION} extracted/gcc-${GCC_VERSION}
        DEPENDS download/binutils-${BINUTILS_VERSION}.tar.gz download/gcc-${GCC_VERSION}.tar.gz
        USES_TERMINAL
        COMMAND cd ${CMAKE_SOURCE_DIR}/src/toolchain
        COMMAND ./extractDependencies.sh
)

add_custom_command(
        OUTPUT download/binutils-${BINUTILS_VERSION}.tar.gz download/gcc-${GCC_VERSION}.tar.gz
        USES_TERMINAL
        COMMAND cd ${CMAKE_SOURCE_DIR}/src/toolchain
        COMMAND ./downloadDependencies.sh
)