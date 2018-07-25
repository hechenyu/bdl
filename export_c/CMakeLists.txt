#set(CMAKE_BUILD_TYPE debug)

set(CLIBBASE_DATASET_LOADER_SRC 
	cbase_dataset_loader.cpp
    )

include_directories(
	${PROJECT_SOURCE_DIR}/src/io
	${PROJECT_SOURCE_DIR}/src/indexfile
    ${PROJECT_SOURCE_DIR}/src/dataset
    )

add_library(cbase_dataset_loader SHARED ${CLIBBASE_DATASET_LOADER_SRC})
target_link_libraries(cbase_dataset_loader base_dataset_loader protobuf-lite boost_filesystem boost_system)

install(TARGETS cbase_dataset_loader LIBRARY DESTINATION lib)
install(FILES cbase_dataset_loader.h DESTINATION include)

