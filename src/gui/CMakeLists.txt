add_library(gui STATIC plusminus.cpp)
add_library(tracker::gui ALIAS gui)

target_include_directories(gui PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(gui PUBLIC Qt5::Core Qt5::Widgets)

cotire(gui)
