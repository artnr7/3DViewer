#ifndef MAIN_WIDGET_HPP_
#define MAIN_WIDGET_HPP_

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

namespace s21 {
class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions {
public:
  MainWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent) {}

protected:
  void initializeGL() override {
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  }

  void resizeGL(int w, int h) override {
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
  }

  void paintGL() override {
    initializeOpenGLFunctions();
    glClear(GL_COLOR_BUFFER_BIT);
  }
};
} // namespace s21

#endif