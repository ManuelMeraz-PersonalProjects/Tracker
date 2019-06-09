add_library(DatabasePlugin SHARED utils.cpp DatabasePlugin.cpp)
add_library(tracker::DatabasePlugin ALIAS DatabasePlugin)

target_include_directories(DatabasePlugin
                           PUBLIC ${PROJECT_SOURCE_DIR}/include
                                  ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(DatabasePlugin
                      PUBLIC Qt5::Quick
                             Qt5::Core
                             Qt5::Widgets
                             tracker::database
                             tracker::food
                             tracker::FoodPlugin)

set(database_plugin_dir ${CONAN_QT_ROOT}/qml/tracker/database/)
install(TARGETS DatabasePlugin DESTINATION ${database_plugin_dir}/)
install(TARGETS DatabasePlugin DESTINATION ${CMAKE_BINARY_DIR}/lib/tracker)
install(FILES qmldir DESTINATION ${database_plugin_dir}/)

cotire(DatabasePlugin)
