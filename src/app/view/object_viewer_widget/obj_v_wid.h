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
enum class VerticeStyle { Square, Circle };
enum class EdgesStyle { Solid, Dot };

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
  void VertexClrUpd();

  // Size / Thickness
  void VerticesSizeUpdate();
  void LineWidthUpdate();

  // Line
  void ContinuityLineUpdate();

  void VerticeStyleUpdate();

  void ActionGetGLVertices();
  void UpdateFront();
  void MouseUpdateY(float y);
  void MouseUpdateX(float x);
  void MouseRotateY(float y);
  void MouseRotateX(float x);

private slots:
  void OnFrontUpdateTimer() {

    Lg::Log()->Trace(std::string(__func__));
    update();

    emit BackgroundColorUpdate();

    if (file_uploaded_) {
      emit ActionGetGLVertices();
      emit EdgeColorUpdate();
      emit LineWidthUpdate();
      emit VerticesSizeUpdate();
      emit VerticeStyleUpdate();
      emit ContinuityLineUpdate();
      emit VertexClrUpd();
    }
  }
  bool eventFilter(QObject *obj, QEvent *event) override;

private:
  // Methods ----------------------------------------→
  void LoadShaders();
  void SetupConnections() {

    Lg::Log()->Info(std::string(__func__));

    connect(front_update_timer_, &QTimer::timeout, this,
            &s21::ObjectViewerWidget::OnFrontUpdateTimer);
  }

  // GL Context
  void MakeInGLContext(std::function<void()>);

  inline bool IsGLBuffersReady(){
    return vertices_ready_ && ebo_ready_;
  };

  // Variables ----------------------------------------→

  // Buffers / shader program
  QOpenGLBuffer *m_vbo_;
  QOpenGLBuffer *m_ebo_;
  QOpenGLVertexArrayObject *m_vao_;
  QOpenGLShaderProgram *m_shader_program_;

  // Colors
  QColor uEdgeClr_ = Qt::darkCyan;
  const char uEdgeColorName[9] = "uEdgeClr";
  QColor uVertexClr_ = Qt::darkCyan;
  const char uVertexColorName[11] = "uVertexClr";

  QColor bckg_clr_ = Qt::gray;

  // Measures
  float verts_point_sz_ = 4.0f;
  float edge_w_ = 0.5f;

  VerticeStyle vertex_style_ = VerticeStyle::Square;
  EdgesStyle edge_style_ = EdgesStyle::Solid;

#define DEF_DOTLINE_DASH_SIZE 5.0f
#define DEF_DOTLINE_GAP_SIZE 15.0f

#define DEF_SOLID_DASH_SIZE 0.0f
#define DEF_SOLID_GAP_SIZE 0.0f

  float dash_sz_ = 0.0f; // расстояние между чёрточками
  float gap_sz_ = 0.0f;  // длина чёрточки

  // Resolution
  int width_ = 1280;
  int height_ = 720;
  QVector2D resolution_ =
      QVector2D(static_cast<float>(width_), static_cast<float>(height_));

  // Model desc
  bool file_uploaded_ = false;
  bool vertices_ready_ = false;
  bool ebo_ready_ = false;
  size_t ebo_qty_ = 0;
  size_t points_qty_ = 0;

  // Update timer
  QTimer *front_update_timer_;

  // Mouse
  QPoint start_pos_{0, 0};
  bool lb_clicked_ = false;
  bool rb_clicked_ = false;
  void MouseClickFilter(QMouseEvent &m_e, int m_y, int m_x);

public:
  void ObjectInit();

  // Setters
  // Buffers
  void SetVBO(std::vector<float> &vert_attrs);
  void SetEBO(std::vector<uint> &vert_indx);

  // Color
  void SetBckgClr(int r, int g, int);
  void SetEdgeColor(int r, int g, int b);
  void SetVertexClr(int r, int g, int b);

  // Measures
  void SetEdgeW(float x);
  void SetVertexSz(float x);

  // Style
  void SetVertexStyle(VerticeStyle style);

  void SetEdgeStyle(EdgesStyle style);
  void SetDottedLine();
  void SetSolidLine();
  void SetDashSize(float);
  void SetGapSize(float);
};
} // namespace s21

#endif
