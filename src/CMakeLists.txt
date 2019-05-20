add_subdirectory(food)
add_subdirectory(database)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE tracker::food tracker::database)

add_executable(gui gui.cpp)
target_link_libraries(gui PRIVATE Qt5::Core Qt5::Widgets)

cotire(main gui)
