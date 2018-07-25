#!/usr/bin/env bash

debug=0

this_sh_path=$(dirname $0)

test $debug -gt 0 && echo "this_sh_path: $this_sh_path"

cd $this_sh_path
this_sh_path=$PWD

rm -rf ./build
rm -rf ./lib
rm -rf ./install
mkdir build
cd build
cmake ..
make
make install

#cd $this_sh_path

#cd gtest
#rm -rf ./build
#mkdir build
#cd build
#cmake ..
#make
#./ut_main
