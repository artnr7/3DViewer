set(OBJECT_VIEWER_WIDGET_FILES
  src/connections.cc
  src/init.cc
  src/object_viewer_widget.cc
  src/shaders.cc
  src/slots.cc
  object_viewer_widget.h
)

add_library(object_viewer_widget_lib STATIC ${OBJECT_VIEWER_WIDGET_FILES})
register_format_sources(${OBJECT_VIEWER_WIDGET_FILES})

target_include_directories(object_viewer_widget_lib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(object_viewer_widget_lib PRIVATE
  controller_lib
  main_window_lib
)

target_link_qt(object_viewer_widget_lib)