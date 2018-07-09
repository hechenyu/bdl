#!/usr/bin/env python

import st_dataset
context = st_dataset.create_io_context("/tmp")
index = st_dataset.Index(context, "file_set", 'r')

for e in index:
    print("key/virtual file path", e.file_path)
    print(".part file path", e.partition_path)
    print("offset", e.offset)
    print("file size", e.file_size)
    s = e.to_string()
    print("serialized data:", s)

    item = st_dataset.IndexItem(s)
    f = index.open(item)
    all_content = f.readAll()
    print(bytes(all_content))
#    print(bytearray(all_content))

