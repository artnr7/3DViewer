#include "value_controller.h"

#include <QApplication>
#include <QKeyEvent>
#include <QMouseEvent>

namespace s21 {

ValueController::ValueController(int width, int height, QWidget* parent)
    : QWidget(parent),
      current_value_(0),
      min_value_(0),
      max_value_(100),
      step_size_(1),
      step_speed_(15),
      is_dragging_(false),
      widget_size_(width, height) {
  SetupUI();
  SetupConntctions();
}

void ValueController::SetupUI() {
  setFixedSize(widget_size_);
  setStyleSheet("background-color: transparent;");
  setFocusPolicy(Qt::StrongFocus);

  const int container_border_radius = 5;

  QWidget* container = new QWidget(this);
  container->setFixedSize(widget_size_);
  container->setStyleSheet(CreateContainerStyle(container_border_radius));

  int arrwo_font_size = widget_size_.height() * 0.4;
  int value_font_size = widget_size_.height() * 0.4;
  int button_width = widget_size_.width() * 0.15;
  int button_height = widget_size_.height();
  int element_height = widget_size_.height() * 0.9;
  int field_width = widget_size_.width() - 2 * button_width;

  main_layout_ = new QHBoxLayout(container);
  main_layout_->setSpacing(0);
  main_layout_->setContentsMargins(0, 0, 0, 0);
  main_layout_->setAlignment(Qt::AlignCenter);

  left_button_ = new QPushButton("<", container);
  left_button_->setFixedSize(button_width, button_height);
  left_button_->setStyleSheet(CreateButtonStyle(
      arrwo_font_size, container_border_radius, 0, container_border_radius, 0));

  value_field_ = new QLineEdit(container);
  value_field_->setFixedSize(field_width, element_height);
  value_field_->setAlignment(Qt::AlignCenter);
  value_field_->setStyleSheet(CreateValueFieldStyle(value_font_size));
  value_field_->setCursor(Qt::ArrowCursor);
  value_field_->installEventFilter(this);
  value_field_->setText("0");
  value_field_->setReadOnly(true);

  right_button_ = new QPushButton(">", container);
  right_button_->setFixedSize(button_width, button_height);
  right_button_->setStyleSheet(CreateButtonStyle(
      arrwo_font_size, 0, container_border_radius, 0, container_border_radius));

  main_layout_->addWidget(left_button_);
  main_layout_->addWidget(value_field_);
  main_layout_->addWidget(right_button_);
}

QString ValueController::CreateContainerStyle(int border_radius) const {
  return QString(R"(
    background-color: #545454;
    border: none;
    border-radius: %1px;
  )")
      .arg(border_radius);
}

QString ValueController::CreateButtonStyle(int font_size, int radius_tl,
                                           int radius_tr, int radius_bl,
                                           int radius_br) const {
  return QString(R"(
    QPushButton {
      background-color: transparent;
      border: none;
      font-size: %1px;
      font-weight: bold;
      color: white;
      border-top-left-radius: %2px;
      border-bottom-left-radius: %3px;
      border-top-right-radius: %4px;
      border-bottom-right-radius: %5px;
    }
    QPushButton:hover {
      background-color: #484848;
    }
    QPushButton:pressed {
      background-color: #404040;
    }
  )")
      .arg(font_size)
      .arg(radius_tl)
      .arg(radius_bl)
      .arg(radius_tr)
      .arg(radius_br);
}

QString ValueController::CreateValueFieldStyle(int font_size) const {
  return QString(R"(
      QLineEdit {
        background-color: transparent;
        border: none;
        font-size: %1px;
        font-weight: bold;
        color: white;
        selection-background-color: #b0b0b0;
      }
    )")
      .arg(font_size);
}

void ValueController::SetupConntctions() {
  connect(left_button_, &QPushButton::clicked, this,
          [this]() { SetCurrentValue(current_value_ - step_size_); });

  connect(right_button_, &QPushButton::clicked, this,
          [this]() { SetCurrentValue(current_value_ + step_size_); });
}

bool ValueController::eventFilter(QObject* obj, QEvent* event) {
  bool result{false};
  if (obj == value_field_) {
    if (event->type() == QEvent::MouseButtonDblClick) {
      result = MouseButtonDblClickEvent(event);
    } else if (event->type() == QEvent::MouseButtonPress) {
      result = MouseButtonPressEvent(event);
    } else if (event->type() == QEvent::MouseMove && is_dragging_) {
      result = MouseMoveEvent(event);
    } else if (event->type() == QEvent::MouseButtonRelease && is_dragging_) {
      result = MouseButtonReleaseEvent();
    } else if (event->type() == QEvent::FocusOut) {
      result = FocusOutEvent();
    } else if (event->type() == QEvent::KeyPress) {
      result = KeyPressEvent(event);
    }
  }

  return result ? result : QWidget::eventFilter(obj, event);
}

bool ValueController::MouseButtonDblClickEvent(QEvent* event) {
  QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
  bool result{false};
  if (mouse_event->button() == Qt::LeftButton) {
    value_field_->setReadOnly(false);
    value_field_->setFocus();
    value_field_->setCursor(Qt::IBeamCursor);
    value_field_->selectAll();
    result = true;
  }
  return result;
}

bool ValueController::MouseButtonPressEvent(QEvent* event) {
  QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
  bool result{false};
  if (mouse_event->button() == Qt::LeftButton && value_field_->isReadOnly()) {
    is_dragging_ = true;
    drag_start_pos_ = mouse_event->globalPosition().toPoint();
    drag_start_value_ = current_value_;
    value_field_->setCursor(Qt::SizeHorCursor);

    result = true;
  }
  return result;
}

bool ValueController::MouseMoveEvent(QEvent* event) {
  if (is_dragging_) {
    QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
    QPoint mouse_pos = mouse_event->globalPosition().toPoint();

    int delta_x = mouse_pos.x() - drag_start_pos_.x();
    int new_value = drag_start_value_ + (delta_x / step_speed_) * step_size_;

    SetCurrentValue(new_value);
  }
  return true;
}

bool ValueController::FocusOutEvent() {
  if (!value_field_->isReadOnly()) {
    value_field_->setReadOnly(true);
    value_field_->setCursor(Qt::ArrowCursor);
    EditFinished();
  }
  return false;
}

bool ValueController::MouseButtonReleaseEvent() {
  is_dragging_ = false;
  value_field_->setCursor(Qt::ArrowCursor);
  return true;
}

bool ValueController::KeyPressEvent(QEvent* event) {
  QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
  bool result{false};
  if (key_event->key() == Qt::Key_Escape) {
    value_field_->setReadOnly(true);
    value_field_->setCursor(Qt::ArrowCursor);
    value_field_->clearFocus();
    UpdateValueField();
    result = true;
  } else if (key_event->key() == Qt::Key_Return ||
             key_event->key() == Qt::Key_Enter) {
    EditFinished();
    value_field_->setReadOnly(true);
    value_field_->setCursor(Qt::ArrowCursor);
    result = true;
  }
  return result;
}

void ValueController::EditFinished() {
  bool status;
  int new_value = value_field_->text().toInt(&status);
  if (status) {
    SetCurrentValue(new_value);
  } else {
    UpdateValueField();
  }
  value_field_->deselect();
  this->setFocus();
}

void ValueController::SetCurrentValue(int value) {
  if (current_value_ != value) {
    current_value_ = qBound(min_value_, value, max_value_);
    UpdateValueField();
    emit CurrentValueChanged(current_value_);
  }
}

void ValueController::UpdateValueField() {
  value_field_->setText(QString::number(current_value_));
}

QSize ValueController::GetSize() const {
  return widget_size_;
}

int ValueController::GetWidth() const {
  return widget_size_.width();
}

int ValueController::GetHeight() const {
  return widget_size_.height();
}


} // namespace s21
