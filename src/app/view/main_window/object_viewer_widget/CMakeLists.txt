add_library(object_viewer_widget_lib STATIC
  src/connections.cc
  src/init.cc
  src/object_viewer_widget.cc
  src/shaders.cc
  src/slots.cc
  object_viewer_widget.h
)

target_include_directories(object_viewer_widget_lib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(object_viewer_widget_lib PRIVATE
  controller_lib
  main_window_lib
)

add_qt_interface(object_viewer_widget_lib)