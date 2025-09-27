#include <iostream>

#include "../main_window.hpp"

void s21::MainWindow::CreateNewObjectWidget(const std::string &obj_filename) {
  if (p_obj_v_wid_ != nullptr) {
    delete p_obj_v_wid_;
  }

  p_obj_v_wid_ = new ObjectViewerWidget(this, obj_filename);
  p_obj_v_wid_->show();
}

void s21::MainWindow::CreateNewObjectImitated() {
  static int i = 0;
  if (i++) return;
  const std::string &obj_filename = "../objs/c1ube.obj";
  // const std::string &obj_filename = "../objs/2.obj";
  // const std::string &obj_filename = "../objs/FinalBaseMesh.obj";
  std::cout << "\n\n---------------\n\n";
  emit NewFilenameEntered(obj_filename);
}