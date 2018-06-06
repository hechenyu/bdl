set(PARTITION_WRITE_SRC partition_write.cpp)
add_executable(partition_write ${PARTITION_WRITE_SRC})
target_link_libraries(partition_write ${DEPEND_LIBS})

