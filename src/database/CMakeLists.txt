add_library(database SHARED Database.cpp)
add_library(tracker::database ALIAS database)

target_include_directories(database
                           PUBLIC ${PROJECT_SOURCE_DIR}/include
                                  ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(database
                      CONAN_PKG::soci
                      CONAN_PKG::nameof
                      CONAN_PKG::range-v3)

install(TARGETS database DESTINATION ${CMAKE_BINARY_DIR}/lib/tracker)
cotire(database)
