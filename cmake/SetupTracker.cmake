if(${CMAKE_VERSION} VERSION_LESS 3.9.6)
	message(FATAL_ERROR "This project requires CMAKE 3.9.6")
else()
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING
		"Choose the type of build: [Debug, Release, RelWithDebInfo]"
		FORCE)
endif()

# creates compile_commands.json database for linters
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# forces C++ 17 to be one
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# will avoid extensions being added
# without it you'd get things like -std=g++11 replacing -std=c++11
set(CMAKE_CXX_EXTENSIONS OFF)

################################
# Set up third party libraries #
################################

# Find out where soci lib is based on the architecture
include(${CMAKE_MODULE_PATH}/thirdparty/SociConfig.cmake)
# Find soci lib. Look at file to see definitions.
# Sets SOCI_FOUND
include(${CMAKE_MODULE_PATH}/thirdparty/FindSoci.cmake)

# All header files for tracker application
set(tracker_include ${PROJECT_SOURCE_DIR}/include/)

# nameof is a library that converts names of variables, types, etc
# into strings
set(nameof_include ${PROJECT_SOURCE_DIR}/extern/nameof/include/)

# ranges-v3 is library to help modernise loops and transform containers
set(ranges_include ${PROJECT_SOURCE_DIR}/extern/range-v3/include/)

