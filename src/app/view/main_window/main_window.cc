#include "main_window.hpp"

#include "object_viewer_widget/object_viewer_widget.hpp"


s21::MainWindow::MainWindow() {
  p_obj_v_wid_ = new ObjectViewerWidget(this);
  // p_menu_wid_ = std::make_unique<MenuWidget>(this);
}