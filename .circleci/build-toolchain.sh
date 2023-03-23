#!/bin/bash

if [ -d "/path/to/dir" ]
then
  exit 0
fi

sudo apt-get update
sudo apt-get install texinfo flex bison nasm graphviz doxygen ccache libmpfr-dev libmpc-dev doxygen --no-install-recommends -y

wget https://github.com/Kitware/CMake/releases/download/v3.26.0/cmake-3.26.0-linux-x86_64.tar.gz
tar -zxvf cmake-3.26.0-linux-x86_64.tar.gz
cd cmake-3.26.0-linux-x86_64 || exit 1
sudo cp -r bin /usr/
sudo cp -r doc /usr/share/
sudo cp -r man /usr/share/
sudo cp -r share /usr/

mkdir -p cmake-build-release
cmake -DCMAKE_BUILD_TYPE=Release -B cmake-build-release
cmake --build cmake-build-release --target gcc-12.2.0