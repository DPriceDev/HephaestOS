
set(BINUTILS_VERSION 2.37)
set(GCC_VERSION 12.2.0)
set(TARGET i386-pc-hephaistos)
set(SYSROOT ${CMAKE_BINARY_DIR}/src/sysroot)
set(PATCH_DIR ${CMAKE_SOURCE_DIR}/toolchain/patches)

set(PREFIX ${CMAKE_CURRENT_BINARY_DIR}/output)

include(ExternalProject)
include(ProcessorCount)

find_program(MAKE_EXE NAMES gmake nmake make)
set(PARALLEL_MAKE_JOBS 1)
ProcessorCount(PARALLEL_MAKE_JOBS)
message(Processor Count = ${PARALLEL_MAKE_JOBS})

ExternalProject_Add(binutils-${BINUTILS_VERSION}
        URL             https://ftp.gnu.org/gnu/binutils/binutils-${BINUTILS_VERSION}.tar.gz
        URL_HASH        MD5=1e55743d73c100b7a0d67ffb32398cdb
        BINARY_DIR      ${CMAKE_CURRENT_BINARY_DIR}/binutils-${BINUTILS_VERSION}-prefix/src/binutils-${BINUTILS_VERSION}-build
        CONFIGURE_COMMAND
            export PATCH_DIR=${PATCH_DIR}
            && export SYSROOT=${SYSROOT}
            && export TARGET=${TARGET}
            && export PREFIX=${PREFIX}
            && export CONFIG_DIR=${CMAKE_CURRENT_BINARY_DIR}/binutils-${BINUTILS_VERSION}-prefix/src/binutils-${BINUTILS_VERSION}/
            && sh ${CMAKE_CURRENT_SOURCE_DIR}/configureBinutils.sh
        BUILD_COMMAND
            ${MAKE_EXE} -j ${PARALLEL_MAKE_JOBS}
        USES_TERMINAL_DOWNLOAD  On
        USES_TERMINAL_PATCH     On
        USES_TERMINAL_CONFIGURE On
        USES_TERMINAL_BUILD     On
        USES_TERMINAL_INSTALL   On
)

ExternalProject_Add(gcc-${GCC_VERSION}
        URL             https://ftp.gnu.org/gnu/gcc/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.gz
        URL_HASH        MD5=d7644b494246450468464ffc2c2b19c3
        DEPENDS         binutils-${BINUTILS_VERSION} CopySysRoot
        BINARY_DIR      ${CMAKE_CURRENT_BINARY_DIR}/gcc-${GCC_VERSION}-prefix/src/gcc-${GCC_VERSION}-build
        CONFIGURE_COMMAND
            export PATCH_DIR=${PATCH_DIR}
            && export SYSROOT=${SYSROOT}
            && export TARGET=${TARGET}
            && export PREFIX=${PREFIX} export CONFIG_DIR=${CMAKE_CURRENT_BINARY_DIR}/gcc-${GCC_VERSION}-prefix/src/gcc-${GCC_VERSION}/
            && sh ${CMAKE_CURRENT_SOURCE_DIR}/configureGcc.sh
        BUILD_COMMAND
            ${MAKE_EXE} CFLAGS=-g0 CXXFLAGS=-g0 -j ${PARALLEL_MAKE_JOBS} all-gcc all-target-libgcc
        INSTALL_COMMAND
            ${MAKE_EXE} install-gcc install-target-libgcc
        USES_TERMINAL_DOWNLOAD  On
        USES_TERMINAL_PATCH     On
        USES_TERMINAL_CONFIGURE On
        USES_TERMINAL_BUILD     On
        USES_TERMINAL_INSTALL   On
)

add_custom_command(TARGET gcc-${GCC_VERSION}
        POST_BUILD
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/gcc-${GCC_VERSION}-prefix/src/gcc-${GCC_VERSION}-build
        COMMAND ${MAKE_EXE} CFLAGS=-g0 CXXFLAGS=-g0 -j ${PARALLEL_MAKE_JOBS} all-target-libstdc++-v3
        COMMAND ${MAKE_EXE} install-target-libstdc++-v3
        USES_TERMINAL
)