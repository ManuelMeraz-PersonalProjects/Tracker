qt5_add_resources(gui_resources gui.qrc)

add_library(gui STATIC sidepanel.cpp ${gui_resources})
add_library(tracker::gui ALIAS gui)

target_include_directories(gui
                           PUBLIC ${PROJECT_SOURCE_DIR}/include
                                  ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(gui PUBLIC Qt5::Quick Qt5::Core Qt5::Widgets)

cotire(gui)
