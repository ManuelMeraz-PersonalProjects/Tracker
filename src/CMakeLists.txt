add_subdirectory(food)
add_subdirectory(database)
add_subdirectory(gui)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE tracker::food tracker::database)

add_executable(app app.cpp gui/gui.qrc)
target_link_libraries(app PRIVATE tracker::gui)

cotire(main app)
