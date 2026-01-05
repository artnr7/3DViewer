#ifndef BRIGHTNESS_SLIDER_STYLE_H_
#define BRIGHTNESS_SLIDER_STYLE_H_

#include <QColor>

struct BrightnessSliderStyle {
  // Brightness range configuration
  int brightness_min = 0;
  int brightness_max = 255;

  // Size configuration
  int line_height_percent = 8;  // Percentage of bar height

  // Slider configuration
  int slider_margin_factor = 2;  // Divider for margin calculation

  // Color configuration
  QColor gradient_start_color = Qt::white;
  QColor gradient_start_mid_color = Qt::white;
  QColor gradient_end_mid_color = Qt::black;
  QColor gradient_end_color = Qt::black;
  QColor border_color = Qt::gray;
  QColor border_color_light = Qt::white;
  QColor border_color_dark = Qt::black;

  // Gradient control points
  double gradient_start_point = 0.0;
  double gradient_start_mid_point = 0.1;
  double gradient_end_mid_point = 0.9;
  double gradient_end_point = 1.0;

  // Line thickness configuration
  int border_width = 2;
  int slider_border_width = 3;

  // Size constraints
  int min_line_height = 6;
  int max_line_height = 15;
};

#endif  // BRIGHTNESS_SLIDER_STYLE_H_
