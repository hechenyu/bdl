#!/usr/bin/env python

import st_dataset
context = st_dataset.create_io_context("/tmp")
index = st_dataset.Index(context, "file_set", 'r')

for idx_file in index.IndexFiles:
    for e in idx_file:
        print("key/virtual file path", e.file_path)
        print(".part file path", e.partition_path)
        print("offset", e.offset)
        print("file size", e.file_size)

        f = index.open(e)
        all_content = f.readAll()
        print(bytes(all_content))
#        print(bytearray(all_content))
