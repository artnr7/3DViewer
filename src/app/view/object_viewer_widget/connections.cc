#include "object_viewer_widget.h"

#include <QTimer>
#include <QtWidgets/QWidget>

void s21::ObjectViewerWidget::Connections() {
  connect(front_update_timer_, &QTimer::timeout, this,
          &s21::ObjectViewerWidget::FrontUpdate);
}
