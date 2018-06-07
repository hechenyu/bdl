set(MYCP_SRC mycp.cpp)
add_executable(mycp ${MYCP_SRC})
target_link_libraries(mycp ${DEPEND_LIBS})

set(MYREAD_SRC myread.cpp)
add_executable(myread ${MYREAD_SRC})
target_link_libraries(myread ${DEPEND_LIBS})

set(HOLE_SRC hole.cpp)
add_executable(hole ${HOLE_SRC})
target_link_libraries(hole ${DEPEND_LIBS})

set(MYWRITE_SRC mywrite.cpp)
add_executable(mywrite ${MYWRITE_SRC})
target_link_libraries(mywrite ${DEPEND_LIBS})

set(MYAPPEND_SRC myappend.cpp)
add_executable(myappend ${MYAPPEND_SRC})
target_link_libraries(myappend ${DEPEND_LIBS})

set(SEEK_SRC seek.cpp)
add_executable(seek ${SEEK_SRC})
target_link_libraries(seek ${DEPEND_LIBS})

set(GETLINE_SRC getline.cpp)
add_executable(getline ${GETLINE_SRC})
target_link_libraries(getline ${DEPEND_LIBS})
