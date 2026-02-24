#include "object_viewer_widget.h"
#include <QSurfaceFormat>
#include <qopenglfunctions.h>

#include "../../utils/logger.h"

namespace s21 {

ObjectViewerWidget::ObjectViewerWidget(int x_offset, int y_offset, int width,
                                       int height, QWidget *parent)
    : QOpenGLWidget(parent), width_(width), height_(height),
      file_uploaded_(false)
// ,QOpenGLFunctions()
{
  // Lg::Log()->Info(std::string(__func__) + " constuctor");

  front_update_timer_ = new QTimer(this);
  front_update_timer_->start(100);

  // GUI
  setGeometry(x_offset, y_offset, width_, height_);
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
