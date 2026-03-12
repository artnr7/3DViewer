#include "iostream"
#include "object_viewer_widget.h"
#include <qlogging.h>
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

#define MULT 0.001
  static int i = 0;
  if (e == QEvent::MouseMove) {
    // qDebug() << vertices_ready_ << ebo_ready_ << lb_clicked_ << "\n";
    if (!vertices_ready_ || !ebo_ready_ || !rb_clicked_) {
    } else {

      if (!(i++ % 5)) {
        start_pos_.setY(my);
        start_pos_.setX(mx);
        if (i == 5) {
          i = 0;
        }
      }

      auto shift_y = MULT * (-static_cast<float>(my - start_pos_.y()));
      auto shift_x = MULT * (static_cast<float>(mx - start_pos_.x()));

      emit MouseUpdateY(shift_y);
      emit MouseUpdateX(shift_x);

      // qDebug() << "Mouse move Y " << shift_y;
      // qDebug() << "Mouse move X " << shift_x;
    }
  }

  // if (e != QEvent::Paint) {
  //   qDebug() << "++++++++++++++++" << e << vertices_ready_ << ebo_ready_
  //            << lb_clicked_ << "\n";
  // }
  if (e == QEvent::MouseMove) {
    // qDebug() << "++++++++++++++++" << vertices_ready_ << ebo_ready_
    //          << lb_clicked_ << "\n";
    if (!vertices_ready_ || !ebo_ready_ || !lb_clicked_) {
    } else {
      if (!(i++ % 5)) {
        start_pos_.setY(my);
        start_pos_.setX(mx);
        if (i == 5) {
          i = 0;
        }
      }

      auto shift_y = MULT * 10 * (-static_cast<float>(my - start_pos_.y()));
      auto shift_x = MULT * 10 * (static_cast<float>(mx - start_pos_.x()));

      emit MouseRotateY(shift_y);
      emit MouseRotateX(shift_x);
      // qDebug() << "Mouse move Y " << shift_y;
      // qDebug() << "Mouse move X " << shift_x;
    }
  }

  RightButton(*m_e, my, mx);

  return false;
}

void ObjectViewerWidget::RightButton(QMouseEvent &m_e, int m_y, int m_x) {
  if (!vertices_ready_ || !ebo_ready_) {
    return;
  }

  if (m_e.button() == Qt::RightButton) {
    if (m_e.type() == QEvent::MouseButtonPress) {
      rb_clicked_ = true;
      start_pos_.setY(m_y);
      start_pos_.setX(m_x);
      // qDebug() << "Mouse CLICK!!!" << start_pos_.y() << " " <<
      // start_pos_.x();
    }
    if (m_e.type() == QEvent::MouseButtonRelease) {
      rb_clicked_ = false;
      start_pos_.setY(0);
      start_pos_.setX(0);
      // qDebug() << "Mouse Release..." << start_pos_.y() << " " <<
      // start_pos_.x();
    }
  }
  if (m_e.button() == Qt::LeftButton) {
    if (m_e.type() == QEvent::MouseButtonPress) {
      lb_clicked_ = true;
      start_pos_.setY(m_y);
      start_pos_.setX(m_x);
      // qDebug() << "Mouse CLICK!!!" << start_pos_.y() << " " <<
      // start_pos_.x();
    }
    if (m_e.type() == QEvent::MouseButtonRelease) {
      lb_clicked_ = false;
      start_pos_.setY(0);
      start_pos_.setX(0);
      // qDebug() << "Mouse Release..." << start_pos_.y() << " " <<
      // start_pos_.x();
    }
  }
}

} // namespace s21
