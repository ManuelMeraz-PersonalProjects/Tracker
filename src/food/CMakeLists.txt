set(FOOD_SOURCE_FILES
	Food.cpp
)

add_library(food
	STATIC
	${FOOD_SOURCE_FILES}
)

target_include_directories(food 
	PUBLIC ${PROJECT_SOURCE_DIR}/include
)
