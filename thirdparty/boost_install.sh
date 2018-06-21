#!/usr/bin/env bash

cmd_path=$(dirname $0)

echo $cmd_path
cd $cmd_path

#wget https://dl.bintray.com/boostorg/release/1.67.0/source/boost_1_67_0.tar.gz
tar xzvf boost_1_67_0.tar.gz
cd boost_1_67_0

./bootstrap.sh --with-toolset=gcc --with-libraries=all --with-python=python3
./b2 -j4 toolset=gcc cflags=-fPIC cxxflags=-fPIC link=static runtime-link=static threading=multi stage
