#!/bin/bash

cd $CONFIG_DIR
patch -p1 < $PATCH_DIR/binutils.patch

cd $BUILD_DIR

sh $CONFIG_DIR/configure \
  CFLAGS='-g0 -O2' \
  CXXFLAGS='-g0 -O2' \
  --target=$TARGET \
  --prefix=$PREFIX \
  --with-build-sysroot=$SYSROOT \
  --with-sysroot=/ \
  --disable-nls \
  --disable-werror