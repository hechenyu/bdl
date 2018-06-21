#!/usr/bin/env python

import st_dataset
context = st_dataset.create_io_context("/tmp")
index = st_dataset.Index(context, "file_set", 'r')
new_index = st_dataset.Index(context, "file_set_new", 'a')

for e in index:
    print("key/virtual file path", e.file_path)
    print(".part file path", e.partition_path)
    print("offset", e.offset)
    print("file size", e.file_size)

    f = index.open(e)
    all_content = bytes(f.readAll())
    new_f = new_index.Append(e.file_path, "xxx")
    new_f.writeAll(all_content)

