set(DATABASE_SOURCE_FILES
	Database.cpp
)

add_library(database
	STATIC
	${DATABASE_SOURCE_FILES}
)

target_include_directories(database 
	PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(database PRIVATE Soci)
