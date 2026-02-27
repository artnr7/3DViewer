#include "../../utils/logger.h"
#include "iostream"
#include "object_viewer_widget.h"
#include <GL/gl.h>
#include <qtclasshelpermacros.h>

#define TR_QTY 1
void s21::ObjectViewerWidget::initializeGL() {
  Lg::Log()->Info("initializeOpenGLFunctions");

  initializeOpenGLFunctions();

  Lg::Log()->Info("glClearColor");
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  // установить цвет фона, который будет
  // храниться в GL_COLOR_BUFFER_BIT

  // // Указывание вершин (и буферов) и настройка вершинных атрибутов
  // float vertices[] = {
  //     0.5f,  0.5f,  0.0f, // верхняя правая
  //     0.5f,  -0.5f, 0.0f, // нижняя правая
  //     -0.5f, -0.5f, 0.0f, // нижняя левая
  //     -0.5f, 0.5f,  0.0f  // верхняя левая
  // };
  // unsigned int indices[] = {
  //     // помните, что мы начинаем с 0!
  //     0, 1, 3, // первый треугольник
  //     1, 2, 3  // второй треугольник
  // };

  m_shader_program_ = new QOpenGLShaderProgram(this);
  LoadShaders();

  m_vao_->create();
  m_vao_->bind();

  m_vbo_->create();
  m_vbo_->bind();
  // m_vbo_.allocate(vertices, 12 * sizeof(GLfloat));

  m_ebo_->create();
  m_ebo_->bind();
  // m_ebo_->allocate(indices, 6 * sizeof(GLuint));

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
  m_projection.setToIdentity();
  m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
}

void s21::ObjectViewerWidget::paintGL() {
  // Lg::Log()->Info("ObjectViewerWidget::" + std::string(__func__));
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (!vertices_ready_ || !ebo_ready_) {
    return;
  }

  m_modelview.setToIdentity();

  m_shader_program_->bind();
  m_vao_->bind();
  // glDrawArrays(GL_QUADS, 0, points_qty_);
  // std::cout << ebo_qty_ << std::endl;
  glDrawElements(GL_LINES, ebo_qty_, GL_UNSIGNED_INT, 0);
  m_vao_->release();
  m_shader_program_->release();
}
