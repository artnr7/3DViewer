#include "../../utils/logger.h"
#include "object_viewer_widget.h"
#include <GL/gl.h>
#include <qtclasshelpermacros.h>

#define TR_QTY 1
void s21::ObjectViewerWidget::initializeGL() {
  Lg::Log()->Info("initializeOpenGLFunctions");
  initializeOpenGLFunctions();

  Lg::Log()->Info("glClearColor");
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  // glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
  // установить цвет фона, который будет
  // храниться в GL_COLOR_BUFFER_BIT

  m_shader_program_ = new QOpenGLShaderProgram(this);
  LoadShaders();

  m_vao_.create();
  m_vao_.bind();

  m_vbo_.create();
  m_vbo_.bind();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  m_shader_program_->enableAttributeArray("aPos");
  m_shader_program_->setAttributeBuffer("aPos", GL_FLOAT, 0, 3);

  m_vbo_.release();
  m_vao_.release();
}

void s21::ObjectViewerWidget::resizeGL(int w, int h) {
  Lg::Log()->Info("ObjectViewerWidget::" + std::string(__func__));
  if (!vertices_ready_) {
    return;
  }
  glViewport(0, 0, w, h);
  m_projection.setToIdentity();
  m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
}

void s21::ObjectViewerWidget::paintGL() {
  // Lg::Log()->Info("ObjectViewerWidget::" + std::string(__func__));
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (!vertices_ready_) {
    return;
  }

  m_modelview.setToIdentity();

  m_shader_program_->bind();
  m_vao_.bind();
  glDrawArrays(GL_QUADS, 0, points_qty_);
  m_vao_.release();
  m_shader_program_->release();
}
