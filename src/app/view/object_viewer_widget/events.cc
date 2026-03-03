#include "iostream"
#include "object_viewer_widget.h"
#include <qnamespace.h>
#include <qpoint.h>

namespace s21 {
bool ObjectViewerWidget::eventFilter(QObject *obj, QEvent *event) {
  // Y then X
  auto e = event->type();
  auto *m_e = static_cast<QMouseEvent *>(event);
  int my = 0, mx = 0;

  if (e == QEvent::MouseMove || e == QEvent::MouseButtonPress ||
      e == QEvent::MouseButtonRelease) {
    my = m_e->pos().y();
    mx = m_e->pos().x();
  }

  if (e == QEvent::MouseMove) {
    emit MouseUpdate(my - start_pos_.y(), mx - start_pos_.x());
    qDebug() << "Mouse move" << my;
    qDebug() << "Mouse move" << mx;
  }

  RightButton(*m_e, my, mx);

  return false;
}

void ObjectViewerWidget::RightButton(QMouseEvent &m_e, int m_y, int m_x) {
  if (m_e.button() == Qt::RightButton) {
    if (m_e.type() == QEvent::MouseButtonPress) {
      start_pos_.setY(m_y);
      start_pos_.setX(m_x);
      qDebug() << "Mouse CLICK!!!" << start_pos_.y() << " " << start_pos_.x();
    }
    if (m_e.type() == QEvent::MouseButtonRelease) {
      start_pos_.setY(0);
      start_pos_.setX(0);
      qDebug() << "Mouse Release..." << start_pos_.y() << " " << start_pos_.x();
    }
  }
}

} // namespace s21
