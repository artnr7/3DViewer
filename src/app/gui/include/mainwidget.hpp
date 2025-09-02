#ifndef MAIN_WIDGET_HPP_
#define MAIN_WIDGET_HPP_

#include <QOpenGLWidget>
#include <QtGui>
#include <QtOpenGL>

namespace s21 {
class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
public:
  MainWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent) {
    setWindowTitle("3DViewer");
    setGeometry(400, 200, 800, 600);
  }

protected:
  void initializeGL() override {
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  }

  void resizeGL(int w, int h) override {
    glViewport(0, 0, w, h);

    m_projection.setToIdentity();
    m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
  }

  void paintGL() override {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

private:
  QMatrix4x4 m_projection;
  QOpenGLVertexArrayObject m_vao;
  QOpenGLBuffer m_vbo;
  QOpenGLShaderProgram *m_program;
  QOpenGLShader *m_shader;
  QOpenGLTexture *m_texture;
};
} // namespace s21

#endif