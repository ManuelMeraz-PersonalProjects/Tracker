# 3.9.6 for C++ 17
cmake_minimum_required(VERSION 3.9.6...3.13)

project(
	tracker 
	VERSION 0.1
	DESCRIPTION "Track macronutrients, micronutrients, and more"
	LANGUAGES CXX
)

include(cmake/setupTracker.cmake)

add_library(
	hellolib 
	STATIC 
	src/implementation/lib.cpp 
)

target_include_directories(hellolib PUBLIC include/tracker/)
target_compile_features(hellolib PUBLIC cxx_std_17)

add_executable(main src/main.cpp)
target_link_libraries(main PUBLIC hellolib)
