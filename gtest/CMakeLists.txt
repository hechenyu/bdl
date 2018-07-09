#set(CMAKE_BUILD_TYPE debug)

set(LIBBASE_DATASET_LOADER_UT_SRC 
    main/main.cpp
    datafile/datafile_test.cpp
    dataset/dataset_test.cpp
    )

include_directories(
    ../src/common
    ../src/io
    ../src/datafile
    ../src/section
    ../src/partition
    ../src/indexfile
    ../src/dataset
    )

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
MESSAGE(STATUS "lib" ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

add_executable(ut_main ${LIBBASE_DATASET_LOADER_UT_SRC})
target_link_libraries(ut_main base_dataset_loader protobuf-lite boost_filesystem boost_system gtest)

