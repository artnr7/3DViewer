#include <GL/gl.h>
#include <qlogging.h>
#include <qvariant.h>

#include "obj_v_wid.h"

namespace s21 {

void ObjectViewerWidget::MakeInGLContext(const std::function<void()> f) {
  makeCurrent();
  f();
  doneCurrent();
}

void ObjectViewerWidget::MakeInGLShader(const std::function<void()> f) {
  m_shader_program_->bind();
  f();
  m_shader_program_->release();
}

void ObjectViewerWidget::SetVBO(std::vector<float>& vert_attrs) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  vbo_points_qty_ = vert_attrs.size();

  MakeInGLContext([&] {
    m_vbo_->bind();
    // size - это размер в байтах всех элементов
    m_vbo_->allocate(vert_attrs.data(), vbo_points_qty_ * sizeof(GLfloat));
    m_vbo_->release();
  });
  vertices_ready_ = true;
}

void ObjectViewerWidget::SetEBO(std::vector<uint>& vert_indx) {
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

void ObjectViewerWidget::SetBckgClr(Color clr) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  bckg_clr_.setRgb(clr.x, clr.y, clr.z);

  MakeInGLContext([&] {
    glClearColor(bckg_clr_.redF(), bckg_clr_.greenF(), bckg_clr_.blueF(),
                 bckg_clr_.alphaF());
  });
}

void ObjectViewerWidget::SetEdgeClr(Color clr) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  uEdgeClr_.setRgb(clr.x, clr.y, clr.z);

  MakeInGLContext([&] {
    m_shader_program_->bind();
    m_shader_program_->setUniformValue(
        uEdgeClrName_, QVector4D{uEdgeClr_.redF(), uEdgeClr_.greenF(),
                                 uEdgeClr_.blueF(), uEdgeClr_.alphaF()});

    m_shader_program_->release();
  });
}

void ObjectViewerWidget::SetVertClr(Color clr) {
  uVertClr_.setRgb(clr.x, clr.y, clr.z);
}

void ObjectViewerWidget::SetVertSz(float x) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));
  vert_sz_ = x;

  MakeInGLContext([&] { glPointSize(vert_sz_); });
}

void ObjectViewerWidget::SetEdgeSz(float x) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));
  edge_sz_ = x;

  MakeInGLContext([&] { glLineWidth(edge_sz_); });
}

void ObjectViewerWidget::SetVertStyle(VertsStyle style) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));
  vertex_style_ = style;

  switch (vertex_style_) {
    case VertsStyle::Square:
      // qDebug() << "SQUARE";
      MakeInGLContext([&] { glDisable(GL_POINT_SMOOTH); });
      break;
    case VertsStyle::Circle:
      // qDebug() << "CIRCLE";
      MakeInGLContext([&] { glEnable(GL_POINT_SMOOTH); });
      break;
  }
}

void ObjectViewerWidget::SetEdgeStyle(EdgesStyle style) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));
  edge_style_ = style;

  switch (edge_style_) {
    case EdgesStyle::Solid:
      SetSolidEdgeStyle();
      break;
    case EdgesStyle::Dot:
      SetDottedEdgeStyle();
      break;
  }
}

void ObjectViewerWidget::SetDashSz(float dash_sz) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  dash_sz_ = dash_sz;

  MakeInGLContext([&] {
    m_shader_program_->bind();
    m_shader_program_->setUniformValue("u_dashSize", dash_sz_);
    m_shader_program_->release();
  });
}

void ObjectViewerWidget::SetGapSz(float gap_sz) {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  gap_sz_ = gap_sz;

  MakeInGLContext([&] {
    m_shader_program_->bind();
    m_shader_program_->setUniformValue("u_gapSize", gap_sz_);
    m_shader_program_->release();
  });
}

void ObjectViewerWidget::SetDottedEdgeStyle() {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  SetDashSz(DEF_DOTLINE_DASH_SIZE);
  SetGapSz(DEF_DOTLINE_GAP_SIZE);
}

void ObjectViewerWidget::SetSolidEdgeStyle() {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  SetDashSz(DEF_SOLID_DASH_SIZE);
  SetGapSz(DEF_SOLID_GAP_SIZE);
}

}  // namespace s21
