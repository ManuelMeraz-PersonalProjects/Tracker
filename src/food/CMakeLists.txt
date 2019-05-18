add_library(food STATIC Food.cpp Macronutrients.cpp)
add_library(tracker::food ALIAS food)

target_include_directories(food
                           PUBLIC ${CONAN_INCLUDE_DIRS}
                           PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(food ${CONAN_LIBS})
cotire(food)
