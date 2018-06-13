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
    io_context/io_context.cpp
    io_context/dataset_index.cpp
    io_context/dataset_util.cpp
    io_context/dataset_writer.cpp
    io_context/dataset_config.cpp
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
    ${CMAKE_CURRENT_SOURCE_DIR}/io_context
    )

add_library(base_dataset_loader SHARED ${LIBBASE_DATASET_LOADER_SRC})
#set_target_properties(base_dataset_loader PROPERTIES VERSION 1.2 SOVERSION 1)

add_library(base_dataset_loader_static STATIC ${LIBBASE_DATASET_LOADER_SRC})
set_target_properties(base_dataset_loader_static PROPERTIES OUTPUT_NAME "base_dataset_loader")

get_target_property(OUTPUT_VALUE base_dataset_loader_static OUTPUT_NAME)
message(STATUS "This is the base_dataset_loader_static OUTPUT_NAME: " ${OUTPUT_VALUE})

install(TARGETS base_dataset_loader base_dataset_loader_static
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
#install(FILES base_dataset_loader.h DESTINATION include/base_dataset_loader)
