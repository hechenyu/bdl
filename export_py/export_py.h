#ifndef __export_py_h
#define __export_py_h

const char *demo_dataset_read_docs = R"(
==================================================
demo of read a dataset:
==================================================
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
    all_content = f.readAll()
    print(bytes(all_content))
==================================================
)";

const char *demo_dataset_index_iterator_docs = R"(
==================================================
demo of st_dataset.IndexItem:
==================================================
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
    all_content = f.readAll()
    print(bytes(all_content))
==================================================
)";

const char *demo_dataset_index_indexfiles_docs = R"(
==================================================
demo of st_dataset.Index.IndexFiles
==================================================
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
==================================================
)";

const char *demo_dataset_index_appenditem_docs = R"(
==================================================
demo of st_dataset.Index.AppendItem
==================================================
#!/usr/bin/env python

import st_dataset
context = st_dataset.create_io_context("/tmp")
index = st_dataset.Index(context, "file_set", 'r')
new_index = st_dataset.Index(context, "file_set.new", 'a')

for e in index:
    print("key/virtual file path", e.file_path)
    print(".part file path", e.partition_path)
    print("offset", e.offset)
    print("file size", e.file_size)

    if e.file_size > 1024:
        new_index.AppendItem(e)
==================================================
)";

const char *demo_dataset_index_append_docs = R"(
==================================================
demo of st_dataset.Index.Append
==================================================
#!/usr/bin/env python

import st_dataset
context = st_dataset.create_io_context("/tmp")
index = st_dataset.Index(context, "file_set_new", 'a')
f = index.Append("test.txt", "text")
f.writeAll("content of test.txt: xxyyzz")
==================================================
)";

const char *demo_dataset_direct_reader1_docs = R"(
==================================================
demo of st_dataset.DirectReader.open
==================================================
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
==================================================
)";

const char *demo_dataset_direct_reader2_docs = R"(
==================================================
demo of st_dataset.DirectReader.open
==================================================
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

    item = st_dataset.IndexItem(s)

    f = direct_reader.open(item)
    all_content = f.readAll()
    print(bytes(all_content))
==================================================
)";

const char *demo_dataset_get_attrs_docs = R"(
get attributes of datafile:
==================================================
demo of st_dataset.getAttrs
==================================================
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
==================================================
)";

const char *dataset_index_docs = R"(
manager of dataset: 
    can traverse indexfile of dataset, 
    can read datafile by indexitem, 
    can append datafile to dataset,
    can append indexitem to dataset.
)";

#endif

