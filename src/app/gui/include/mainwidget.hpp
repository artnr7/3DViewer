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
    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  }

  void resizeGL(int w, int h) override {
    initializeOpenGLFunctions();

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1, 1, -1, 1, 1, 2);

    // m_projection.setToIdentity();
    // m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
    // m_projection.perspective(45.0f, w / float(h), 0.0f, -2.0f);
  }

  void paintGL() override {
    initializeOpenGLFunctions();

    glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(90, 0, 0, 1);

    // float vex[] = {0, 0, -1.5, 1, 0, -1.5, 0, 1, -1.5};

    // glVertexPointer(3, GL_FLOAT, 0, &vex);
    // glEnableClientState(GL_VERTEX_ARRAY);

    // glDrawArrays(GL_TRIANGLES, 0, 3);

    // glDisableClientState(GL_VERTEX_ARRAY);

    glBegin(GL_TRIANGLES);
    glColor3d(1.0f, 0.0f, 0.0f);
    glVertex2d(0.0f, 0.0f);
    glVertex2d(0.0f, 1.0f);
    glVertex2d(1.0f, 0.0f);
    glEnd();
  }

 private:
  QMatrix4x4 m_modelview;
  QMatrix4x4 m_projection;
  QOpenGLVertexArrayObject m_vao;
  QOpenGLBuffer m_vbo;
  QOpenGLShaderProgram *m_program;
  QOpenGLShader *m_shader;
  QOpenGLTexture *m_texture;
};
}  // namespace s21

#endif