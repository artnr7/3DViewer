#include <iostream>

#include "../object_viewer_widget.hpp"

// s21::ObjectViewerWidget::ObjectViewerWidget() {
//
// }

s21::ObjectViewerWidget::ObjectViewerWidget(QWidget *parent)
    : QOpenGLWidget(parent), obj_filename_() {
  setWindowTitle("3DViewer");
  setGeometry(400, 200, 800, 600);
}

void s21::ObjectViewerWidget::EnterObjFilename() noexcept {
  obj_filename_ = "../objs/cube.obj";

  std::cout << "ObjectViewerWidget :: SetFilename: " << obj_filename_
            << std::endl;
  emit NewFilenameEnetered();
}