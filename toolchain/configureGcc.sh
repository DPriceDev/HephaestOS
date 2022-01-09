#!/bin/bash

pushd .
cd $CONFIG_DIR
patch -p1 < $PATCH_DIR/gcc.patch
popd

sh $CONFIG_DIR/configure \
  CFLAGS='-g0 -O2' \
  CXXFLAGS='-g0 -O2' \
  --target=$TARGET \
  --prefix=$PREFIX \
  --with-sysroot=$SYSROOT \
  --with-newlib \
  --disable-nls \
  --enable-languages=c,c++