set (DEPEND_LIBS base_dataset_loader protobuf-lite)

include_directories(
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/io
    ${PROJECT_SOURCE_DIR}/src/datafile
    ${PROJECT_SOURCE_DIR}/src/section
    ${PROJECT_SOURCE_DIR}/src/partition
    )

add_subdirectory(io)
add_subdirectory(datafile)
add_subdirectory(section)
add_subdirectory(partition)
