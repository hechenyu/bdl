#include "datafile_metadata.h"
#include <string>
#include <chrono>
#include <iostream>
#include <gtest/gtest.h>

using namespace std;
using namespace std::chrono;

TEST(DatafileTest, Metadata)
{
    string blob = "test";
    DatafileMetadata meta("test.txt", "plain/txt", (const uint8_t *) blob.data(), blob.size(),
            {{"key1", "value1"}, {"key2", "value2"}});

    EXPECT_EQ(blob.size(), meta.file_size());

    string serialize_data = meta.serialize();

    EXPECT_FALSE(serialize_data.empty()); 

    DatafileMetadata meta2(serialize_data);

    EXPECT_EQ(meta.file_size(), meta2.file_size());
    EXPECT_EQ(meta.etag(), meta2.etag());
    EXPECT_EQ(meta.content_type(), meta2.content_type());
//    EXPECT_EQ(meta.creation_time(), meta2.creation_time());   // 精度nano以下会损失
    EXPECT_EQ(meta.attrs(), meta2.attrs());
    EXPECT_EQ(meta.file_name(), meta2.file_name());
}

