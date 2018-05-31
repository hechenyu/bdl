include_directories(${PROJECT_SOURCE_DIR}/src/common)
set(APP_SRC main.cpp)
add_executable(test ${APP_SRC})
target_link_libraries(test base_dataset_loader)
