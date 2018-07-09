#include "indexfile_item.h"
#include "dataset_index_item.h"
#include <string>
#include <iostream>
#include <gtest/gtest.h>

using namespace std;

TEST(DatasetIndexItem, serialize)
{
    DatasetIndexItem index_item;
    index_item.file_item_ = make_shared<IndexfileItem>("/tmp/file_set", 435, 102400);
    index_item.partition_path_ = make_shared<string>("0000.part");

    auto serialized_data = index_item.to_string();
    cout << "serialized_data: " << serialized_data << endl;

    DatasetIndexItem index_item2(serialized_data); 

    EXPECT_EQ(index_item.file_path(), index_item2.file_path());
    EXPECT_EQ(index_item.offset(), index_item2.offset());
    EXPECT_EQ(index_item.file_size(), index_item2.file_size());
    EXPECT_EQ(index_item.partition_path(), index_item2.partition_path());
}

