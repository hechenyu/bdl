#!/usr/bin/env bash

if (( $# != 2 ))
then
    echo "usage: $(basename $0) proc_num time_wait"
    exit 1
fi

proc_num=$1
time_wait=$2
node_name=$(uname -n | cut -d. -f1)

cmd=/mnt/lustressd/hx/base_dataset_loader2/perf_test/build/dataset/dataset_read_samp
seed=1530106820
root=/mnt/lustressd/hx/dataset${proc_num}
dir=/mnt/lustressd/hx/samp/ran.sdd/${proc_num}/${node_name}

i=1
while (( i <= proc_num ))
do
   label=dataset.samp.ran.ssd.${node_name}.${i}
   dataset=data${i}
   echo $i
   $cmd --seed ${seed} --label ${label} --root ${root} --dataset ${dataset} --dir ${dir} &
   (( i = i + 1 ))
done

sleep $time_wait
killall -9 dataset_read_samp
sleep 1
killall -9 dataset_read_samp
#wait

