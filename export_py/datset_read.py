#!/usr/bin/env python

import st_dataset
context = st_dataset.create_io_context("/tmp")
index = st_dataset.Index(context, "file_set", 'r')

for idx_file in index.IndexFiles():
    for e in idx_file:
        print("key/virtual file path", e.file_path)

