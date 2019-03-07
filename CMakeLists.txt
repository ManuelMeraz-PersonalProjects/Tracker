# 3.9.6 for C++ 17
cmake_minimum_required(VERSION 3.9.6...3.13)

#TODO(Manny): Use git tag to get version
project(tracker VERSION 0.0.1)

# Sets compiler standards(e.g. C++ 17) and checks cmake version
include(cmake/setupTracker.cmake)

# Creates libraries and creates main executable
add_subdirectory(src)
