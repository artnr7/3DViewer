#ifndef MAIN_WIDGET_HPP_
#define MAIN_WIDGET_HPP_

// #include <QOpenGLExtraFunctions>
// #include <QOpenGLVertexArrayObject>
#include <qevent.h>

#include <QOpenGLWidget>
#include <QtGui>
#include <QtOpenGL>
#include <array>

namespace s21 {

enum class VerticeMappingType {
  Nothing,
  Circle,
  Square,
};

enum class ProjectionType {
  Ortho,
  Perspective,
};

class ObjectViewerWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  ObjectViewerWidget(QWidget *parent, const std::string &obj_filename);

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  void LoadShaders();
  void Connections();

  // Mouse --------→
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  QPoint mPos_;
  double xRot_, yRot_, zRot_;

  QTimer *update_timer_ = nullptr;
  std::vector<float> *glvertices_ = nullptr;

  // Variables -------------------→
  // Graphics →
  std::array<GLclampf, 4> bckg_color_ = {1.0f, 0.5f, 0.0f, 1.0f};
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
  // Color ------------>
  // Background
  void SetBckgColor(const std::array<GLclampf, 4> &color);
  void SetEdgeColor();
  void SetVerticeColor();

  // Edge thickness -------------→
  void SetEdgeThickness();

  // Vertices ---------------------------→
  // Mapping ---→
  void SetVerticeMapping(const VerticeMappingType &v_map_type);
  // Size ---→
  void SetVerticeSize();
};
}  // namespace s21

#endif
