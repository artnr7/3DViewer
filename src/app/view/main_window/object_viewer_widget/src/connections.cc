#include <QTimer>

#include "../object_viewer_widget.hpp"

void s21::ObjectViewerWidget::Connections() {
  update_timer_ = new QTimer(this);
  update_timer_->start(15);

  connect(update_timer_, &QTimer::timeout, this,
          &s21::ObjectViewerWidget::update);
}
