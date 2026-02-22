#include "object_viewer_widget.h"
#include <memory>

namespace s21 {

ObjectViewerWidget::ObjectViewerWidget(int x_offset, int y_offset, int width,
                                       int height, QWidget *parent)
    // const std::string &obj_filename)
    //  : QOpenGLWidget(parent), obj_filename_(obj_filename) {
    : QOpenGLWidget(parent), width_(width), height_(height) {
  front_update_timer_ = new QTimer(this);

  // GUI
  setGeometry(x_offset, y_offset, width_, height_);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);

  format.setVersion(4, 5);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  // INIT
}

} // namespace s21
