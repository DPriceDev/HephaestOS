#!/bin/bash

sh $CONFIG_DIR/configure CFLAGS='-g0 -O2' CXXFLAGS='-g0 -O2' --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx