set(TEST_METADATA_SRC test_metadata.cpp dump_data.cpp print_metadata.cpp)
add_executable(test_metadata ${TEST_METADATA_SRC})
target_link_libraries(test_metadata ${DEPEND_LIBS})
