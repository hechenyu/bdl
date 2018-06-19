#!/usr/bin/env python

import sys
import st_dataset

filename = "test.index"

if len(sys.argv) == 2:
    filename = sys.argv[1]

print("filename:", filename)

file_system = st_dataset.PosixFileSystem()
reader = st_dataset.IndexfileReader(filename, file_system.create_line_reader())

while reader.has_next():
    item = reader.next()
    print(item.key, item.offset, item.file_size)

