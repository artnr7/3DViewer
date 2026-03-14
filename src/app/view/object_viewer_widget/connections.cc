#include "obj_v_wid.h"

#include <QTimer>
#include <QtWidgets/QWidget>

#include "../../utils/logger.h"

void s21::ObjectViewerWidget::SetupConnections() {
  Lg::Log()->Info(std::string(__func__));

  connect(front_update_timer_, &QTimer::timeout, this,
          &s21::ObjectViewerWidget::OnFrontUpdateTimer);
}
