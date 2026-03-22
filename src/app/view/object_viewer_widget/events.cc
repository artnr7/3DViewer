#include <qevent.h>
#include <qlogging.h>
#include <qnamespace.h>
#include <qpoint.h>
#include <qtimezone.h>

#include "iostream"
#include "obj_v_wid.h"

namespace s21 {
bool ObjectViewerWidget::eventFilter(QObject* obj, QEvent* event) {
  // Y then X
  auto e = event->type();
  auto* m_e = static_cast<QMouseEvent*>(event);
  int my = 0, mx = 0;

  if (e == QEvent::MouseMove || e == QEvent::MouseButtonPress ||
      e == QEvent::MouseButtonRelease) {
    my = m_e->pos().y();
    mx = m_e->pos().x();
  }

#define MULT 1e-3
  static int i = 0;
  if (e == QEvent::MouseMove && IsGLBuffersReady()) {
    if (!(i++ % 5)) {
      start_pos_.setY(my);
      start_pos_.setX(mx);
      if (i == 5) {
        i = 0;
      }
    }

    float shift_y = MULT * (-static_cast<float>(my - start_pos_.y()));
    float shift_x = MULT * (static_cast<float>(mx - start_pos_.x()));

    if (lb_clicked_) {
      emit MouseRotYChanged(shift_y * 10);
      emit MouseRotXChanged(-shift_x * 10);
    }

    if (rb_clicked_) {
      emit MouseTransYChanged(shift_y);
      emit MouseTransXChanged(shift_x);
    }

    // qDebug() << "Mouse move Y" << shift_y << "Mouse move X " << shift_x;
  }

  if (e == QEvent::Wheel) {
    auto* w_e = static_cast<QWheelEvent*>(event);
    emit MouseTransZChanged(MULT * w_e->angleDelta().ry());
    qDebug() << w_e->position() << w_e->angleDelta();
  }
  // if (e != QEvent::Paint) {
  //   qDebug() << e;
  // }

  MouseClickFilter(*m_e, my, mx);

  return false;
}

void ObjectViewerWidget::MouseClickFilter(QMouseEvent& m_e, int m_y, int m_x) {
  if (!IsGLBuffersReady()) {
    return;
  }

  if (m_e.type() == QEvent::MouseButtonPress) {
    switch (m_e.button()) {
      case Qt::LeftButton:
        lb_clicked_ = true;
        break;
      case Qt::RightButton:
        rb_clicked_ = true;
        break;
    }
    start_pos_.setY(m_y);
    start_pos_.setX(m_x);
    // qDebug() << "Mouse CLICK" << start_pos_.y() << start_pos_.x();
  }

  if (m_e.type() == QEvent::MouseButtonRelease) {
    switch (m_e.button()) {
      case Qt::LeftButton:
        lb_clicked_ = false;
        break;
      case Qt::RightButton:
        rb_clicked_ = false;
        break;
    }
    start_pos_.setY(0);
    start_pos_.setX(0);
    // qDebug() << "Mouse Release" << start_pos_.y() << start_pos_.x();
  }
}

}  // namespace s21
