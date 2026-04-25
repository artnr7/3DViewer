#ifndef VALUE_CONTROLLER_STYLE_H_
#define VALUE_CONTROLLER_STYLE_H_

#include <QCursor>
#include <QMargins>
#include <QString>

namespace s21 {

struct ValueControllerStyle {
  const QMargins zero_margins{0, 0, 0, 0};
  const int zero_spacing = 0;

  // Values
  int default_min_value = -100;
  int default_max_value = 100;
  int default_center_value = 0;
  int default_step_size = 1;
  int default_step_speed = 1;
  bool default_dragging = false;

  // Colors
  QString container_background = "#545454";
  QString button_hover_background = "#484848";
  QString button_pressed_background = "#404040";
  QString text_color = "#FFFFFF";
  QString selection_background = "#b0b0b0";
  QString font_weight = "bold";
  QString element_border = "none";

  double button_width_ratio = 0.25;    // 15% от ширины виджета
  double button_font_size_ratio = 0.6; // 60% от высоты виджета
  double value_font_size_ratio = 0.6;  // 60% от высоты виджета
  int container_border_radius = 5;     // px

  QString left_arrow_symbol = "❮";
  QString right_arrow_symbol = "❯";

  QCursor default_cursor = Qt::ArrowCursor;
  QCursor edit_cursor = Qt::IBeamCursor;
  QCursor drag_cursor = Qt::SizeHorCursor;
};

} // namespace s21

#endif // VALUE_CONTROLLER_STYLE_H_
