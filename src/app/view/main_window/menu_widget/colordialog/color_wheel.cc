#include "color_wheel.h"

#include <qcolor.h>
#include <qevent.h>
#include <qpoint.h>

#include <QColor>
#include <QPainter>
#include <QPen>
#include <QPixmap>

namespace  s21 {

ColorWheel::ColorWheel(int size, QWidget* parent)
    : QWidget(parent),
      style_{},
      wheel_size_(size),
      wheel_radius_((size - style_.border_margin) / 2),
      brightness_(style_.max_brightness),
      current_color_(style_.default_color) {
  setFixedSize(wheel_size_, wheel_size_);
  GenerateColorWheel();
  UpdatePositionFromColor(current_color_);
}

/* Color Management */
QColor ColorWheel::CoordToColor(int dx, int dy, int radius,
                                int brightness) const {
  double distance = sqrt(dx * dx + dy * dy);
  if (distance > radius) {
    return QColor();
  }

  double angle = atan2(dy, dx);
  if (angle < 0) {
    angle += style_.full_circle_radians;
  }

  double hue = angle * style_.hue_conversion_factor;
  double saturation = (distance / radius) * style_.saturation_scale;

  return QColor::fromHsv(hue, saturation, brightness);
}

QColor ColorWheel::GetColorAtPosition(const QPoint& pos) const {
  QColor res = QColor();

  QPoint center(wheel_size_ / 2, wheel_size_ / 2);

  int dx = pos.x() - center.x();
  int dy = pos.y() - center.y();

  return CoordToColor(dx, dy, wheel_radius_, brightness_);
}
// Color Management

/* Wheel Management */
void ColorWheel::GenerateColorWheel() {
  if (base_wheel_generated_) {
    ApplyBrightnessToWheel();
    return;
  }

  base_color_wheel_ = QPixmap(wheel_size_, wheel_size_);
  base_color_wheel_.fill(Qt::transparent);

  QPainter painter(&base_color_wheel_);
  painter.setRenderHint(QPainter::Antialiasing, style_.use_antialiasing);

  QPoint center(wheel_size_ / 2, wheel_size_ / 2);
  int color_radius = wheel_radius_ - 1;

  for (int y = 0; y < wheel_size_; ++y) {
    for (int x = 0; x < wheel_size_; ++x) {
      QPoint point(x, y);
      int dx = x - center.x();
      int dy = y - center.y();
      QColor color = CoordToColor(dx, dy, color_radius, style_.max_brightness);
      if (color.isValid()) {
        painter.setPen(color);
        painter.drawPoint(x, y);
      }
    }
  }

  painter.setPen(QPen(style_.wheel_border_color, style_.wheel_border_width));
  painter.setBrush(Qt::NoBrush);
  painter.drawEllipse(center, color_radius, color_radius);

  base_wheel_generated_ = true;

  ApplyBrightnessToWheel();
}

void ColorWheel::ApplyBrightnessToWheel() {
  if (base_color_wheel_.isNull()) {
    return;
  }

  QImage image = base_color_wheel_.toImage();
  double brightness_factor = brightness_ / style_.saturation_scale;

  for (int y = 0; y < image.height(); ++y) {
    for (int x = 0; x < image.width(); ++x) {
      QRgb pixel = image.pixel(x, y);

      QColor color = QColor::fromRgb(pixel);
      if (color.alpha() > 0 && color != style_.wheel_border_color) {
        int r = color.red() * brightness_factor;
        int g = color.green() * brightness_factor;
        int b = color.blue() * brightness_factor;
        color.setRgb(r, g, b);
        image.setPixel(x, y, color.rgb());
      }
    }
  }

  color_wheel_ = QPixmap::fromImage(image);
}
// Wheel Management

/* State Management */
void ColorWheel::UpdatePositionFromColor(const QColor& color) {
  QColor hsvColor = color.toHsv();
  QPoint center(wheel_size_ / 2, wheel_size_ / 2);

  double hue = hsvColor.hueF() * style_.full_circle_radians;
  double saturation = hsvColor.saturationF();

  double radius = saturation * wheel_radius_;
  int x = center.x() + radius * cos(hue);
  int y = center.y() + radius * sin(hue);

  current_pos_.setX(x);
  current_pos_.setY(y);

  update();
}
// State Management

/* Color Management Mutators */
void ColorWheel::SetBrightness(int brightness) {
  brightness =
      qMax(style_.min_brightness, qMin(brightness, style_.max_brightness));
  if (brightness_ != brightness) {
    brightness_ = brightness;

    if (current_color_.isValid()) {
      QColor new_color = current_color_;
      new_color.setHsv(new_color.hue(), new_color.saturation(), brightness_);
      current_color_ = new_color;
      UpdatePositionFromColor(current_color_);
    }

    GenerateColorWheel();

    if (current_color_.isValid()) {
      emit ColorChanged(current_color_);
    }
  }
}

void ColorWheel::SetColor(const QColor& color) {
  if (color.isValid() && current_color_ != color) {
    current_color_ = color;
    brightness_ = color.value();

    GenerateColorWheel();

    UpdatePositionFromColor(color);
  }
}
// Color Management Mutators

/* Event Handlers */
void ColorWheel::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, style_.use_antialiasing);

  painter.drawPixmap(0, 0, color_wheel_);

  QColor border_coolor =
      (current_color_.lightness() > style_.cursor_border_threshold)
          ? style_.cursor_dark_border_color
          : style_.cursor_light_border_color;

  painter.setPen(QPen(border_coolor, style_.cursor_border_width));

  painter.drawEllipse(current_pos_, style_.cursor_radius, style_.cursor_radius);
  painter.drawLine(
      current_pos_.x() - style_.cursor_cross_size, current_pos_.y(),
      current_pos_.x() + style_.cursor_cross_size, current_pos_.y());
  painter.drawLine(
      current_pos_.x(), current_pos_.y() - style_.cursor_cross_size,
      current_pos_.x(), current_pos_.y() + style_.cursor_cross_size);

  painter.setPen(QPen(Qt::red, 1));
  painter.setBrush(Qt::NoBrush);
  painter.drawRect(0, 0, width() - 1, height() - 1);
}

void ColorWheel::MouseEvent(QMouseEvent* event) {
  QPoint pos = event->pos();
  QColor color = GetColorAtPosition(pos);

  if (color.isValid()) {
    current_color_ = color;
    UpdatePositionFromColor(current_color_);
    emit ColorChanged(color);
  }
}

void ColorWheel::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    MouseEvent(event);
  }
}

void ColorWheel::mouseMoveEvent(QMouseEvent* event) {
  if (event->buttons() & Qt::LeftButton) {
    MouseEvent(event);
  }
}
// Event Handlers

} // namespace s21
