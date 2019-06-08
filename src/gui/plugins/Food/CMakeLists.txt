add_library(FoodPlugin SHARED Food.cpp FoodPlugin.cpp)
add_library(tracker::FoodPlugin ALIAS FoodPlugin)

target_include_directories(FoodPlugin
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(FoodPlugin PUBLIC Qt5::Quick Qt5::Core Qt5::Widgets)

install(TARGETS FoodPlugin 
  DESTINATION ${CONAN_QT_ROOT}/qml/org/example/io/
  )

install(
  FILES qmldir
  DESTINATION ${CONAN_QT_ROOT}/qml/org/example/io/
  )
cotire(FoodPlugin)
