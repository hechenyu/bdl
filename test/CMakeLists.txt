set (DEPEND_LIBS base_dataset_loader protobuf-lite boost_filesystem boost_system)

include_directories(
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/io
    ${PROJECT_SOURCE_DIR}/src/datafile
    ${PROJECT_SOURCE_DIR}/src/section
    ${PROJECT_SOURCE_DIR}/src/partition
    ${PROJECT_SOURCE_DIR}/src/indexfile
    ${PROJECT_SOURCE_DIR}/src/io_context
    )

add_subdirectory(main)
add_subdirectory(io)
add_subdirectory(datafile)
add_subdirectory(section)
add_subdirectory(partition)
add_subdirectory(indexfile)
add_subdirectory(io_context)
