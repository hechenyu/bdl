set (DEPEND_LIBS base_dataset_loader protobuf-lite)

include_directories(
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/io
    ${PROJECT_SOURCE_DIR}/src/storage
    )

add_subdirectory(main)
add_subdirectory(io)
add_subdirectory(storage)
