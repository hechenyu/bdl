#!/usr/bin/env bash

clear_cache=1
time_wait=300

for proc_num in 1 5 10 20 30 40
do
    (( clear_cache == 1 )) && ssh hexu@10.10.17.165 "sudo /home/hexu/clearcache.sh"
    (( clear_cache == 1 )) && ssh hexu@10.10.17.166 "sudo /home/hexu/clearcache.sh"
    (( clear_cache == 1 )) && sudo /mnt/lustressd/hx/clearcache.sh
    ./standard.samp.hdd.sh    ${proc_num} ${time_wait}
done
