#include "object_viewer_widget.h"
#include <qtimer.h>

#include "../../utils/logger.h"

void s21::ObjectViewerWidget::OnObjectBuilded() {
  Lg::Log()->Info(std::string(__func__));
  file_uploaded_ = true;
  // initGL();
}

void s21::ObjectViewerWidget::OnUpdateFront() {
  Lg::Log()->Info(std::string(__func__));
  update();
}

void s21::ObjectViewerWidget::OnFrontUpdateTimer() {
  Lg::Log()->Info(std::string(__func__));

  emit BackgroundColorUpdate();

  if (file_uploaded_) {
    emit ActionGetGLVertices();
  }
}
