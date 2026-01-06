add_library(menu_widget_lib STATIC
  menu_widget.cc
  panel/panel.cc
  panel/panel_items.cc
  value_controller/value_controller.cc
  buttons/double_button_base.cc
  buttons/exclusive_double_button.cc
  buttons/independent_double_button.cc
  combobox/combo_box.cc
  combobox/custom_delegate.cc

  menu_widget.h
  panel/panel.h
  panel/panel_items.h
  value_controller/value_controller.h
  buttons/double_button_base.h
  buttons/exclusive_double_button.h
  buttons/independent_double_button.h
  combobox/combo_box.h
  combobox/custom_delegate.h
)

target_include_directories(menu_widget_lib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(menu_widget_lib PRIVATE
  main_window_lib
)

add_qt_interface(menu_widget_lib)