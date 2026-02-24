#ifndef MAIN_WIDGET_HPP_
#define MAIN_WIDGET_HPP_

// #include <QOpenGLExtraFunctions>
// #include <QOpenGLVertexArrayObject>
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
  QTimer *front_update_timer_;

public:
  void initGL();
  void SetGLVertices(std::vector<float> &vert_attrs) {
    vert_attrs = vert_attrs;
  }

  // Fields
  int width_;
  int height_;
};
} // namespace s21

#endif
