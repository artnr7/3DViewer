#include "TriangleWidget.h"

// #include <QApplication>
#include <cmath>

#include <GL/glu.h>
#include <QtCore/QDebug>

TriangleWidget::TriangleWidget(QWidget *parent) : QOpenGLWidget(parent) {
  _azimuth = 0.0f;     // Start facing the positive X axis
  _declination = 0.0f; // Start looking straight ahead
  _distance = 3.0f;    // Start 3 units away from the origin
}

void TriangleWidget::initializeGL() {
  // Initialize OpenGL functions
  initializeOpenGLFunctions();

  // Set clear color to black
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void TriangleWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float aspect = static_cast<float>(w) / static_cast<float>(h);
  gluPerspective(45.0, aspect, 0.1, 100.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void TriangleWidget::mousePressEvent(QMouseEvent *event) {
  qDebug() << "press ev :" << mouseEventPosition(event);
  if (event->button() == Qt::LeftButton) {
    _lastPos = event->pos();
  }
}

void TriangleWidget::mouseMoveEvent(QMouseEvent *event) {
  qDebug() << "move ev :" << mouseEventPosition(event);
  if (event->buttons() & Qt::LeftButton) {
    int dx = mouseEventPosition(event).x() - _lastPos.x();
    int dy = mouseEventPosition(event).y() - _lastPos.y();
    _azimuth -= dx * 0.5 * 0.01;
    _declination += dy * 0.5 * 0.01;
    _lastPos = event->pos();
    update();
  }
}

void TriangleWidget::wheelEvent(QWheelEvent *event) {
  qDebug() << "wheel ev angle delta:" << event->angleDelta();
  qDebug() << "wheel ev pixel delta:" << event->pixelDelta();
  int numDegrees = event->angleDelta().y() / 8;
  int numSteps = numDegrees / 15;
  _distance += numSteps;
  update();
}

void TriangleWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  GLfloat camX = _distance * sin(_azimuth) * cos(_declination);
  GLfloat camY = _distance * sin(_declination);
  GLfloat camZ = _distance * cos(_azimuth) * cos(_declination);
  gluLookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);

  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 0.0f, 0.0f); // red
  glVertex3f(-1.0f, -1.0f, 0.0f);
  glColor3f(0.0f, 1.0f, 0.0f); // green
  glVertex3f(0.0f, 1.0f, 0.0f);
  glColor3f(0.0f, 0.0f, 1.0f); // blue
  glVertex3f(1.0f, -1.0f, 0.0f);
  glEnd();
}