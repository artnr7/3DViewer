add_library(main_window_lib STATIC
  src/connections.cc
  src/main_window.cc
  src/slots.cc
  main_window.h
  config.h
)

add_subdirectory(menu_widget)
add_subdirectory(object_viewer_widget)

target_include_directories(main_window_lib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  menu_widget
  object_viewer_widget
)

target_link_libraries(main_window_lib PRIVATE
  menu_widget_lib
  object_viewer_widget_lib
  utils_lib
)

add_qt_interface(main_window_lib)
