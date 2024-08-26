#!/usr/bin/env bash

sudo apt install build-essential make sudo git cmake doxygen cppcheck valgrind -y 

git clone https://github.com/google/googletest.git
cd googletest && mkdir -p build && cd build && cmake .. && cmake --build . && \sudo cmake --install .