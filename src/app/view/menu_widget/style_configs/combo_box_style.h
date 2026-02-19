#ifndef COMBOX_STYLE_H_
#define COMBOX_STYLE_H_

#include <QColor>
#include <QEasingCurve>

namespace s21 {

struct ComboBoxStyle {
  // Corner radii
  int border_radius = 10;

  // Dimension scaling factors
  double icon_scale_factor = 0.6;      // Relative to widget height
  double arrow_scale_factor = 0.6;     // Relative to arrow area size
  double current_icon_max_scale = 0.5; // Maximum icon size (50%)

  // Animation settings
  int animation_duration_ms = 200;     // Animation duration
  QEasingCurve::Type easing_curve = QEasingCurve::OutCubic;

  // Additional settings
  int minimum_arrow_area_width = 40;   // Minimum arrow area width
  int item_margin = 0;                 // Spacing between items

  int border_width = 1;
  int border_correction = border_width;

  // Color scheme substructure
  struct Color {
    QColor background = QColor("#3D3D3D");
    QColor border = QColor("#555555");
    QColor hover = QColor("#353535");
    QColor selected = QColor("#4D4D4D");
  } colors;

  // Delegate
  int default_item_border = 1;
  double hotizontal_thresold = 1.0;
};

} // namespace s21

#endif  // COMBOX_STYLE_H_