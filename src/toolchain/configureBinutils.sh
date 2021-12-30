#!/bin/bash

sh $CONFIG_DIR/configure CFLAGS='-g0 -O2' CXXFLAGS='-g0 -O2' --target=$TARGET --prefix=$PREFIX --with-sysroot --disable-nls --disable-werror