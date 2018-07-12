
node_name=$(uname -n | cut -d. -f1)

sudo /mnt/lustressd/hx/clearcache.sh
/mnt/lustressd/hx/base_dataset_loader2/perf_test/build/dataset/standard_read_samp --conf standard.samp.hdd.conf --label standard.samp.hdd.${node_name}

sudo /mnt/lustressd/hx/clearcache.sh
/mnt/lustressd/hx/base_dataset_loader2/perf_test/build/dataset/dataset_read_samp --conf dataset.samp.ran.hdd.conf --label dataset.samp.ran.hdd.${node_name}

sudo /mnt/lustressd/hx/clearcache.sh
/mnt/lustressd/hx/base_dataset_loader2/perf_test/build/dataset/dataset_read_samp --conf dataset.samp.seq.hdd.conf --label dataset.samp.seq.hdd.${node_name}
