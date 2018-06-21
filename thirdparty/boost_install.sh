#!/usr/bin/env bash

cmd_path=$(dirname $0)

echo $cmd_path
cd $cmd_path

tar xzvf boost_1_67_0.tar.gz || echo "tar boost_1_67_0.tar.gz fail"; exit 1
cd boost_1_67_0

#wget https://dl.bintray.com/boostorg/release/1.67.0/source/boost_1_67_0.tar.gz
./bootstrap.sh --with-toolset=gcc link=static runtime-link=static threading=multi stage --with-python=python3
./b2 -j4 cflags=-fPIC cxxflags=-fPIC
