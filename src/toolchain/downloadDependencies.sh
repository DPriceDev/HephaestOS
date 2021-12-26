#!/bin/bash

export BINUTILS_VERSION="2.37"
export GCC_VERSION="11.2.0"

export BIN_UTILS_SOURCE_URL="https://ftp.gnu.org/gnu/binutils/binutils-$BINUTILS_VERSION.tar.gz"
export GCC_SOURCE_URL="https://ftp.gnu.org/gnu/gcc/gcc-11.2.0/gcc-$GCC_VERSION.tar.gz"

export TOOLCHAIN_BUILD_DIR="/shareddrive/Projects/Prog_OS/New/HephaistOS/cmake-build-debug/src/toolchain"
export DOWNLOAD_DIR="$TOOLCHAIN_BUILD_DIR/download"

mkdir -p "$DOWNLOAD_DIR"
cd $DOWNLOAD_DIR || exit 1

if [ ! -f "binutils-$BINUTILS_VERSION.tar.gz" ]; then
  echo downloading bin utils $BINUTILS_VERSION
  wget -c $BIN_UTILS_SOURCE_URL --show-progress
else
  echo bin utils $BINUTILS_VERSION tar downloaded already
fi

if [ ! -f "gcc-$GCC_VERSION.tar.gz" ]; then
  echo downloading gcc $GCC_VERSION
  wget -c $GCC_SOURCE_URL --show-progress
else
  echo gcc $GCC_VERSION tar downloaded already
fi
