set(UTIL_SRC ../util/config_parser.cpp ../util/utc_to_string.cpp ../util/get_file_list.cpp output_functions.cpp)
include_directories(../util)

set(DATASET_READ_SRC dataset_read_perf.cpp)
add_executable(dataset_read_perf ${DATASET_READ_SRC} ${UTIL_SRC})
target_link_libraries(dataset_read_perf ${DEPEND_LIBS} boost_program_options)

set(DATASET_READ_RT_SRC dataset_read_perf_rt.cpp)
add_executable(dataset_read_perf_rt ${DATASET_READ_RT_SRC} ${UTIL_SRC})
target_link_libraries(dataset_read_perf_rt ${DEPEND_LIBS} boost_program_options)

set(STANDARD_READ_SRC standard_read_perf.cpp)
add_executable(standard_read_perf ${STANDARD_READ_SRC} ${UTIL_SRC})
target_link_libraries(standard_read_perf ${DEPEND_LIBS} boost_program_options)

set(STANDARD_READ2_SRC standard_read_perf2.cpp)
add_executable(standard_read_perf2 ${STANDARD_READ2_SRC} ${UTIL_SRC})
target_link_libraries(standard_read_perf2 ${DEPEND_LIBS} boost_program_options)

