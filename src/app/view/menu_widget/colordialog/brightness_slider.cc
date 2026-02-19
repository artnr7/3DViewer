#include "brightness_slider.h"

#include <QMouseEvent>
#include <QPainter>

namespace s21 {

BrightnessSlider::BrightnessSlider(int width, int height, QWidget* parent)
    : QWidget(parent),
      style_{},
      brightness_(style_.brightness_max),
      current_pos_(0),
      bar_width_(width),
      bar_height_(height) {
  setFixedSize(bar_width_, bar_height_);
  CalculateRanges();
  GenerateBrightnessBar();
  UpdatePositionFromBrightness();
}

/* Configure */
void BrightnessSlider::CalculateRanges() {
  line_height_ = (bar_height_ * style_.line_height_percent) / 100;
  line_height_ =
      qMax(style_.min_line_height, qMin(line_height_, style_.max_line_height));

  slider_margin_ = line_height_ / 2;

  slider_min_ = slider_margin_;
  slider_max_ = bar_height_ - slider_margin_ - 1;
  slider_range_ = slider_max_ - slider_min_;
}

void BrightnessSlider::GenerateBrightnessBar() {
  brightness_bar_ = QPixmap(bar_width_, bar_height_);
  brightness_bar_.fill(Qt::transparent);

  QPainter painter(&brightness_bar_);
  painter.setRenderHint(QPainter::Antialiasing);

  QLinearGradient gradient(0, 0, 0, bar_height_);
  gradient.setColorAt(style_.gradient_start_point, style_.gradient_start_color);
  gradient.setColorAt(style_.gradient_start_mid_point,
                      style_.gradient_start_mid_color);
  gradient.setColorAt(style_.gradient_end_mid_point,
                      style_.gradient_end_mid_color);
  gradient.setColorAt(style_.gradient_end_point, style_.gradient_end_color);

  painter.fillRect(0, 0, bar_width_, bar_height_, gradient);

  painter.setPen(QPen(style_.border_color, style_.border_width));
  painter.drawRect(0, 0, bar_width_ - 1, bar_height_ - 1);
}
// Configure

/* Event Handlers */
void BrightnessSlider::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  painter.drawPixmap(0, 0, brightness_bar_);

  int line_half_height = line_height_ / 2;

  QColor border_color = (current_pos_ > bar_height_ / 2)
                            ? style_.border_color_light
                            : style_.border_color_dark;

  painter.setPen(QPen(border_color, style_.slider_border_width));

  painter.drawLine(0, current_pos_ - line_half_height, bar_width_,
                   current_pos_ - line_half_height);

  painter.drawLine(0, current_pos_ + line_half_height, bar_width_,
                   current_pos_ + line_half_height);
  painter.drawLine(0, current_pos_ - line_half_height, 0,
                   current_pos_ + line_half_height);
  painter.drawLine(bar_width_, current_pos_ - line_half_height, bar_width_,
                   current_pos_ + line_half_height);

  painter.setPen(QPen(Qt::red, 1));
  painter.setBrush(Qt::NoBrush);
  painter.drawRect(0, 0, width() - 1, height() - 1);
}

void BrightnessSlider::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    UpdateBrightnessFromPos(event->pos().y());
  }
}

void BrightnessSlider::mouseMoveEvent(QMouseEvent* event) {
  if (event->buttons() & Qt::LeftButton) {
    UpdateBrightnessFromPos(event->pos().y());
  }
}
// Event Handlers

/* Value Update */
void BrightnessSlider::UpdateBrightnessFromPos(int y) {
  y = qBound(slider_min_, y, slider_max_);

  int new_brightness =
      TransformValue(y, slider_min_, slider_max_, style_.brightness_max,
                     style_.brightness_min);

  if (new_brightness != brightness_) {
    brightness_ = new_brightness;
    current_pos_ = y;
    update();
    emit BrightnessChanged(brightness_);
  }
}

void BrightnessSlider::UpdatePositionFromBrightness() {
  current_pos_ =
      TransformValue(brightness_, style_.brightness_min, style_.brightness_max,
                     slider_max_, slider_min_);
  update();
}

int BrightnessSlider::TransformValue(int value, int from_min, int from_max,
                                     int to_min, int to_max) {
  return ((value - from_min) * (to_max - to_min)) / (from_max - from_min) +
         to_min;
}
// Value Update

/* Brightness Managment Mutators*/
void BrightnessSlider::SetBrightness(int brightness) {
  brightness = qBound(style_.brightness_min, brightness, style_.brightness_max);
  if (brightness_ != brightness) {
    brightness_ = brightness;
    UpdatePositionFromBrightness();
  }
}
// Brightness Managment Mutators

}  // namespace s21
