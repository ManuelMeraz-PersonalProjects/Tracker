add_library(FoodPlugin SHARED Food.cpp FoodPlugin.cpp)
add_library(tracker::FoodPlugin ALIAS FoodPlugin)

target_include_directories(FoodPlugin
                           PUBLIC ${PROJECT_SOURCE_DIR}/include
                                  ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(FoodPlugin
                      PUBLIC Qt5::Quick
                             Qt5::Core
                             Qt5::Widgets
                             tracker::food
                             tracker::database)

set(food_plugin_dir ${CONAN_QT_ROOT}/qml/tracker/food/)
install(TARGETS FoodPlugin DESTINATION ${food_plugin_dir}/Food/)
install(FILES qmldir DESTINATION ${food_plugin_dir}/Food/)

cotire(FoodPlugin)
