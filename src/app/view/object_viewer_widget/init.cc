#include "object_viewer_widget.h"
#include <QSurfaceFormat>
#include <qopenglbuffer.h>
#include <qopenglfunctions.h>
#include <qopenglvertexarrayobject.h>

#include "../../utils/logger.h"

namespace s21 {

ObjectViewerWidget::ObjectViewerWidget(int x_offset, int y_offset, int width,
                                       int height, QWidget *parent)
    : QOpenGLWidget(parent) {
  Lg::Log()->Info(std::string(__func__) + " constuctor");

  m_vao_ = new QOpenGLVertexArrayObject();
  m_vbo_ = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  m_ebo_ = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);

  installEventFilter(this);

  front_update_timer_ = new QTimer(this);
  front_update_timer_->start(16);

  // GUI
  setGeometry(x_offset, y_offset, width, height);
  //
  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);

  format.setVersion(3, 3);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  SetupConnections();
}

} // namespace s21
