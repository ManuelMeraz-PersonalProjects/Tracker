if(${CMAKE_VERSION} VERSION_LESS 3.9.6)
	message(FATAL_ERROR "This project requires CMAKE 3.9.6")
else()
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# creates compile_commands.json database for linters
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# forces C++ 17 to be one
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# will avoid extensions being added
# without it you'd get things like -std=g++11 replacing -std=c++1
set(CMAKE_CXX_EXTENSIONS OFF)
