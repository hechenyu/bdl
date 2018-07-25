project(BASE_DATASET_LOADER)
cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)
add_definitions("-Wall -g -fPIC -DUSE_PARTITION_POS_READER_POOL -DSTDC_FILE_READER_BUFFER_SIZE=16777216")

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

if(DEFINED ENV{BOOST_INCLUDE_DIR}) 
	include_directories($ENV{BOOST_INCLUDE_DIR}) 
endif()

if(DEFINED ENV{BOOST_LIB_DIR}) 
	link_directories($ENV{BOOST_LIB_DIR})
endif()

#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
add_subdirectory(thirdparty)
add_subdirectory(src)
add_subdirectory(export_c)
add_subdirectory(test)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install/cbase_dataset_loader)
