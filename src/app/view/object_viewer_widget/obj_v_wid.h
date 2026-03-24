#ifndef MAIN_WIDGET_HPP_
#define MAIN_WIDGET_HPP_

// #include <QOpenGLExtraFunctions>
#include <GL/gl.h>
#include <qnamespace.h>
#include <qvectornd.h>

#include <QOpenGLWidget>
#include <QTimer>
#include <QtGui>
#include <QtOpenGL>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "../../api/primitives.h"
#include "../../utils/logger.h"
#include "../config.h"

namespace s21 {
enum class VertsStyle { None, Square, Circle };
enum class EdgesStyle { Solid, Dot };

class ObjectViewerWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  ObjectViewerWidget(
      int x_offset, int y_offset, int width, int height,
      QWidget* parent = nullptr);  //, const std::string &obj_filename);

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 signals:
  // Affine
  void MouseTransYChanged(float y);
  void MouseTransXChanged(float x);
  void MouseTransZChanged(float z);

  void MouseRotYChanged(float y);
  void MouseRotXChanged(float x);

  // Vert
  void updVertSzRequested();
  void updVertStyleRequested();
  void updVertClrRequested();

  // Edge
  void updEdgeSzRequested();
  void updEdgeStyleRequested();
  void updEdgeClrRequested();

  // Misc
  void updBckgClrRequested();

  void updGLVertRequested();

 private slots:
  void OnFrontUpdateTimerTimeout() {
    Lg::Log()->Trace(std::string(__func__));
    update();

    emit updBckgClrRequested();

    if (!file_uploaded_) {
      return;
    }
    emit updGLVertRequested();

    // Vert
    emit updVertSzRequested();
    emit updVertStyleRequested();
    emit updVertClrRequested();

    // Edge
    emit updEdgeSzRequested();
    emit updEdgeStyleRequested();
    emit updEdgeClrRequested();
  }
  bool eventFilter(QObject* obj, QEvent* event) override;

 private:
  // Methods ----------------------------------------→
  void LoadShaders();
  void SetupConnections() {
    Lg::Log()->Info(std::string(__func__));

    connect(front_update_timer_, &QTimer::timeout, this,
            &s21::ObjectViewerWidget::OnFrontUpdateTimerTimeout);

    connect(gif_timer_, &QTimer::timeout, this, &s21::ObjectViewerWidget::MGIF);
  }

  // GL Context
  void MakeInGLContext(const std::function<void()>);
  void MakeInGLShader(const std::function<void()>);

  inline bool IsGLBuffersReady() { return vertices_ready_ && ebo_ready_; };

  // Variables ----------------------------------------→

  // Buffers / shader program
  QOpenGLBuffer* m_vbo_ = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  QOpenGLBuffer* m_ebo_ = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
  QOpenGLVertexArrayObject* m_vao_ = new QOpenGLVertexArrayObject();
  QOpenGLShaderProgram* m_shader_program_;

  // Colors
  const char uMeshClrName_[9] = "uMeshClr";
  QColor uEdgeClr_ = Qt::darkCyan;
  QColor uVertClr_ = Qt::darkYellow;

  QColor bckg_clr_ = Qt::gray;

  // Measures
  float vert_sz_ = 4.0f;
  float edge_sz_ = 0.5f;

  VertsStyle vert_style_ = VertsStyle::Square;
  EdgesStyle edge_style_ = EdgesStyle::Solid;

#define DEF_DOTLINE_DASH_SIZE 5.0f
#define DEF_DOTLINE_GAP_SIZE 15.0f

#define DEF_SOLID_DASH_SIZE 0.0f
#define DEF_SOLID_GAP_SIZE 0.0f

  float dash_sz_ = 0.0f;  // расстояние между чёрточками
  float gap_sz_ = 0.0f;   // длина чёрточки

  // Resolution
  int width_ = INIT_W_MAIN_WIN;
  int height_ = INIT_H_MAIN_WIN;
  QVector2D resolution_ =
      QVector2D(static_cast<float>(width_), static_cast<float>(height_));

  // Model desc
  bool file_uploaded_ = false;
  bool vertices_ready_ = false;
  bool ebo_ready_ = false;

  size_t ebo_qty_ = 0;
  size_t vbo_points_qty_ = 0;

  // Update timer
  QTimer* front_update_timer_ = new QTimer(this);
  // GIF
  QTimer* gif_timer_ = new QTimer(this);
  bool gif_status = false;
  bool img_status = false;
  std::vector<QImage> images_{};

  uint16_t gif_w_ = 640;
  uint16_t gif_h_ = 480;
  uint16_t delay_ = 10;  // 1 delay == 10 msc

  // Mouse
  QPoint start_pos_{0, 0};
  bool lb_clicked_ = false;
  bool rb_clicked_ = false;
  void MouseClickFilter(QMouseEvent& m_e, int m_y, int m_x);

 public:
  void ObjectInit();

  // Setters
  void SetVertSz(float);
  void SetVertStyle(VertsStyle style);
  void SetVertClr(Color);

  void SetEdgeSz(float x);
  void SetEdgeStyle(EdgesStyle style);
  void SetEdgeClr(Color);

  // clang-format off
      void SetDottedEdgeStyle();
      void SetSolidEdgeStyle();

      void SetDashSz(float);  // чёрточка
      void SetGapSz(float);   // пропуск м/у чёрточками
  // clang-format on

  void SetBckgClr(Color);

  // Buffers
  void SetVBO(std::vector<float>& vert_attrs);
  void SetEBO(std::vector<uint>& vert_indx);

  void MakeGIF();
  void MakeImage();
  void MGIF();
  Str GetTimeStamp();
};
}  // namespace s21

#endif
