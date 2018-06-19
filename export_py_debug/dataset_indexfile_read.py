#!/usr/bin/env python

import sys
import st_dataset

filename = "test.index"
partition_path = "test.part"

if len(sys.argv) == 2:
    filename = sys.argv[1]

print("filename:", filename)

file_system = st_dataset.create_posix_file_system()
reader = st_dataset.DatasetIndexfileReader(file_system, filename, partition_path)

for item in reader:
    print(item.file_path, item.partition_path, item.offset, item.file_size)

