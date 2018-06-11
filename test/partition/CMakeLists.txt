set(PARTITION_WRITE_SRC partition_write.cpp test_partition_util.cpp)
add_executable(partition_write ${PARTITION_WRITE_SRC})
target_link_libraries(partition_write ${DEPEND_LIBS})

set(PARTITION_READ_SRC partition_read.cpp config_parser.cpp)
add_executable(partition_read ${PARTITION_READ_SRC})
target_link_libraries(partition_read ${DEPEND_LIBS} boost_program_options boost_filesystem boost_system)

set(PARTITION_APPEND_SRC partition_append.cpp test_partition_util.cpp)
add_executable(partition_append ${PARTITION_APPEND_SRC})
target_link_libraries(partition_append ${DEPEND_LIBS})

set(PARTITION_POS_READ_SRC partition_pos_read.cpp config_parser.cpp)
add_executable(partition_pos_read ${PARTITION_POS_READ_SRC})
target_link_libraries(partition_pos_read ${DEPEND_LIBS} boost_program_options boost_filesystem boost_system)

