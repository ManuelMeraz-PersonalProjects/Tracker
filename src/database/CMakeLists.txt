set(DATABASE_SOURCE_FILES Database.cpp)

add_library(database STATIC ${DATABASE_SOURCE_FILES})

target_include_directories(database
                           PUBLIC ${tracker_include}
                           PUBLIC ${nameof_include}
                           PUBLIC ${ranges_include})

target_link_libraries(database PUBLIC Soci)
cotire(database)
