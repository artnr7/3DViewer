#include <qevent.h>

#include "../object_viewer_widget.hpp"

void s21::ObjectViewerWidget::mousePressEvent(QMouseEvent *mo) {
  mPos_ = mo->pos();
}

void s21::ObjectViewerWidget::mouseMoveEvent(QMouseEvent *mo) {
  xRot_ = 1 / M_PI * (mo->pos().y() - mPos_.y());
  yRot_ = 1 / M_PI * (mo->pos().x() - mPos_.x());
}