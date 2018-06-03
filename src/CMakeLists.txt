set(LIBBASE_DATASET_LOADER_SRC 
    common/error.cpp
    common/wrapposix.cpp
    io/i_file_writer.cpp
    io/posix_file_writer.cpp
    io/i_file_reader.cpp
    io/posix_file_reader.cpp
    proto/metadata.pb.cc
    storage/datafile_metadata.cpp
    storage/datafile_serializer.cpp
    storage/datafile_view.cpp
    )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}/io
    ${CMAKE_CURRENT_SOURCE_DIR}/proto
    ${CMAKE_CURRENT_SOURCE_DIR}/storage
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
