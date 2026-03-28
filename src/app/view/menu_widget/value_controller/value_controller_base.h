#ifndef VALUE_CONTROLLER_BASE_H_
#define VALUE_CONTROLLER_BASE_H_

#include <QEvent>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPushButton>
#include <QWidget>

#include <concepts>

#include "style_configs/value_controller_style.h"

namespace s21 {

template <typename T>
concept Numeric = std::is_arithmetic_v<T>;

template <Numeric T = float>
class ValueControllerBase : public QWidget {

public:
  explicit ValueControllerBase(int width = 100, int height = 40,
                               QWidget *parent = nullptr);

  /* Value & Size Management Accessors */
  T GetCurrentValue() const;
  int GetWidth() const;
  int GetHeight() const;
  QSize GetSize() const;

  /* Value Management Mutators */
  void SetCurrentValue(T value);
  void SetMinValue(T value);
  void SetMaxValue(T value);
  void SetStepSize(T step_size);

protected:
  /* Callback for sending a signal (redefined in the heirs) */
  virtual void OnValueChanged(T value);

private:
  /* Setup */
  void SetupUI();
  void SetupConnections();

  /* Style Management */
  QString CreateContainerStyle() const;
  QString CreateButtonStyle(int font_size, int radius_tl, int radius_tr,
                            int radius_bl, int radius_br) const;
  QString CreateValueFieldStyle(int font_size) const;

protected:
  /* Event Handlers */
  bool eventFilter(QObject *obj, QEvent *event) override;

private:
  /* Internal Helpers */
  bool MouseButtonDblClickEvent(QEvent *event);
  bool MouseButtonPressEvent(QEvent *event);
  bool MouseMoveEvent(QEvent *event);
  bool MouseButtonReleaseEvent();
  bool KeyPressEvent(QEvent *event);
  bool FocusOutEvent();
  void EditFinished();

 protected:
  /* Value Management Update */
  virtual void UpdateValueField();

  /* Fields */
 private:
  ValueControllerStyle style_;
  QSize widget_size_;
  T min_value_;
  T max_value_;
  T step_size_;
  T step_speed_;

  bool is_dragging_;
  QPoint drag_start_pos_;
  T drag_start_value_;

  QHBoxLayout *main_layout_;
  QPushButton *left_button_;
  QPushButton *right_button_;

 protected:
  T current_value_;
  QLineEdit *value_field_;
};

template <Numeric T>
ValueControllerBase<T>::ValueControllerBase(int width, int height, QWidget *parent)
    : QWidget(parent), style_{}, widget_size_(width, height),
      min_value_(style_.default_min_value),
      max_value_(style_.default_max_value),
      step_size_(style_.default_step_size),
      step_speed_(style_.default_step_speed),
      is_dragging_(style_.default_dragging),
      current_value_(style_.default_center_value) {
  SetupUI();
  SetupConnections();
  value_field_->setText(QString::number(current_value_));
}

/* Value & Size Management Accessors */
template <Numeric T>
T ValueControllerBase<T>::GetCurrentValue() const {
  return current_value_;
}

template <Numeric T>
int ValueControllerBase<T>::GetWidth() const {
  return widget_size_.width();
}

template <Numeric T>
int ValueControllerBase<T>::GetHeight() const {
  return widget_size_.height();
}

template <Numeric T>
QSize ValueControllerBase<T>::GetSize() const {
  return widget_size_;
}
// Value & Size Management Accessors

/* Value Management Mutators */
template <Numeric T>
void ValueControllerBase<T>::SetCurrentValue(T value) {
  if (current_value_ != value) {
    current_value_ = qBound(min_value_, value, max_value_);
    UpdateValueField();
    OnValueChanged(current_value_);
  }
}

template <Numeric T>
void ValueControllerBase<T>::SetMinValue(T value) {
  min_value_ = value;
}

template <Numeric T>
void ValueControllerBase<T>::SetMaxValue(T value) {
  max_value_ = value;
}

template <Numeric T>
void ValueControllerBase<T>::SetStepSize(T step_size) {
  step_size_ = step_size;
}
// Value Management Mutators

/* Setup */
template <Numeric T>
void ValueControllerBase<T>::SetupUI() {
  setFixedSize(widget_size_);
  setFocusPolicy(Qt::StrongFocus);

  QWidget *container = new QWidget(this);
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
  left_button_->setStyleSheet(
      CreateButtonStyle(arrow_font_size, style_.container_border_radius, 0,
                        style_.container_border_radius, 0));

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
  right_button_->setStyleSheet(
      CreateButtonStyle(arrow_font_size, 0, style_.container_border_radius, 0,
                        style_.container_border_radius));

  main_layout_->addWidget(left_button_);
  main_layout_->addWidget(value_field_);
  main_layout_->addWidget(right_button_);
}

template <Numeric T>
void ValueControllerBase<T>::SetupConnections() {
  connect(left_button_, &QPushButton::clicked, this,
          [this]() { SetCurrentValue(current_value_ - step_size_); });

  connect(right_button_, &QPushButton::clicked, this,
          [this]() { SetCurrentValue(current_value_ + step_size_); });
}
// Setup

/* Style Management */
template <Numeric T>
QString ValueControllerBase<T>::CreateContainerStyle() const {
  return QString(R"(
    background-color: %1;
    border: none;
    border-radius: %2px;
  )")
      .arg(style_.container_background)
      .arg(style_.container_border_radius);
}

template <Numeric T>
QString ValueControllerBase<T>::CreateButtonStyle(int font_size, int radius_tl,
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

template <Numeric T>
QString ValueControllerBase<T>::CreateValueFieldStyle(int font_size) const {
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
template <Numeric T>
bool ValueControllerBase<T>::eventFilter(QObject *obj, QEvent *event) {
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
template <Numeric T>
bool ValueControllerBase<T>::MouseButtonDblClickEvent(QEvent *event) {
  QMouseEvent *mouse_event = static_cast<QMouseEvent *>(event);
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

template <Numeric T>
bool ValueControllerBase<T>::MouseButtonPressEvent(QEvent *event) {
  QMouseEvent *mouse_event = static_cast<QMouseEvent *>(event);
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

template <Numeric T>
bool ValueControllerBase<T>::MouseMoveEvent(QEvent *event) {
  if (is_dragging_) {
    QMouseEvent *mouse_event = static_cast<QMouseEvent *>(event);
    QPoint mouse_pos = mouse_event->globalPosition().toPoint();

    int delta_x = mouse_pos.x() - drag_start_pos_.x();
    T new_value = drag_start_value_ + (delta_x / step_speed_) * step_size_;

    SetCurrentValue(new_value);
  }
  return true;
}

template <Numeric T>
bool ValueControllerBase<T>::MouseButtonReleaseEvent() {
  is_dragging_ = false;
  value_field_->setCursor(style_.default_cursor);
  return true;
}

template <Numeric T>
bool ValueControllerBase<T>::KeyPressEvent(QEvent *event) {
  QKeyEvent *key_event = static_cast<QKeyEvent *>(event);
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

template <Numeric T>
bool ValueControllerBase<T>::FocusOutEvent() {
  if (!value_field_->isReadOnly()) {
    value_field_->setReadOnly(true);
    value_field_->setCursor(style_.default_cursor);
    EditFinished();
  }
  return false;
}

template <Numeric T>
void ValueControllerBase<T>::EditFinished() {
  bool status;
  T new_value;
  if constexpr (std::is_integral_v<T>) {
    new_value = value_field_->text().toInt(&status);
  } else {
    new_value = value_field_->text().toFloat(&status);
  }
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
template <Numeric T>
void ValueControllerBase<T>::UpdateValueField() {
  value_field_->setText(QString::number(current_value_));
}
// Value Management Update

template <Numeric T>
void ValueControllerBase<T>::OnValueChanged(T /*value*/) {
  // Переопределяется в наследниках для отправки сигнала
}

} // namespace s21

#endif // VALUE_CONTROLLER_BASE_H_
