#!/usr/bin/env python

import st_dataset
context = st_dataset.create_io_context("/tmp")
index = st_dataset.Index(context, "file_set", 'r')

for e in index:
    print("key/virtual file path", e.file_path)
    print(".part file path", e.partition_path)
    print("offset", e.offset)
    print("file size", e.file_size)

    f = index.open(e)
    attrs = st_dataset.getAttrs(f)
    print(attrs)

