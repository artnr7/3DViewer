#include "object_viewer_widget.h"
#include <vector>

#define TR_QTY 1
void s21::ObjectViewerWidget::initializeGL() {}
void s21::ObjectViewerWidget::initGL() {
  initializeOpenGLFunctions();
  m_shader_program_ = new QOpenGLShaderProgram(this);
  glClearColor(1.0f, 0.5f, 0.0f, 1.0f); // установить цвет фона, который будет
                                        // храниться в GL_COLOR_BUFFER_BIT
  LoadShaders();

  auto glv_size = vert_attrs_->size();
  verts_qty_ = glv_size / 3;

  m_vao_.create();
  m_vao_.bind();

  m_vbo_.create();
  m_vbo_.bind();
  m_vbo_.allocate(vert_attrs_->data(), glv_size * sizeof(GLfloat));
  // m_vbo_.allocate(vertices, sizeof(vertices));

  m_shader_program_->enableAttributeArray("aPos");
  m_shader_program_->setAttributeBuffer("aPos", GL_FLOAT, 0, 3);

  m_vbo_.release();
  m_vao_.release();
}

void s21::ObjectViewerWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  m_projection.setToIdentity();
  m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
}

void s21::ObjectViewerWidget::paintGL() {
  m_modelview.setToIdentity();

  emit ActionGetGLVertices();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // glUniformMatrix4fv(projLoc, 1, GL_FALSE, m_projection.constData());

  m_shader_program_->bind();
  m_vao_.bind();
  glDrawArrays(GL_TRIANGLES, 0, 3 * verts_qty_);
  // glDrawArrays(GL_TRIANGLES, 0, 3 * TR_QTY);
  m_vao_.release();
  m_shader_program_->release();
}
