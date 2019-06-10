if(${CMAKE_VERSION} VERSION_LESS 3.9.6)
  message(FATAL_ERROR "This project requires CMAKE 3.9.6")
else()
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release"
      CACHE STRING "Choose the type of build: [Debug, Release, RelWithDebInfo]"
      FORCE)
endif()

# creates compile_commands.json database for linters
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# forces C++ 17 to be one
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Use glibc 2.23 for to be compatible with Ubuntu 16.04 
# more options: https://github.com/bincrafters/conan-glibc_version_header
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CONAN_C_FLAGS_GLIBC_VERSION_HEADER}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CONAN_CXX_FLAGS_GLIBC_VERSION_HEADER_LIST}")

# will avoid extensions being added without it you'd get things like -std=g++11
# replacing -std=c++11
set(CMAKE_CXX_EXTENSIONS OFF)

# Tell CMake to run moc when necessary:
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# As moc files are generated in the binary dir, tell CMake to always look for
# includes there:
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# All static libs will be placed here
link_directories(${PROJECT_BINARY_DIR}/lib)

# Reduce compile time with cotire
include(${CMAKE_MODULE_PATH}/thirdparty/cotire.cmake)

find_package(Qt5 REQUIRED COMPONENTS Core Quick Widgets)
