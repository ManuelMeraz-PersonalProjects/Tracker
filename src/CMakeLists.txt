# Creates food library
add_subdirectory(food)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE food)
