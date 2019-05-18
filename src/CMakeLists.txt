add_subdirectory(food)
add_subdirectory(database)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE tracker::food)
target_link_libraries(main PRIVATE tracker::database)
cotire(main)

set_target_properties(main
                      PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                 ${PROJECT_BINARY_DIR}/bin)
