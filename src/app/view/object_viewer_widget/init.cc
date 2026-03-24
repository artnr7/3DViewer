#include <qopenglbuffer.h>
#include <qopenglfunctions.h>
#include <qopenglvertexarrayobject.h>

#include <QSurfaceFormat>

#include "../../utils/logger.h"
#include "obj_v_wid.h"

namespace s21 {

ObjectViewerWidget::ObjectViewerWidget(int x_offset, int y_offset, int width,
                                       int height, QWidget* parent)
    : QOpenGLWidget(parent) {
  Lg::Log()->Info(std::string(__func__) + " constuctor");

  // GUI
  setGeometry(x_offset, y_offset, width, height);
  //
  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);

  format.setVersion(4, 5);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  installEventFilter(this);

  front_update_timer_->start(16);

  // GIF
  images_.reserve(50);

  SetupConnections();
}

void ObjectViewerWidget::ObjectInit() {
  if (file_uploaded_) {  // если файл уже загружен
    vertices_ready_ = false;
    ebo_ready_ = false;
    ebo_qty_ = 0;
    vbo_points_qty_ = 0;
  }
  file_uploaded_ = true;
}

}  // namespace s21
