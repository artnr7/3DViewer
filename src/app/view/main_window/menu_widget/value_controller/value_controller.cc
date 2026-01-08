#include "value_controller.h"

#include <QApplication>
#include <QKeyEvent>
#include <QMouseEvent>

namespace  s21 {

ValueController::ValueController(int width, int height, QWidget* parent)
    : QWidget(parent),
      widget_size_(width, height),
      style_{},
      current_value_(style_.default_min_value),
      min_value_(style_.default_min_value),
      max_value_(style_.default_max_value),
      step_size_(style_.default_step_size),
      step_speed_(style_.default_step_speed),
      is_dragging_(style_.default_dragging) {
  SetupUI();
  SetupConnections();
}

/* Value & Size Management Accessors*/
int ValueController::GetCurrentValue() const { return current_value_; }

int ValueController::GetWidth() const { return widget_size_.width(); }

int ValueController::GetHeight() const { return widget_size_.height(); }

QSize ValueController::GetSize() const { return widget_size_; }
// Value & Size Management Accessors

/* Value Management Mutators */
void ValueController::SetCurrentValue(int value) {
  if (current_value_ != value) {
    current_value_ = qBound(min_value_, value, max_value_);
    UpdateValueField();
    emit CurrentValueChanged(current_value_);
  }
}

void ValueController::SetMinValue(int value) { min_value_ = value; }

void ValueController::SetMaxValue(int value) { max_value_ = value; }
// Value Management Mutators

/* Setup */
void ValueController::SetupUI() {
  setFixedSize(widget_size_);
  setFocusPolicy(Qt::StrongFocus);

  QWidget* container = new QWidget(this);
  container->setFixedSize(widget_size_);
  container->setStyleSheet(CreateContainerStyle());

  int arrow_font_size = widget_size_.height() * style_.button_font_size_ratio;
  int value_font_size = widget_size_.height() * style_.value_font_size_ratio;
  int button_width = widget_size_.width() * style_.button_width_ratio;
  int button_height = widget_size_.height();
  int field_height = widget_size_.height();
  int field_width = widget_size_.width() - 2 * button_width;

  main_layout_ = new QHBoxLayout(container);
  main_layout_->setContentsMargins(style_.zero_margins);
  main_layout_->setSpacing(style_.zero_spacing);
  main_layout_->setAlignment(Qt::AlignCenter);

  left_button_ = new QPushButton(style_.left_arrow_symbol, container);
  left_button_->setFixedSize(button_width, button_height);
  left_button_->setStyleSheet(CreateButtonStyle(
      arrow_font_size, style_.container_border_radius, 0, style_.container_border_radius, 0));

  value_field_ = new QLineEdit(container);
  value_field_->setFixedSize(field_width, field_height);
  value_field_->setAlignment(Qt::AlignCenter);
  value_field_->setStyleSheet(CreateValueFieldStyle(value_font_size));
  value_field_->setCursor(style_.default_cursor);
  value_field_->installEventFilter(this);
  value_field_->setText(QString::number(min_value_));
  value_field_->setReadOnly(true);

  right_button_ = new QPushButton(style_.right_arrow_symbol, container);
  right_button_->setFixedSize(button_width, button_height);
  right_button_->setStyleSheet(CreateButtonStyle(
      arrow_font_size, 0, style_.container_border_radius, 0, style_.container_border_radius));

  main_layout_->addWidget(left_button_);
  main_layout_->addWidget(value_field_);
  main_layout_->addWidget(right_button_);
}

void ValueController::SetupConnections() {
  connect(left_button_, &QPushButton::clicked, this,
          [this]() { SetCurrentValue(current_value_ - step_size_); });

  connect(right_button_, &QPushButton::clicked, this,
          [this]() { SetCurrentValue(current_value_ + step_size_); });
}
// Setup

/* Style Management */
QString ValueController::CreateContainerStyle() const {
  return QString(R"(
    background-color: %1;
    border: none;
    border-radius: %2px;
  )")
      .arg(style_.container_background)
      .arg(style_.container_border_radius);
}

QString ValueController::CreateButtonStyle(int font_size, int radius_tl,
                                           int radius_tr, int radius_bl,
                                           int radius_br) const {
  return QString(R"(
    QPushButton {
      border: %1;
      font-size: %2px;
      font-weight: %3;
      color: %4;
      border-top-left-radius: %5px;
      border-bottom-left-radius: %6px;
      border-top-right-radius: %7px;
      border-bottom-right-radius: %8px;
    }
    QPushButton:hover {
      background-color: %9;
    }
    QPushButton:pressed {
      background-color: %10;
    }
  )")
      .arg(style_.element_border)
      .arg(font_size)
      .arg(style_.font_weight)
      .arg(style_.text_color)
      .arg(radius_tl)
      .arg(radius_bl)
      .arg(radius_tr)
      .arg(radius_br)
      .arg(style_.button_hover_background)
      .arg(style_.button_pressed_background);
}

QString ValueController::CreateValueFieldStyle(int font_size) const {
  return QString(R"(
      QLineEdit {
        border: %1;
        font-size: %2px;
        font-weight: %3;
        color: %4;
        selection-background-color: %5;
      }
    )")
      .arg(style_.element_border)
      .arg(font_size)
      .arg(style_.font_weight)
      .arg(style_.text_color)
      .arg(style_.selection_background);
}
// Style Management

/* Event Handlers */
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
// Event Handlers

/* Internal Helpers */
bool ValueController::MouseButtonDblClickEvent(QEvent* event) {
  QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
  bool result{false};
  if (mouse_event->button() == Qt::LeftButton) {
    value_field_->setReadOnly(false);
    value_field_->setFocus();
    value_field_->setCursor(style_.edit_cursor);
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
    value_field_->setCursor(style_.drag_cursor);

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

bool ValueController::MouseButtonReleaseEvent() {
  is_dragging_ = false;
  value_field_->setCursor(style_.default_cursor);
  return true;
}

bool ValueController::KeyPressEvent(QEvent* event) {
  QKeyEvent* key_event = static_cast<QKeyEvent*>(event);
  bool result = false;
  if (key_event->key() == Qt::Key_Escape) {
    value_field_->setReadOnly(true);
    value_field_->setCursor(style_.default_cursor);
    value_field_->clearFocus();
    UpdateValueField();
    result = true;
  } else if (key_event->key() == Qt::Key_Return ||
             key_event->key() == Qt::Key_Enter) {
    EditFinished();
    value_field_->setReadOnly(true);
    value_field_->setCursor(style_.default_cursor);
    result = true;
  }
  return result;
}

bool ValueController::FocusOutEvent() {
  if (!value_field_->isReadOnly()) {
    value_field_->setReadOnly(true);
    value_field_->setCursor(style_.default_cursor);
    EditFinished();
  }
  return false;
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
// Internal Helpers

/* Value Management Update */
void ValueController::UpdateValueField() {
  value_field_->setText(QString::number(current_value_));
}
// Value Management Update

} // namespace s21
