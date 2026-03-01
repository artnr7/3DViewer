#include "object_viewer_widget.h"
#include <qcoreevent.h>
#include <qevent.h>
#include <qlogging.h>
#include <qtimer.h>

#include "../../utils/logger.h"
namespace s21 {

void ObjectViewerWidget::OnFrontUpdateTimer() {
  // Lg::Log()->Info(std::string(__func__));
  update();

  emit BackgroundColorUpdate();

  if (file_uploaded_) {
    emit ActionGetGLVertices();
  }
}

bool ObjectViewerWidget::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() == QEvent::MouseMove) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    emit MouseUpdate(mouseEvent->pos().x(), mouseEvent->pos().y());
    // qDebug() << "Mouse move" << mouseEvent->pos().x();
  }
  return false;
}

} // namespace s21
