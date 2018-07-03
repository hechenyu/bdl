set (CMAKE_CXX_STANDARD 11)

set (DEPEND_LIBS base_dataset_loader protobuf-lite boost_filesystem boost_system pthread)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

set(TOP_LEVEL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)

if(DEFINED ENV{BOOST_INCLUDE_DIR}) 
	include_directories($ENV{BOOST_INCLUDE_DIR}) 
endif()

if(DEFINED ENV{BOOST_LIB_DIR}) 
	link_directories($ENV{BOOST_LIB_DIR})
endif()

include_directories(
    ${TOP_LEVEL_DIR}/src/common
    ${TOP_LEVEL_DIR}/src/io
    ${TOP_LEVEL_DIR}/src/datafile
    ${TOP_LEVEL_DIR}/src/section
    ${TOP_LEVEL_DIR}/src/partition
    ${TOP_LEVEL_DIR}/src/indexfile
    ${TOP_LEVEL_DIR}/src/dataset
    )

add_subdirectory(dataset)
