#include "object_viewer_widget.h"
#include <GL/gl.h>
#include <iostream>

namespace s21 {
void ObjectViewerWidget::ObjectInit() { file_uploaded_ = true; }

void ObjectViewerWidget::SetVBO(std::vector<float> &vert_attrs) {
  makeCurrent();

  vertices_ready_ = true;

  points_qty_ = vert_attrs.size();
  m_vbo_->bind();
  // size - это размер в байтах всех элементов
  m_vbo_->allocate(vert_attrs.data(), points_qty_ * sizeof(GLfloat));
  m_vbo_->release();
  doneCurrent();
}

void ObjectViewerWidget::SetEBO(std::vector<uint> &vert_indx) {
  if (ebo_ready_) {
    return;
  }

  // std::cout << "-----------------------" << std::endl;
  //
  // for (auto el : vert_indx) {
  //   std::cout << el << " ";
  // }
  //
  // std::cout << "\n-----------------------" << std::endl;

  ebo_qty_ = vert_indx.size();

  makeCurrent();
  m_vao_->bind();
  m_ebo_->bind();
  m_ebo_->allocate(vert_indx.data(), ebo_qty_ * sizeof(GLuint));

  m_vao_->release();
  doneCurrent();
  ebo_ready_ = true;
}

void ObjectViewerWidget::SetBackgroundColor(int r, int g, int b) {
  // Lg::Log()->Info("ObjectViewerWidget::" + std::string(__func__));
  makeCurrent();
  glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
  doneCurrent();
}

} // namespace s21
