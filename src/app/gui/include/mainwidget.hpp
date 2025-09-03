#ifndef MAIN_WIDGET_HPP_
#define MAIN_WIDGET_HPP_

// // #include <QOpenGLExtraFunctions>
// // #include <QOpenGLVertexArrayObject>
// #include <GL/glu.h>

// #include <QOpenGLWidget>
// #include <QtGui/QOpenGLFunctions>
// #include <QtGui>
// #include <QtOpenGL>
// #include <QtOpenGLWidgets/QOpenGLWidget>
// #include <cmath>

// namespace s21 {
// class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions {
//   Q_OBJECT
//  public:
//   MainWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent) {
//     setWindowTitle("3DViewer");
//     setGeometry(400, 200, 800, 600);
//     _azimuth = 0.0f;      // Start facing the positive X axis
//     _declination = 0.0f;  // Start looking straight ahead
//     _distance = 3.0f;     // Start 3 units away from the origin
//   }

//  protected:
//   void initializeGL() override {
//     initializeOpenGLFunctions();
//     // glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
//     glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//   }

//   void resizeGL(int w, int h) override {
//     glViewport(0, 0, w, h);

//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();

//     float aspect = static_cast<float>(w) / static_cast<float>(h);
//     gluPerspective(45.0, aspect, 0.1, 100.0);

//     // glOrtho(-1, 1, -1, 1, 1, 2);

//     // m_projection.setToIdentity();
//     // m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
//     // m_projection.perspective(45.0f, w / float(h), 0.0f, -2.0f);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
//   }

//   void paintGL() override {
//     // glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glEnable(GL_DEPTH_TEST);

//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();

//     // glRotatef(90, 0, 0, 1);

//     GLfloat camX = _distance * sin(_azimuth) * cos(_declination);
//     GLfloat camY = _distance * sin(_declination);
//     GLfloat camZ = _distance * cos(_azimuth) * cos(_declination);
//     gluLookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);

//     // float vex[] = {0, 0, -1.5, 1, 0, -1.5, 0, 1, -1.5};

//     // glVertexPointer(3, GL_FLOAT, 0, &vex);
//     // glEnableClientState(GL_VERTEX_ARRAY);

//     // glDrawArrays(GL_TRIANGLES, 0, 3);

//     // glDisableClientState(GL_VERTEX_ARRAY);

//     // glBegin(GL_TRIANGLES);
//     // glColor3d(1.0f, 0.0f, 0.0f);
//     // glVertex2f(0.0f, 0.0f);
//     // glColor3d(1.0f, 0.0f, 0.0f);
//     // glVertex2f(0.0f, 1.0f);
//     // glColor3d(1.0f, 0.0f, 0.0f);
//     // glVertex2f(1.0f, 0.0f);
//     // glEnd();

//     glBegin(GL_TRIANGLES);
//     glColor3f(1.0f, 0.0f, 0.0f);  // red
//     glVertex3f(-1.0f, -1.0f, 0.0f);
//     glColor3f(0.0f, 1.0f, 0.0f);  // green
//     glVertex3f(0.0f, 1.0f, 0.0f);
//     glColor3f(0.0f, 0.0f, 1.0f);  // blue
//     glVertex3f(1.0f, -1.0f, 0.0f);
//     glEnd();

//     // auto f = context()->extraFunctions();
//     // // Инициализация (например, в инициализаторе OpenGL)
//     // GLuint VBO, VAO;
//     // f->glGenVertexArrays(1, &VAO);
//     // glGenBuffers(1, &VBO);

//     // f->glBindVertexArray(VAO);

//     // glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
//     // GL_STATIC_DRAW);

//     // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
//     //                       (void *)0);
//     // glEnableVertexAttribArray(0);

//     // glBindBuffer(GL_ARRAY_BUFFER, 0);
//     // f->glBindVertexArray(0);

//     // // В функции отрисовки
//     // f->glBindVertexArray(VAO);
//     // glDrawArrays(GL_TRIANGLES, 0, 3);
//     // f->glBindVertexArray(0);
//   }

//  private:
//   QMatrix4x4 m_modelview;
//   QMatrix4x4 m_projection;
//   QOpenGLVertexArrayObject m_vao;
//   QOpenGLBuffer m_vbo;
//   QOpenGLShaderProgram *m_program;
//   QOpenGLShader *m_shader;
//   QOpenGLTexture *m_texture;
//   double _azimuth;
//   double _declination;
//   double _distance;
//   // public:
//   //   void paint() { paintGL(); }
// };
// }  // namespace s21

// #endif

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QtGui>
#include <QtOpenGL>
namespace s21 {
class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  MainWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent) {}

 protected:
  void initializeGL() override {
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  }

  void paintGL() override {
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();
  }

  void resizeGL(int w, int h) override { glViewport(0, 0, w, h); }
};
}  // namespace s21
#endif