#include "../object_viewer_widget.hpp"

#include <GL/gl.h>

#include "../../../../controller/controller.hpp"

#define TR_QTY 1
void s21::ObjectViewerWidget::initializeGL() {
  initializeOpenGLFunctions();
  m_shader_program_ = new QOpenGLShaderProgram(this);
  glClearColor(bckg_color_[0], bckg_color_[1], bckg_color_[2], bckg_color_[3]);

  LoadShaders();

  glvertices_ = s21::Controller::GetVertices();

  auto glv_size = glvertices_->size();

  vert_qty_ = glv_size / 3;

  // GLdouble vertices[] = {
  //     0.5f,  1.0f, 0.5f,  0.5f,  1.0f, -0.5f, 0.5f,  0.0f, 0.5f,
  //     0.5f,  0.0f, -0.5f, -0.5f, 1.0f, -0.5f, -0.5f, 1.0f, 0.5f,
  //     -0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f,  -0.5f, 1.0f, -0.5f,
  //     0.5f,  1.0f, -0.5f, -0.5f, 1.0f, 0.5f,  0.5f,  1.0f, 0.5f,
  //     -0.5f, 0.0f, 0.5f,  0.5f,  0.0f, 0.5f,  -0.5f, 0.0f, -0.5f,
  //     0.5f,  0.0f, -0.5f, -0.5f, 1.0f, 0.5f,  0.5f,  1.0f, 0.5f,
  //     -0.5f, 0.0f, 0.5f,  0.5f,  0.0f, 0.5f,  0.5f,  1.0f, -0.5f,
  //     -0.5f, 1.0f, -0.5f, 0.5f,  0.0f, -0.5f, -0.5f, 0.0f, -0.5f};

  // GLfloat vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
  //                       0.0f,  0.0f,  0.5f, 0.0f};

  m_vao_.create();
  m_vao_.bind();

  m_vbo_.create();
  m_vbo_.bind();
  m_vbo_.allocate(glvertices_->data(), glv_size * sizeof(GLfloat));
  // m_vbo_.allocate(vertices, sizeof(vertices));

  m_shader_program_->enableAttributeArray("aPos");
  m_shader_program_->setAttributeBuffer("aPos", GL_FLOAT, 0, 3);

  m_vbo_.release();
  m_vao_.release();
}

void s21::ObjectViewerWidget::resizeGL(int w, int h) {
  // glViewport(0, 0, w, h);
  s21::Controller::SetPerspective(w, h);
}

void s21::ObjectViewerWidget::paintGL() {
  glvertices_ = s21::Controller::GetVertices();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // glUniformMatrix4fv(projLoc, 1, GL_FALSE, m_projection.constData());

  m_shader_program_->bind();
  m_vao_.bind();
  glDrawArrays(GL_TRIANGLES, 0, 3 * vert_qty_);
  // glDrawArrays(GL_TRIANGLES, 0, 3 * TR_QTY);
  m_vao_.release();
  m_shader_program_->release();
}