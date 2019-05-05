set(DATABASE_SOURCE_FILES Database.cpp)

add_library(database STATIC ${DATABASE_SOURCE_FILES})

target_include_directories(database
                           PUBLIC ${CONAN_INCLUDE_DIRS}
                           PUBLIC ${tracker_include})

target_link_libraries(database ${CONAN_LIBS})
cotire(database)
