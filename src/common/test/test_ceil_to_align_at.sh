#!/usr/bin/env bash


for align in {2..16}
do
    for val in {1..100}
    do
        ./ceil_to_align_at $val $align
    done
done
