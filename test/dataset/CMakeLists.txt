set(CONFIG_PARSER_SRC ../partition/config_parser.cpp ../partition/test_partition_util.cpp)
include_directories(../partition)

set(DATASET_WRITE_SRC dataset_write.cpp)
add_executable(dataset_write ${DATASET_WRITE_SRC} ${CONFIG_PARSER_SRC})
target_link_libraries(dataset_write ${DEPEND_LIBS} boost_program_options)

set(DATASET_READ_SRC dataset_read.cpp)
add_executable(dataset_read ${DATASET_READ_SRC})
target_link_libraries(dataset_read ${DEPEND_LIBS})

set(DATASET_INDEXFILE_READ_SRC dataset_indexfile_read.cpp)
add_executable(dataset_indexfile_read ${DATASET_INDEXFILE_READ_SRC})
target_link_libraries(dataset_indexfile_read ${DEPEND_LIBS})

