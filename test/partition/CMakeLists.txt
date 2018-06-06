set(PARTITION_WRITE_SRC partition_write.cpp)
add_executable(partition_write ${PARTITION_WRITE_SRC})
target_link_libraries(partition_write ${DEPEND_LIBS})

set(PARTITION_READ_SRC partition_read.cpp config_parser.cpp)
add_executable(partition_read ${PARTITION_READ_SRC})
target_link_libraries(partition_read ${DEPEND_LIBS} boost_program_options boost_filesystem boost_system)

