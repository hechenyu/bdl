set(TEST_INDEX_ITEM_SRC test_index_item.cpp)
add_executable(test_index_item ${TEST_INDEX_ITEM_SRC})
target_link_libraries(test_index_item ${DEPEND_LIBS})

set(TEST_INDEXFILE_WRITE_SRC test_indexfile_write.cpp)
add_executable(test_indexfile_write ${TEST_INDEXFILE_WRITE_SRC})
target_link_libraries(test_indexfile_write ${DEPEND_LIBS})

set(TEST_INDEXFILE_READ_SRC test_indexfile_read.cpp)
add_executable(test_indexfile_read ${TEST_INDEXFILE_READ_SRC})
target_link_libraries(test_indexfile_read ${DEPEND_LIBS})

