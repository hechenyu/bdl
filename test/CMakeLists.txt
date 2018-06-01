set (DEPEND_LIBS base_dataset_loader protobuf-lite)

include_directories(
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/io
    )

add_subdirectory(io)
