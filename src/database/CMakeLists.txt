add_library(database STATIC Database.cpp)
add_library(tracker::database ALIAS database)

target_include_directories(database
                           PUBLIC ${CONAN_INCLUDE_DIRS}
                           PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(database PUBLIC ${CONAN_LIBS})
cotire(database)
