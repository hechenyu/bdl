set(DATASET_WRITE_SRC dataset_write.cpp)
add_executable(dataset_write ${DATASET_WRITE_SRC})
target_link_libraries(dataset_write ${DEPEND_LIBS})

set(DATASET_READ_SRC dataset_read.cpp)
add_executable(dataset_read ${DATASET_READ_SRC})
target_link_libraries(dataset_read ${DEPEND_LIBS})

