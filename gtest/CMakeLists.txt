#set(CMAKE_BUILD_TYPE debug)

set(LIBBASE_DATASET_LOADER_UT_SRC 
    main/main.cpp
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

add_executable(ut_main ${LIBBASE_DATASET_LOADER_UT_SRC})
target_link_libraries(ut_main gtest)
