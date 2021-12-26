#!/bin/bash

export BINUTILS_VERSION="2.37"
export GCC_VERSION="11.2.0"

export TOOLCHAIN_DIR="/shareddrive/Projects/Prog_OS/New/HephaistOS/cmake-build-debug/src/toolchain"
export EXTRACTED_DIR="$TOOLCHAIN_DIR/extracted"
export BUILD_DIR="$TOOLCHAIN_DIR/build"
export OUTPUT_DIR="$TOOLCHAIN_DIR/output"

export PREFIX="$OUTPUT_DIR"
export TARGET=i386-elf

# Build environment
mkdir -p "$BUILD_DIR"
mkdir -p "$OUTPUT_DIR"

# Build binutils
cd $BUILD_DIR || exit 1
mkdir -p build-binutils

cd build-binutils || exit 1
$EXTRACTED_DIR/binutils-$BINUTILS_VERSION/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install

# Build gcc
cd $BUILD_DIR || exit 1
mkdir -p build-gcc

cd build-gcc || exit 1
$EXTRACTED_DIR/gcc-$GCC_VERSION/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc