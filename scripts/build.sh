#!/bin/bash
cd ..
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make

echo "Attempting to Build the Project ..."