set(FOOD_SOURCE_FILES Food.cpp Macronutrients.cpp)

add_library(food STATIC ${FOOD_SOURCE_FILES})

target_include_directories(food
                           PUBLIC ${CONAN_INCLUDE_DIRS}
                           PUBLIC ${tracker_include}
                           PUBLIC ${ranges_include})

target_link_libraries(food ${CONAN_LIBS})
cotire(food)
