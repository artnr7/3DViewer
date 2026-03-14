#include "obj_v_wid.h"
#include <GL/gl.h>
#include <iostream>
#include <qlogging.h>

namespace s21 {

void ObjectViewerWidget::MakeInGLContext(std::function<void()> f) {
  makeCurrent();
  f();
  doneCurrent();
}

void ObjectViewerWidget::SetVBO(std::vector<float> &vert_attrs) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  points_qty_ = vert_attrs.size();

  MakeInGLContext([&] {
    m_vbo_->bind();
    // size - это размер в байтах всех элементов
    m_vbo_->allocate(vert_attrs.data(), points_qty_ * sizeof(GLfloat));
    m_vbo_->release();
  });
  vertices_ready_ = true;
}

void ObjectViewerWidget::SetEBO(std::vector<uint> &vert_indx) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  if (ebo_ready_) {
    return;
  }

  ebo_qty_ = vert_indx.size();

  MakeInGLContext([&] {
    m_ebo_->bind();
    m_ebo_->allocate(vert_indx.data(), ebo_qty_ * sizeof(GLuint));
  });
  ebo_ready_ = true;
}

void ObjectViewerWidget::SetBackgroundColor(int r, int g, int b) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  bckg_clr_.setRgb(r, g, b);

  MakeInGLContext([&] {
    glClearColor(bckg_clr_.redF(), bckg_clr_.greenF(), bckg_clr_.blueF(),
                 bckg_clr_.alphaF());
  });
}

void ObjectViewerWidget::SetEdgeColor(int r, int g, int b) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  uColor_.setRgb(r, g, b);

  MakeInGLContext([&] {
    m_shader_program_->bind();
    m_shader_program_->setUniformValue(
        "uColor", QVector4D{uColor_.redF(), uColor_.greenF(), uColor_.blueF(),
                            uColor_.alphaF()});

    m_shader_program_->release();
  });
}

void ObjectViewerWidget::SetVerticesSize(float x) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));
  verts_point_sz_ = x;

  MakeInGLContext([&] { glPointSize(verts_point_sz_); });
}

void ObjectViewerWidget::SetLinesWidth(float x) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));
  line_w_ = x;

  MakeInGLContext([&] { glLineWidth(line_w_); });
}

void ObjectViewerWidget::SetDashSize(float x) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  dashsize = x;

  MakeInGLContext([&] {
    m_shader_program_->bind();
    m_shader_program_->setUniformValue("u_dashSize", dashsize);
    m_shader_program_->release();
  });
}

void ObjectViewerWidget::SetGapSize(float x) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  gapsize = x;

  MakeInGLContext([&] {
    m_shader_program_->bind();
    m_shader_program_->setUniformValue("u_gapSize", gapsize);
    m_shader_program_->release();
  });
}

void ObjectViewerWidget::SetDottedLine() {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  SetDashSize(DEF_DOTLINE_DASH_SIZE);
  SetGapSize(DEF_DOTLINE_GAP_SIZE);
}

void ObjectViewerWidget::SetSolidLine() {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  SetDashSize(DEF_SOLID_DASH_SIZE);
  SetGapSize(DEF_SOLID_GAP_SIZE);
}

} // namespace s21
