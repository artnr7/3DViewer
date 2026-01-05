#ifndef COLOR_WHEEL_STYLE_H_
#define COLOR_WHEEL_STYLE_H_

#include <QColor>
#include <cmath>

namespace s21 {

struct ColorWheelStyle {
  // Size configuration
  int border_margin = 20;           // Margin from wheel to widget edge

  // Color configuration
  QColor default_color = Qt::white; // Default selected color

  // Wheel appearance
  int wheel_border_width = 2;       // Wheel outline thickness
  QColor wheel_border_color = Qt::black;

  // Cursor (selector) appearance
  int cursor_radius = 5;            // Radius of selection circle
  int cursor_cross_size = 10;       // Size of crosshair lines
  int cursor_border_width = 2;      // Cursor outline thickness
  QColor cursor_dark_border_color = Qt::black;
  QColor cursor_light_border_color = Qt::white;
  int cursor_border_threshold = 128; // Lightness threshold for color selection

  // Brightness adjustment
  int min_brightness = 0;
  int max_brightness = 255;

  // Color calculation constants
  double hue_conversion_factor = 180.0 / M_PI;   // Radians to degrees
  double full_circle_radians = 2 * M_PI;
  double saturation_scale = 255.0;
  int max_saturation = 255;

  bool use_antialiasing = true;
};

} // namespace s21

#endif  // COLOR_WHEEL_STYLE_H_
