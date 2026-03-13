#include "object_viewer_widget.h"
#include <GL/gl.h>
#include <iostream>
#include <qlogging.h>

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

  makeCurrent();
  m_ebo_->bind();
  m_ebo_->allocate(vert_indx.data(), ebo_qty_ * sizeof(GLuint));
  doneCurrent();
  ebo_ready_ = true;
}

void ObjectViewerWidget::SetBackgroundColor(int r, int g, int b) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  bckg_clr_.setRgb(r, g, b);

  makeCurrent();
  glClearColor(bckg_clr_.redF(), bckg_clr_.greenF(), bckg_clr_.blueF(),
               bckg_clr_.alphaF());
  doneCurrent();
}

void ObjectViewerWidget::SetEdgeColor(int r, int g, int b) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  uColor_.setRgb(r, g, b);

  makeCurrent();
  m_shader_program_->bind();
  m_shader_program_->setUniformValue(
      "uColor", QVector4D{uColor_.redF(), uColor_.greenF(), uColor_.blueF(),
                          uColor_.alphaF()});

  m_shader_program_->release();
  doneCurrent();
}

void ObjectViewerWidget::SetVerticesSize(float x) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));
  verts_point_sz_ = x;

  makeCurrent();
  glPointSize(verts_point_sz_);
  doneCurrent();
}
void ObjectViewerWidget::SetLinesWidth(float x) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));
  line_w_ = x;

  makeCurrent();
  glLineWidth(line_w_);
  doneCurrent();
}

} // namespace s21
