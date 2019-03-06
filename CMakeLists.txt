# 3.9.6 for C++ 17
cmake_minimum_required(VERSION 3.9.6...3.13)

#TODO(Manny): Use git tag to get version
project(tracker VERSION 0.0.1)

include(cmake/setupTracker.cmake)

set(SOURCE_FILES src/implementation/compute.cpp)
add_library(computelib ${SOURCE_FILES})

target_include_directories(computelib PUBLIC include/)
target_compile_features(computelib PUBLIC cxx_std_17)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE computelib)
