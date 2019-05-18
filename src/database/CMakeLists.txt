add_library(database STATIC Database.cpp)

target_include_directories(database
                           PUBLIC ${CONAN_INCLUDE_DIRS}
                           PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(database ${CONAN_LIBS})
cotire(database)
