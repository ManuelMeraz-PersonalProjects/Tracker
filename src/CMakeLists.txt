# Creates food library
#add_subdirectory(food)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE Soci)
set_target_properties(main 
	PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)


