set(FOOD_SOURCE_FILES Food.cpp Macronutrients.cpp)

add_library(food STATIC ${FOOD_SOURCE_FILES})

target_include_directories(food
                           PUBLIC ${tracker_include}
                           PUBLIC ${nameof_include}
                           PUBLIC ${ranges_include})

target_link_libraries(food ${CONAN_LIBS})
cotire(food)
