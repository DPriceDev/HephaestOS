#!/bin/bash

if [ -d "cmake-build-release/toolchain/output" ]
then
  exit 0
fi

sudo apt-get update
sudo apt-get install texinfo flex bison nasm graphviz doxygen ccache libmpfr-dev libmpc-dev doxygen ninja-build --no-install-recommends -y

wget https://github.com/Kitware/CMake/releases/download/v3.30.5/cmake-3.30.5-linux-x86_64.tar.gz
tar -zxvf cmake-3.30.5-linux-x86_64.tar.gz
cd cmake-3.30.5-linux-x86_64 || exit 1
sudo cp -r bin /usr/
sudo cp -r doc /usr/share/
sudo cp -r man /usr/share/
sudo cp -r share /usr/

cd .. || exit 1
mkdir -p cmake-build-release
cmake -DCMAKE_BUILD_TYPE=Release -B cmake-build-release
cmake --build cmake-build-release --target gcc-14.2.0