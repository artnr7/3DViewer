#ifndef COLOR_PICKER_STYLE_H_
#define COLOR_PICKER_STYLE_H_

#include <QColor>

namespace s21 {

struct ColorPickerStyle {
  int outer_border_radius = 8;
  int inner_border_radius = 5;
  int border_thickness = 3;
  QColor outer_border_color = QColor("#545454");
  int dialog_offset_y = 10;
  QColor default_color = Qt::white;

  // ColorSelectionDialog
  int color_selection_dialog_width = 320;
  int color_selection_dialog_height = 450;
};

} // namespace s21

#endif  // COLOR_PICKER_STYLE_H_
