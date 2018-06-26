set(CONFIG_PARSER_SRC ../util/config_parser.cpp ../util/utc_to_string.cpp)
include_directories(../util)

set(DATASET_READ_SRC dataset_read_perf.cpp)
add_executable(dataset_read_perf ${DATASET_READ_SRC} ${CONFIG_PARSER_SRC})
target_link_libraries(dataset_read_perf ${DEPEND_LIBS} boost_program_options)

