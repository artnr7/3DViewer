#include "object_viewer_widget.h"
#include <qtimer.h>

#include "../../utils/logger.h"

void s21::ObjectViewerWidget::OnObjectBuilded() {
  Lg::Log()->Info(std::string(__func__));
  emit ActionGetGLVertices();
  // initGL();
  // front_update_timer_->start(15);
}

void s21::ObjectViewerWidget::OnUpdateFront() {
  Lg::Log()->Info(std::string(__func__));
  update();
}

void s21::ObjectViewerWidget::OnFrontUpdateTimer() {
  Lg::Log()->Info(std::string(__func__));
  emit ActionGetGLVertices();
}
