add_library(view_lib STATIC
  src/app.cc
  src/view.cc
  include/app.h
)

add_qt_interface(view_lib)

add_subdirectory(main_window)

target_include_directories(view_lib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  main_window
  main_window/menu_widget
)

target_link_libraries(view_lib PRIVATE
  main_window_lib
)
