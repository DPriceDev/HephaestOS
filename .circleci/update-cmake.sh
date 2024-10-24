#!/bin/bash

wget https://github.com/Kitware/CMake/releases/download/v3.30.5/cmake-3.30.5-linux-x86_64.tar.gz
tar -zxvf cmake-3.30.5-linux-x86_64.tar.gz
cd cmake-3.30.5-linux-x86_64 || exit 1
sudo cp -r bin /usr/
sudo cp -r doc /usr/share/
sudo cp -r man /usr/share/
sudo cp -r share /usr/

cd ..
wget https://github.com/ninja-build/ninja/releases/download/v1.12.1/ninja-linux.zip
unzip ninja-linux.zip
cd ninja-linux || exit 1
sudo cp ninja /usr/bin