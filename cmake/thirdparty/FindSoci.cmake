# ~~~
# CMake module to search for SOCI library
#
# WARNING: This module is experimental work in progress.
#
# This module defines:
#  SOCI_INCLUDE_DIRS        = include dirs to be used when using the soci library
#  SOCI_LIBRARY             = full path to the soci library
#  SOCI_VERSION             = the soci version found (not yet. soci does not provide that info.)
#  SOCI_FOUND               = true if soci was found
#
# This module respects:
#  LIB_SUFFIX         = (64|32|"") Specifies the suffix for the lib directory
#
# For each component you specify in find_package(), the following variables are set.
#
#  SOCI_${COMPONENT}_PLUGIN = full path to the soci plugin
#  SOCI_${COMPONENT}_FOUND
#
# Copyright (c) 2011 Michael Jansen <info@michael-jansen.biz>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
# ~~~

# Global Configuration Section
set(_SOCI_ALL_PLUGINS mysql odbc postgresql sqlite3)
set(_SOCI_REQUIRED_VARS SOCI_INCLUDE_DIR SOCI_LIBRARY)

# FIRST STEP: Find the soci headers.
find_path(SOCI_INCLUDE_DIR
          NAMES soci.h PATH "/usr/local/"
          PATH_SUFFIXES "" "soci"
          DOC "Soci (http://soci.sourceforge.net) include directory")
mark_as_advanced(SOCI_INCLUDE_DIR)

set(SOCI_INCLUDE_DIRS ${SOCI_INCLUDE_DIR})

# SECOND STEP: Find the soci core library. Respect LIB_SUFFIX
find_library(SOCI_LIBRARY
             NAMES soci_core
             HINTS ${SOCI_INCLUDE_DIR}/..
             PATH_SUFFIXES lib${LIB_SUFFIX})
mark_as_advanced(SOCI_LIBRARY)

get_filename_component(SOCI_LIBRARY_DIR ${SOCI_LIBRARY} PATH)
mark_as_advanced(SOCI_LIBRARY_DIR)

# THIRD STEP: Find all installed plugins if the library was found
if(SOCI_INCLUDE_DIR AND SOCI_LIBRARY)

  message(STATUS "Soci found: Looking for plugins")
  foreach(plugin IN LISTS _SOCI_ALL_PLUGINS)

    find_library(SOCI_${plugin}_PLUGIN
                 NAMES soci_${plugin}
                 HINTS ${SOCI_INCLUDE_DIR}/..
                 PATH_SUFFIXES lib${LIB_SUFFIX})
    mark_as_advanced(SOCI_${plugin}_PLUGIN)

    if(SOCI_${plugin}_PLUGIN)
      message(STATUS "    * Plugin ${plugin} found ${SOCI_${plugin}_PLUGIN}.")
      set(SOCI_${plugin}_FOUND True)
      set(SOCI_INCLUDE_DIRS ${SOCI_INCLUDE_DIRS} ${SOCI_INCLUDE_DIR}/${plugin})
    else()
      message(STATUS "    * Plugin ${plugin} not found.")
      set(SOCI_${plugin}_FOUND False)
    endif()

  endforeach()

  # FOURTH CHECK: Check if the required components were all found
  foreach(component ${Soci_FIND_COMPONENTS})
    if(NOT SOCI_${component}_FOUND)
      message(SEND_ERROR "Required component ${component} not found.")
    endif()
  endforeach()
else()
  message(STATUS "SOCI_INCLUDE_DIR: ${SOCI_INCLUDE_DIR}")
  message(STATUS "SOCI_LIBRARY_DIR: ${SOCI_LIBRARY_DIR}")
  message(FATAL_ERROR "Soci library not found, it is required for build.")
endif()

# ADHERE TO STANDARDS
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Soci DEFAULT_MSG ${_SOCI_REQUIRED_VARS})

if(SOCI_FOUND)
  # Make library visible in source directory by setting global
  add_library(Soci SHARED IMPORTED GLOBAL)
  set_target_properties(Soci PROPERTIES IMPORTED_LOCATION ${SOCI_LIBRARY})
  target_include_directories(Soci INTERFACE ${SOCI_INCLUDE_DIRS})
else()
  message(FATAL_ERROR "Soci is a required library")
endif()
