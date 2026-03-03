#include "object_viewer_widget.h"
#include <GL/gl.h>
#include <iostream>

namespace s21 {
void ObjectViewerWidget::ObjectInit() {
  if (file_uploaded_) { // если файл уже загружен
    vertices_ready_ = false;
    ebo_ready_ = false;
    ebo_qty_ = 0;
    points_qty_ = 0;
  }
  file_uploaded_ = true;
}

void ObjectViewerWidget::SetVBO(std::vector<float> &vert_attrs) {
  points_qty_ = vert_attrs.size();

  makeCurrent();
  m_vbo_->bind();
  // size - это размер в байтах всех элементов
  m_vbo_->allocate(vert_attrs.data(), points_qty_ * sizeof(GLfloat));
  m_vbo_->release();
  doneCurrent();
  vertices_ready_ = true;
}

void ObjectViewerWidget::SetEBO(std::vector<uint> &vert_indx) {
  if (ebo_ready_) {
    return;
  }

  ebo_qty_ = vert_indx.size();
  verts_point_sz_ = 4.0f;
  line_w_ = 0.5f;

  makeCurrent();
  m_ebo_->bind();
  m_ebo_->allocate(vert_indx.data(), ebo_qty_ * sizeof(GLuint));
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
