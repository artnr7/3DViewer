#include "../main_window.hpp"

void s21::MainWindow::CreateNewObjectWidget() {
  if (p_obj_v_wid_ != nullptr) {
    delete p_obj_v_wid_;
  }

  p_obj_v_wid_ = new ObjectViewerWidget();
}