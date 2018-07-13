set(BDL_SRC 
    common/error.cpp)

add_library(bdl SHARED ${BDL_SRC})
#set_target_properties(bdl PROPERTIES VERSION 1.2 SOVERSION 1)

add_library(bdl_static STATIC ${BDL_SRC})
set_target_properties(bdl_static PROPERTIES OUTPUT_NAME "bdl")

get_target_property(OUTPUT_VALUE bdl_static OUTPUT_NAME)
message(STATUS "This is the bdl_static OUTPUT_NAME: " ${OUTPUT_VALUE})

install(TARGETS bdl bdl_static
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
