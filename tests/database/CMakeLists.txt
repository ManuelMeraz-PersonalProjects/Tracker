list(APPEND database_tests test_utils)

foreach(test IN LISTS database_tests) 
  package_add_test(${test} ${test}.cpp)
  target_link_libraries(${test} PRIVATE tracker::database)
endforeach()

