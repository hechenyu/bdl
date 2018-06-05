set(PRINT_FUNC_SRC ../datafile/dump_data.cpp ../datafile/print_metadata.cpp ../datafile/print_datafile.cpp print_section.cpp)

include_directories(../datafile)

set(TEST_SECTION_WRITE_SRC test_section_write.cpp create_datafile.cpp ${PRINT_FUNC_SRC})
add_executable(test_section_write ${TEST_SECTION_WRITE_SRC})
target_link_libraries(test_section_write ${DEPEND_LIBS})

set(TEST_SECTION_READ_SRC test_section_read.cpp ${PRINT_FUNC_SRC})
add_executable(test_section_read ${TEST_SECTION_READ_SRC})
target_link_libraries(test_section_read ${DEPEND_LIBS})
