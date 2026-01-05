#ifndef COLOR_SELECT_DIALOG_STYLE_H_
#define COLOR_SELECT_DIALOG_STYLE_H_

#include <QString>
#include <QMargins>

struct ColorSelectionDialogStyle {
  QString background_color = "#3D3D3D";
  QString border_color = "#555555";
  int border_width = 2;
  int border_radius = 5;

  int dialog_margin = 5;
  int dialog_spacing = 10;

  const QMargins zero_margins{0, 0, 0, 0};
  const int zero_spacing = 0;

  double wheel_size_percent = 0.9;
  double slider_width_percent = 1.0 - wheel_size_percent;
  double slider_height_percent = wheel_size_percent;

  double close_button_remaining_height_percent = 0.3;
  double rgb_controller_remaining_height_percent = 1.0 - close_button_remaining_height_percent;

  // Close Button
  QString cbutton_text = "X";
  QString cbutton_normal_color = "#FF5555";
  QString cbutton_hover_color = "#FF7777";
  QString cbutton_text_color = "white";
  int cbutton_border_radius = 5;
  int cbutton_font_size = 15;

  // ValueControllers Text
  QString label_text = "RGB VALUES";
  QString label_color = "white";
  int label_font_size = 18;
  QString label_font_weight = "bold";
  double text_height_percent = 0.3;

  // ValueControllers
  int min_rgb_value = 0;
  int max_rgb_value = 255;
  int spacing_between_controllers = 10;
};

#endif  // COLOR_SELECT_DIALOG_STYLE_H_
