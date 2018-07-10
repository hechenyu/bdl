#!/usr/bin/env python

import st_dataset
context = st_dataset.create_io_context("/tmp")
index = st_dataset.Index(context, "file_set", 'r')
direct_reader = st_dataset.DirectReader(context);

for e in index:
    print("key/virtual file path", e.file_path)
    print(".part file path", e.partition_path)
    print("offset", e.offset)
    print("file size", e.file_size)
    s = e.to_string()
    print("serialized data:", s)

    f = direct_reader.open(s)
    all_content = f.readAll()
    print(bytes(all_content))
#    print(bytearray(all_content))

