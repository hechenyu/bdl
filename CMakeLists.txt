project(BASE_DATASET_LOADER)
cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)
add_definitions("-Wall -g -fPIC -DUSE_PARTITION_POS_READER_POOL -DSTDC_FILE_READER_BUFFER_SIZE=16777216")

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
add_subdirectory(src)
add_subdirectory(test)
