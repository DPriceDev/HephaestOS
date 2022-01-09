#!/bin/bash

pushd .
cd $CONFIG_DIR
patch -p1 < $PATCH_DIR/binutils.patch
popd

sh $CONFIG_DIR/configure CFLAGS='-g0 -O2' CXXFLAGS='-g0 -O2' --target=$TARGET --prefix=$PREFIX --with-sysroot=$SYSROOT --disable-nls --disable-werror