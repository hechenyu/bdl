#!/usr/bin/env python

import st_dataset
context = st_dataset.create_io_context("/tmp")
index = st_dataset.Index(context, "file_set_new", 'a')
f = index.Append("test.txt", "text")
f.writeAll("content of test.txt: xxyyzz")

