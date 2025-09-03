#pragma once

#include <QtCore/qconfig.h>

#if QT_VERSION_MAJOR < 6
#warning "QT_VERSION_MAJOR < 6"
// #if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
// #error "Qt version not supported"
// #else
#include <QtWidgets/QOpenGLWidget>
// #endif
#else
#warning "QT_VERSION_MAJOR >= 6"
#include <QtOpenGLWidgets/QOpenGLWidget>
#endif

#include <QtGui/QOpenGLFunctions>

#include <QtCore/QPoint>
#include <QtGui/QMouseEvent>

inline QPointF mouseEventPosition(QMouseEvent *event) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  return event->position();
#else
  return event->pos();
#endif
}

class TriangleWidget : public QOpenGLWidget, protected QOpenGLFunctions {
public:
  TriangleWidget(QWidget *parent = nullptr);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

private:
  QPoint _lastPos;
  double _azimuth;
  double _declination;
  double _distance;
};