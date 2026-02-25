#include "object_viewer_widget.h"
#include <iostream>

namespace s21 {
void ObjectViewerWidget::ObjectInit() { file_uploaded_ = true; }

void ObjectViewerWidget::SetVBO(std::vector<float> &vert_attrs) {
  makeCurrent();
  // for (auto el : vert_attrs) {
  //   std::cout << el << " ";
  // }
  // std::cout << std::endl;

  data_ready_ = true;

  points_qty_ = vert_attrs.size();
  m_vbo_.bind();
  // size - это размер в байтах всех элементов
  m_vbo_.allocate(vert_attrs.data(), points_qty_ * sizeof(GLfloat));
  m_vbo_.release();
  doneCurrent();
}

void ObjectViewerWidget::SetBackgroundColor(int r, int g, int b) {
  // Lg::Log()->Info("ObjectViewerWidget::" + std::string(__func__));
  // std::cout << r << " " << g << " " << b << std::endl;
  // std::cout << r / 255.0f << " " << g / 255.0f << " " << b / 255.0f
  //           << std::endl;
  makeCurrent();
  glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
  doneCurrent();
}

} // namespace s21
