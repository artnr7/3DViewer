#ifndef MAIN_WIDGET_HPP_
#define MAIN_WIDGET_HPP_

// #include <QOpenGLExtraFunctions>
// #include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QtGui>
#include <QtOpenGL>

namespace s21 {
class ObjectViewerWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
public:
  ObjectViewerWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent);

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

private:
  QMatrix4x4 m_modelview;
  QMatrix4x4 m_projection;
  // GLint projLoc;
  // QOpenGLVertexArrayObject m_vao;
  // QOpenGLBuffer m_vbo;
  QOpenGLShaderProgram *m_program;
  // QOpenGLShader *m_shader;
  // QOpenGLTexture *m_texture;
  GLuint shader_program;
  GLuint VBO;
  GLuint VAO;
  QOpenGLExtraFunctions *f;
};
} // namespace s21

#endif
