#include "../object_viewer_widget.hpp"

#include <iostream>

s21::ObjectViewerWidget::ObjectViewerWidget(QWidget *parent)
    : QOpenGLWidget(parent) {
  setWindowTitle("3DViewer");
  setGeometry(400, 200, 800, 600);
  m_shader_program_ = new QOpenGLShaderProgram(this);
}

void s21::ObjectViewerWidget::initializeGL() {
  initializeOpenGLFunctions();
  m_shader_program_ = new QOpenGLShaderProgram(this);
  glClearColor(1.0f, 0.5f, 0.0f, 1.0f);

  LoadShaders();

  // std::vector<GLdouble> glvertices = s21::Controller::GetVertices();
  // GLdouble vertices[glvertices.size()];

  // std::move(glvertices.begin(), glvertices.end(), vertices);
  // std::cout << "\n\n\n" << glvertices.size() << "\n\n\n\n";

  GLdouble vertices[] = {
      0.5,  1, 0.5,  0.5,  1, -0.5, 0.5,  0, 0.5,  0.5,  0, -0.5, -0.5, 1, -0.5,
      -0.5, 1, 0.5,  -0.5, 0, -0.5, -0.5, 0, 0.5,  -0.5, 1, -0.5, 0.5,  1, -0.5,
      -0.5, 1, 0.5,  0.5,  1, 0.5,  -0.5, 0, 0.5,  0.5,  0, 0.5,  -0.5, 0, -0.5,
      0.5,  0, -0.5, -0.5, 1, 0.5,  0.5,  1, 0.5,  -0.5, 0, 0.5,  0.5,  0, 0.5,
      0.5,  1, -0.5, -0.5, 1, -0.5, 0.5,  0, -0.5, -0.5, 0, -0.5};

  m_vao_.create();
  m_vao_.bind();

  m_vbo_.create();
  m_vbo_.bind();
  m_vbo_.allocate(vertices, sizeof(vertices));

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

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // glUniformMatrix4fv(projLoc, 1, GL_FALSE, m_projection.constData());

  m_shader_program_->bind();
  m_vao_.bind();
  glDrawArrays(GL_TRIANGLES, 0, 3);
  m_vao_.release();
  m_shader_program_->release();
}