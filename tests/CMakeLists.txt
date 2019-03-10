#TODO(Manny): Google test
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/tests)
add_executable(test-food test-food.cpp)
add_test(test-food test-food)
