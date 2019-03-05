# 3.9.6 for C++ 17
cmake_minimum_required(VERSION 3.9.6...3.13)

if(${CMAKE_VERSION} VERSION_LESS 3.9.6)
	message(FATAL_ERROR "This project requires CMAKE 3.9.6")
else()
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(
	tracker 
	VERSION 0.1
	DESCRIPTION "Track macronutrients, micronutrients, and more"
	LANGUAGES CXX
)

add_executable(main ${PROJECT_SOURCE_DIR}/src/main.cpp)

