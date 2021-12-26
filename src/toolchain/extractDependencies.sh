#!/bin/bash

export BINUTILS_VERSION="2.37"
export GCC_VERSION="11.2.0"

export TOOLCHAIN_BUILD_DIR="/shareddrive/Projects/Prog_OS/New/HephaistOS/cmake-build-debug/src/toolchain"
export EXTRACTED_DIR="$TOOLCHAIN_BUILD_DIR/extracted"
export DOWNLOAD_DIR="$TOOLCHAIN_BUILD_DIR/download"

mkdir -p "$EXTRACTED_DIR"
cd $EXTRACTED_DIR || exit 1

if [ ! -d "binutils-$BINUTILS_VERSION" ]; then
  echo extracting bin utils $BINUTILS_VERSION
  tar -xzf $DOWNLOAD_DIR/binutils-$BINUTILS_VERSION.tar.gz
else
  echo bin utils 2.37 extracted directory exists
fi

if [ ! -d "gcc-$GCC_VERSION" ]; then
  echo extracting gcc $GCC_VERSION
  tar -xzf $DOWNLOAD_DIR/gcc-$GCC_VERSION.tar.gz
else
  echo gcc $GCC_VERSION extracted directory exists
fi
