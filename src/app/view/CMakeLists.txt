register_format_cmake_file()

add_library(view_lib STATIC
  connections.cc
  slots.cc
  view.cc
  view.h
  config.h)

add_subdirectory(menu_widget)
add_subdirectory(object_viewer_widget)

target_include_directories(view_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(
  view_lib PUBLIC menu_widget_lib object_viewer_widget_lib utils_lib controller_lib)

target_link_qt(view_lib)
