#!/usr/bin/env bash

cmd_path=$(dirname $0)

echo $cmd_path
cd $cmd_path && rm -rf ./build ./lib
