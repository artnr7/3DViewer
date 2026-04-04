#ifndef STATUS_BAR_STYLE_H_
#define STATUS_BAR_STYLE_H_

#include <QString>
#include <QColor>
#include <qmargins.h>

namespace s21 {

struct StatusBarStyle {
  /* Colors */
  QString status_text_color = "#A8A6A6";
  QColor error_text_color = QColor(255, 68, 68);

  /* Fonts */
  int text_font_size = 14;
  QString text_font_weight = "bold";
  QString vertices_label = "Vertices";
  QString edges_label = "Edges";
  QString error_label = "Error";

  int default_value = 0;
  int stretch_factor = 1;
  int zero_space = 0;
  int statistics_space = 10;
  QMargins zero_margins = QMargins(0, 0, 0, 0);

  /* Animation */
  int animation_duration = 1200;
  double animation_start_value = 0.4;
  double animation_end_value = 1.0;
  int animation_loop_count = 10;

  /* Numbers formatting */
  int thousands_threshold = 1000;
  int millions_threshold = 1000000;
  int decimal_places = 3;
  QChar decimal_point = '.';
  QChar zero_char = '0';
  int chop_count = 1;

  /* Stack */
  int statistics_page_index = 0;
  int error_page_index = 1;
};

} // namespace s21

#endif // STATUS_BAR_STYLE_H_
