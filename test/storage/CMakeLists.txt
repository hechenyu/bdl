set(TEST_METADATA_SRC test_metadata.cpp dump_data.cpp print_metadata.cpp)
add_executable(test_metadata ${TEST_METADATA_SRC})
target_link_libraries(test_metadata ${DEPEND_LIBS})

set(TEST_DATAFILE_SRC test_datafile.cpp dump_data.cpp print_metadata.cpp print_datafile.cpp)
add_executable(test_datafile ${TEST_DATAFILE_SRC})
target_link_libraries(test_datafile ${DEPEND_LIBS})
