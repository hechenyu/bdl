set(TEST_METADATA_SRC test_metadata.cpp dump_data.cpp print_metadata.cpp)
add_executable(test_metadata ${TEST_METADATA_SRC})
target_link_libraries(test_metadata ${DEPEND_LIBS})

set(TEST_DATAFILE_SRC test_datafile.cpp dump_data.cpp print_metadata.cpp print_datafile.cpp)
add_executable(test_datafile ${TEST_DATAFILE_SRC})
target_link_libraries(test_datafile ${DEPEND_LIBS})

set(WRITE_DATAFILE_SRC write_datafile.cpp print_metadata.cpp)
add_executable(write_datafile ${WRITE_DATAFILE_SRC})
target_link_libraries(write_datafile ${DEPEND_LIBS})

set(READ_DATAFILE_SRC read_datafile.cpp dump_data.cpp print_metadata.cpp print_datafile.cpp)
add_executable(read_datafile ${READ_DATAFILE_SRC})
target_link_libraries(read_datafile ${DEPEND_LIBS})

set(TEST_SECTION_WRITE_SRC test_section_write.cpp create_datafile.cpp dump_data.cpp print_metadata.cpp print_datafile.cpp print_section.cpp)
add_executable(test_section_write ${TEST_SECTION_WRITE_SRC})
target_link_libraries(test_section_write ${DEPEND_LIBS})

set(TEST_SECTION_READ_SRC test_section_read.cpp dump_data.cpp print_metadata.cpp print_datafile.cpp print_section.cpp)
add_executable(test_section_read ${TEST_SECTION_READ_SRC})
target_link_libraries(test_section_read ${DEPEND_LIBS})
