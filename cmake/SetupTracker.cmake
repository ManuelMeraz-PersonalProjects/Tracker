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
include(${CMAKE_MODULE_PATH}/thirdparty/FindSoci.cmake)

if(SOCI_FOUND) 
	# Make library visible in source directory by setting global
	add_library(Soci SHARED IMPORTED GLOBAL)
	set_target_properties(Soci 
		PROPERTIES 
		IMPORTED_LOCATION ${SOCI_LIBRARY})
	target_include_directories(Soci INTERFACE ${SOCI_INCLUDE_DIRS})
else()
	message(FATAL_ERROR "Soci is a required library")
endif()
