#ifndef MAIN_WIDGET_HPP_
#define MAIN_WIDGET_HPP_

// #include <QOpenGLExtraFunctions>
#include "../../utils/logger.h"
#include <GL/gl.h>
#include <QOpenGLWidget>
#include <QTimer>
#include <QtGui>
#include <QtOpenGL>
#include <cstddef>
#include <qnamespace.h>
#include <qvectornd.h>
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
  // Color
  void BackgroundColorUpdate();
  void EdgeColorUpdate();

  // Size / Thickness
  void VerticesSizeUpdate();
  void LineWidthUpdate();

  // Line
  void ContinuityLineUpdate();

  void ActionGetGLVertices();
  void UpdateFront();
  void MouseUpdateY(float y);
  void MouseUpdateX(float x);
  void MouseRotateY(float y);
  void MouseRotateX(float x);

private slots:
  void OnFrontUpdateTimer();
  bool eventFilter(QObject *obj, QEvent *event) override;

private:
  void LoadShaders();
  void SetupConnections();

  // Variables -------------------→

  // Graphics →
  QOpenGLBuffer *m_vbo_;
  QOpenGLBuffer *m_ebo_;
  QOpenGLVertexArrayObject *m_vao_;
  QOpenGLShaderProgram *m_shader_program_;

  QColor uColor_ = Qt::darkCyan;
  QColor bckg_clr_ = Qt::gray;

  float verts_point_sz_ = 4.0f;
  float line_w_ = 0.5f;

#define DEF_DOTLINE_DASH_SIZE 5.0f
#define DEF_DOTLINE_GAP_SIZE 15.0f

#define DEF_SOLID_DASH_SIZE 0.0f
#define DEF_SOLID_GAP_SIZE 0.0f

  float dashsize = 0.0f; // расстояние между чёрточками
  float gapsize = 0.0f;  // длина чёрточки

  // Model →
  // std::string obj_filename_;
  bool file_uploaded_ = false;
  bool vertices_ready_ = false;
  bool ebo_ready_ = false;
  size_t ebo_qty_ = 0;
  size_t points_qty_ = 0;

  QTimer *front_update_timer_;

  // Mouse
  QPoint start_pos_{0, 0};
  bool lb_clicked_ = false;
  bool rb_clicked_ = false;
  void RightButton(QMouseEvent &m_e, int m_y, int m_x);

  // Resolution
  int width_ = 1280;
  int height_ = 720;
  QVector2D resolution_ =
      QVector2D(static_cast<float>(width_), static_cast<float>(height_));

  // GL Context
  void MakeInGLContext(std::function<void()>);

public:
  // void initGL();
  void ObjectInit();

  // Setters
  void SetVBO(std::vector<float> &vert_attrs);
  void SetEBO(std::vector<uint> &vert_indx);
  void SetBackgroundColor(int r, int g, int);
  void SetEdgeColor(int r, int g, int);
  void SetVerticesSize(float x);
  void SetLinesWidth(float x);

  void SetContinuityLine();
  void SetDottedLine();
  void SetSolidLine();
  void SetDashSize(float);
  void SetGapSize(float);
};
} // namespace s21

#endif
