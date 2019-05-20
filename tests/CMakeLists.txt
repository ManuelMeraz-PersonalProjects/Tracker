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

# macro to easily add tests
macro(package_add_test TESTNAME)
  add_executable(${TESTNAME} ${ARGN})
  add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
  target_link_libraries(${TESTNAME} PRIVATE CONAN_PKG::gtest)
endmacro()

add_subdirectory(database)
