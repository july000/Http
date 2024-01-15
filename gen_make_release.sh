#!/bin/bash

rm -rf build_release
mkdir -p build_release
cd build_release

cmake .. -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" 
