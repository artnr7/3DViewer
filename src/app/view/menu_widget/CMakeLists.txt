register_format_cmake_file()

#* action_types interface *#
set(ACTION_TYPES_FILES interface/action_types.h)
register_format_sources(${ACTION_TYPES_FILES})

add_library(action_types INTERFACE)
target_include_directories(action_types INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/interface
)
## action_types interface

set(MENU_WIDGET_FILES
    menu_widget.cc
    menu_builder/builder_contexts.cc
    panel/panel.cc
    panel/panel_items.cc
    buttons/double_button_base.cc
    buttons/exclusive_double_button.cc
    buttons/independent_double_button.cc
    buttons/trash_button.cc
    combobox/combo_box.cc
    combobox/custom_delegate.cc
    colordialog/brightness_slider.cc
    colordialog/color_picker.cc
    colordialog/color_select_dialog.cc
    colordialog/color_wheel.cc
    filedialog/file_dialog_button.cc
    filedialog/file_dialog_panel.cc
    status_info/status_info.cc
    menu_widget.h
    menu_builder/builder_contexts.h
    menu_builder/menu_builder.h
    panel/panel.h
    panel/panel_items.h
    value_controller/value_controller.h
    value_controller/value_controller_base.h
    buttons/double_button_base.h
    buttons/exclusive_double_button.h
    buttons/independent_double_button.h
    buttons/trash_button.h
    combobox/combo_box.h
    combobox/custom_delegate.h
    colordialog/brightness_slider.h
    colordialog/color_picker.h
    colordialog/color_select_dialog.h
    colordialog/color_wheel.h
    filedialog/file_dialog_button.h
    filedialog/file_dialog_panel.h
    status_info/status_info.h
    style_configs/trash_button_style.h
    style_configs/status_bar_style.h
    style_configs/brightness_slider_style.h
    style_configs/color_picker_style.h
    style_configs/color_select_dialog_style.h
    style_configs/color_wheel_style.h
    style_configs/combo_box_style.h
    style_configs/file_dialog_button_style.h
    style_configs/file_dialog_panel_style.h
    style_configs/panel_items_style.h
    style_configs/value_controller_style.h
    interface/action_types.h
  )

add_library(menu_widget_lib STATIC ${MENU_WIDGET_FILES})
register_format_sources(${MENU_WIDGET_FILES})

target_include_directories(menu_widget_lib
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/
)

# target_link_libraries(menu_widget_lib PRIVATE action_types model_types)
target_link_libraries(menu_widget_lib PUBLIC action_types )

target_link_qt(menu_widget_lib)
