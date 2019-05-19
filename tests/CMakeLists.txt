find_package(GTest REQUIRED)
if(NOT GTEST_FOUND)
  message(FATAL_ERROR "Could not find GTest")
endif()

# Helps keep cache cleaner
mark_as_advanced(BUILD_GMOCK
                 BUILD_GTEST
                 BUILD_SHARED_LIBS
                 gmock_build_tests
                 gtest_build_samples
                 gtest_build_tests
                 gtest_disable_pthreads
                 gtest_force_shared_crt
                 gtest_hide_internal_symbols)

# Put test executables into build_dir/tests/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/tests)

# macro to easily add tests
macro(package_add_test TESTNAME)
  add_executable(${TESTNAME} ${ARGN})
  target_link_libraries(${TESTNAME} PRIVATE CONAN_PKG::gtest)
  add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
  set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
  cotire(${TESTNAME})
endmacro()

add_subdirectory(database)
