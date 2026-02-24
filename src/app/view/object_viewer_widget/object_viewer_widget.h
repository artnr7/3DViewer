#ifndef MAIN_WIDGET_HPP_
#define MAIN_WIDGET_HPP_

// #include <QOpenGLExtraFunctions>
// #include <QOpenGLVertexArrayObject>
#include <GL/gl.h>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtGui>
#include <QtOpenGL>
#include <vector>

namespace s21 {
class ObjectViewerWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
public:
  ObjectViewerWidget(
      int x_offset, int y_offset, int width, int height,
      QWidget *parent = nullptr); //, const std::string &obj_filename);

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

signals:
  void BackgroundColorUpdate();
  void ObjectParseStarted();
  void ActionGetGLVertices();
  void UpdateFront();

private slots:
  void OnObjectBuilded();
  void OnUpdateFront();
  void OnFrontUpdateTimer();

private:
  void LoadShaders();
  void SetupConnections();

  // Variables -------------------→
  // Graphics →
  std::vector<float> *vert_attrs_;
  size_t verts_qty_;
  QMatrix4x4 m_modelview;
  QMatrix4x4 m_projection;
  // GLint projLoc;
  QOpenGLBuffer m_vbo_;
  QOpenGLVertexArrayObject m_vao_;
  QOpenGLShaderProgram *m_shader_program_;
  // Model →
  std::string obj_filename_;
  bool file_uploaded_ = false;

  QTimer *front_update_timer_;

public:
  void initGL();
  void ObjectInit();
  void SetVBO(std::vector<float> &vert_attrs) {
    verts_qty_ = vert_attrs.size() / 3;
    m_vbo_.bind();
    // size - это размер в байтах всех элементов
    m_vbo_.allocate(vert_attrs.data(), verts_qty_ * 3 * sizeof(GLfloat));
    m_vbo_.release();
  }

  void SetBackgroundColor(int r, int g, int b) {
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
  }

  // Fields
  int width_;
  int height_;
};
} // namespace s21

#endif
