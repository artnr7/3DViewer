#include <iostream>

#include "../main_window.hpp"

void s21::MainWindow::CreateNewObjectWidget(const std::string &obj_filename) {
  if (p_obj_v_wid_ != nullptr) {
    delete p_obj_v_wid_;
  }

  p_obj_v_wid_ = new ObjectViewerWidget(this, obj_filename);
}

void s21::MainWindow::CreateNewObjectImitated() {
  const std::string &obj_filename = "../objs/cube.obj";
  std::cout << "\n\n---------------\n\n";
  emit NewFilenameEntered(obj_filename);
}