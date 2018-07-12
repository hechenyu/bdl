
sudo /mnt/lustressd/hx/clearcache.sh
/mnt/lustressd/hx/base_dataset_loader2/perf_test/build/dataset/standard_read_perf --conf standard.perf.ssd.conf

sleep 120

sudo /mnt/lustressd/hx/clearcache.sh
/mnt/lustressd/hx/base_dataset_loader2/perf_test/build/dataset/dataset_read_perf --conf dataset.perf.seq.hdd.conf

sleep 120

sudo /mnt/lustressd/hx/clearcache.sh
/mnt/lustressd/hx/base_dataset_loader2/perf_test/build/dataset/dataset_read_perf --conf dataset.perf.seq.ssd.conf

sleep 120

sudo /mnt/lustressd/hx/clearcache.sh
/mnt/lustressd/hx/base_dataset_loader2/perf_test/build/dataset/standard_read_perf --conf standard.perf.hdd.conf

sleep 120

sudo /mnt/lustressd/hx/clearcache.sh
/mnt/lustressd/hx/base_dataset_loader2/perf_test/build/dataset/dataset_read_perf --conf dataset.perf.ran.ssd.conf

sleep 120

sudo /mnt/lustressd/hx/clearcache.sh
/mnt/lustressd/hx/base_dataset_loader2/perf_test/build/dataset/dataset_read_perf --conf dataset.perf.ran.hdd.conf

