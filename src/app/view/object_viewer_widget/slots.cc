#include "object_viewer_widget.h"
#include <qtimer.h>

void s21::ObjectViewerWidget::OnObjectBuilded() {
  initGL();
  front_update_timer_->start(15);
}

void s21::ObjectViewerWidget::FrontUpdate() { update(); }
