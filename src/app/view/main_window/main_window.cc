#include "main_window.hpp"

#include <iostream>

#include "menu_widget/menu_widget.hpp"
#include "object_viewer_widget/object_viewer_widget.hpp"

s21::MainWindow::MainWindow() {
  p_obj_v_wid_ = std::make_unique<ObjectViewerWidget>(this);
  p_menu_wid_ = std::make_unique<MenuWidget>(this);
}