#set(CMAKE_BUILD_TYPE debug)

set(LIBBASE_DATASET_LOADER_SRC 
    common/error.cpp
    common/wrapposix.cpp
    common/calculate_crc32.cpp
    io/i_file_writer.cpp
    io/posix_file_writer.cpp
    io/i_file_reader.cpp
    io/posix_file_reader.cpp
    io/i_line_reader.cpp
    io/file_line_reader.cpp
    io/i_line_writer.cpp
    io/file_line_writer.cpp
    io/i_file_system.cpp
    io/posix_file_system.cpp
    io/io_context.cpp
    proto/metadata.pb.cc
    datafile/datafile_metadata.cpp
    datafile/datafile_serializer.cpp
    datafile/datafile_view.cpp
    section/section_memory_cache.cpp
    partition/partition_writer.cpp
    partition/partition_reader.cpp
    partition/partition_pos_reader.cpp
    partition/partition_full_error.cpp
    indexfile/indexfile_item.cpp
    indexfile/indexfile_reader.cpp
    indexfile/indexfile_writer.cpp
    dataset/dataset_index.cpp
    dataset/dataset_util.cpp
    dataset/dataset_writer.cpp
    dataset/dataset_config.cpp
    dataset/dataset_indexfile_reader.cpp
    dataset/dataset_indexfile_writer.cpp
    dataset/i_partition_pos_reader_factory.cpp
    dataset/partition_pos_reader_factory.cpp
    dataset/partition_pos_reader_pool.cpp
    )

include_directories(
    ${PROJECT_SOURCE_DIR}/thirdparty/protobuf/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}/io
    ${CMAKE_CURRENT_SOURCE_DIR}/proto
    ${CMAKE_CURRENT_SOURCE_DIR}/datafile
    ${CMAKE_CURRENT_SOURCE_DIR}/section
    ${CMAKE_CURRENT_SOURCE_DIR}/partition
    ${CMAKE_CURRENT_SOURCE_DIR}/indexfile
    ${CMAKE_CURRENT_SOURCE_DIR}/dataset
    )

add_library(base_dataset_loader STATIC ${LIBBASE_DATASET_LOADER_SRC})

