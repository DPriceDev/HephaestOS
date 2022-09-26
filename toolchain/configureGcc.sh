#!/bin/bash

cd $CONFIG_DIR
patch -p1 < $PATCH_DIR/gcc.patch

cd $BUILD_DIR

sh $CONFIG_DIR/configure \
  CFLAGS='-g0 -O2' \
  CXXFLAGS='-g0 -O2' \
  --target=$TARGET \
  --prefix=$PREFIX \
  --with-build-sysroot=$SYSROOT \
  --with-sysroot=/ \
  --with-newlib \
  --disable-nls \
  --disable-hosted-libstdcxx \
  --enable-languages=c,c++