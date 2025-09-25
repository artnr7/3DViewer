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
  ObjectViewerWidget(QWidget *parent = nullptr,
                     const std::string &obj_filename);

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  void LoadShaders();
  void Connections();

  // Variables -------------------→
  // Graphics →
  size_t vert_qty_;
  QMatrix4x4 m_modelview;
  QMatrix4x4 m_projection;
  // GLint projLoc;
  QOpenGLBuffer m_vbo_;
  QOpenGLVertexArrayObject m_vao_;
  QOpenGLShaderProgram *m_shader_program_;
  // Model →
  std::string obj_filename_;

 public:
  // void EnterObjFilename() noexcept;
  // void SetObjFilename() noexcept;
};
}  // namespace s21

#endif
