list(APPEND database_tests test_utils)

add_library(dummy_storable STATIC DummyStorable.cpp)
target_link_libraries(dummy_storable PUBLIC tracker::database)

foreach(test IN LISTS database_tests) 
  package_add_test(${test} ${test}.cpp)
  target_link_libraries(${test} PRIVATE dummy_storable)
endforeach()

