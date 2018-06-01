include_directories(
    ${PROJECT_SOURCE_DIR}/src/common
    ${PROJECT_SOURCE_DIR}/src/io
    )

set(MYCP_SRC mycp.cpp)
add_executable(mycp ${MYCP_SRC})
target_link_libraries(mycp base_dataset_loader protobuf)

set(MYREAD_SRC myread.cpp)
add_executable(myread ${MYREAD_SRC})
target_link_libraries(myread base_dataset_loader protobuf)

set(HOLE_SRC hole.cpp)
add_executable(hole ${HOLE_SRC})
target_link_libraries(hole base_dataset_loader protobuf)

set(MYWRITE_SRC mywrite.cpp)
add_executable(mywrite ${MYWRITE_SRC})
target_link_libraries(mywrite base_dataset_loader protobuf)

set(MYAPPEND_SRC myappend.cpp)
add_executable(myappend ${MYAPPEND_SRC})
target_link_libraries(myappend base_dataset_loader protobuf)

set(SEEK_SRC seek.cpp)
add_executable(seek ${SEEK_SRC})
target_link_libraries(seek base_dataset_loader protobuf)
