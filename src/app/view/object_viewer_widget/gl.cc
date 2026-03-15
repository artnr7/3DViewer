#include "../../utils/logger.h"
#include "iostream"
#include "obj_v_wid.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <qtclasshelpermacros.h>

#define TR_QTY 1
void s21::ObjectViewerWidget::initializeGL() {
  Lg::Log()->Info("initializeOpenGLFunctions");

  initializeOpenGLFunctions();

  // Lg::Log()->Info("glClearColor");
  glClearColor(bckg_clr_.redF(), bckg_clr_.greenF(), bckg_clr_.blueF(),
               bckg_clr_.alphaF());
  // установить цвет фона, который будет
  // храниться в GL_COLOR_BUFFER_BIT
  glEnable(GL_DEPTH_TEST);

  m_shader_program_ = new QOpenGLShaderProgram(this);
  LoadShaders();

  m_vao_->create();
  m_vao_->bind();

  m_vbo_->create();
  m_vbo_->bind();
  m_vbo_->setUsagePattern(QOpenGLBuffer::DynamicDraw);

  m_ebo_->create();
  m_ebo_->bind();
  m_ebo_->setUsagePattern(QOpenGLBuffer::DynamicDraw);

  m_shader_program_->enableAttributeArray("aPos");
  m_shader_program_->setAttributeBuffer("aPos", GL_FLOAT, 0, 3);

  m_vbo_->release();
  m_vao_->release();
}

void s21::ObjectViewerWidget::resizeGL(int w, int h) {
  Lg::Log()->Info("ObjectViewerWidget::" + std::string(__func__));

  if (!vertices_ready_ || !ebo_ready_) {
    return;
  }
  glViewport(0, 0, w, h);
}

void s21::ObjectViewerWidget::paintGL() {
  Lg::Log()->Trace("ObjectViewerWidget::" + std::string(__func__));

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (!vertices_ready_ || !ebo_ready_) {
    return;
  }

  m_shader_program_->bind();
  m_vao_->bind();
  m_ebo_->bind();

  glDrawElements(GL_LINES, ebo_qty_, GL_UNSIGNED_INT, (void *)0);
  glLineWidth(edge_w_);

  // points
  m_shader_program_->setUniformValue(uEdgeColorName, uVertexClr_);
  glPointSize(verts_point_sz_);
  glDrawArrays(GL_POINTS, 0, points_qty_ / 3);
  m_shader_program_->setUniformValue(uEdgeColorName, uEdgeClr_);

  // glEnable(GL_BLEND);
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  m_vao_->release();
  m_ebo_->release();
  m_shader_program_->release();
}
