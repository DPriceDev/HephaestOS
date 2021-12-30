
set(BINUTILS_VERSION 2.37)
set(GCC_VERSION 11.2.0)
set(TARGET i386-elf)

set(PREFIX ${CMAKE_CURRENT_BINARY_DIR}/output)


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

include(ExternalProject)
include(ProcessorCount)

find_program(MAKE_EXE NAMES gmake nmake make)
set(PARALLEL_MAKE_JOBS 1)
ProcessorCount(PARALLEL_MAKE_JOBS)
message(Processor Count = ${PARALLEL_MAKE_JOBS})

ExternalProject_Add(binutils-${BINUTILS_VERSION}
        URL               https://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.gz
        URL_HASH          MD5=1e55743d73c100b7a0d67ffb32398cdb
        BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/binutils-${BINUTILS_VERSION}-prefix/src/binutils-${BINUTILS_VERSION}-build
        USES_TERMINAL_DOWNLOAD On
        USES_TERMINAL_CONFIGURE On
        USES_TERMINAL_BUILD On
        USES_TERMINAL_INSTALL On
        CONFIGURE_COMMAND export TARGET=${TARGET} && export PREFIX=${PREFIX} export CONFIG_DIR=${CMAKE_CURRENT_BINARY_DIR}/binutils-${BINUTILS_VERSION}-prefix/src/binutils-${BINUTILS_VERSION}/ && sh ${CMAKE_CURRENT_SOURCE_DIR}/configureBinutils.sh
        BUILD_COMMAND ${MAKE_EXE} -j ${PARALLEL_MAKE_JOBS}
        )

ExternalProject_Add(gcc-${GCC_VERSION}
        URL               https://ftp.gnu.org/gnu/gcc/gcc-11.2.0/gcc-${GCC_VERSION}.tar.gz
        URL_HASH          MD5=dc6886bd44bb49e2d3d662aed9729278
        DEPENDS binutils-${BINUTILS_VERSION}
        BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/gcc-${GCC_VERSION}-prefix/src/gcc-${GCC_VERSION}-build
        USES_TERMINAL_DOWNLOAD On
        USES_TERMINAL_CONFIGURE On
        USES_TERMINAL_BUILD On
        USES_TERMINAL_INSTALL On
        CONFIGURE_COMMAND export TARGET=${TARGET} && export PREFIX=${PREFIX} export CONFIG_DIR=${CMAKE_CURRENT_BINARY_DIR}/gcc-${GCC_VERSION}-prefix/src/gcc-${GCC_VERSION}/ && sh ${CMAKE_CURRENT_SOURCE_DIR}/configureGcc.sh
        BUILD_COMMAND ${MAKE_EXE} CFLAGS=-g0 CXXFLAGS=-g0 -j ${PARALLEL_MAKE_JOBS} all-gcc all-target-libgcc
        INSTALL_COMMAND ${MAKE_EXE} install-gcc install-target-libgcc
)

# todo: Add new command to build libstdc++ after gcc has compiled?