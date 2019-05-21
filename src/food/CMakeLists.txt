add_library(food STATIC Food.cpp Macronutrients.cpp)
add_library(tracker::food ALIAS food)

target_include_directories(food
                           PUBLIC ${PROJECT_SOURCE_DIR}/include
                                  ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(food
                      CONAN_PKG::soci
                      CONAN_PKG::nameof
                      CONAN_PKG::range-v3)
cotire(food)
