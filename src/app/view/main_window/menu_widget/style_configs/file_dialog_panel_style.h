#ifndef FILE_DIALOG_PANEL_STYLE_H_
#define FILE_DIALOG_PANEL_STYLE_H_

#include <QString>
#include <QMargins>

namespace s21 {

struct FileDialogPanelStyle {
  // Colors
  QString background_color = "#202020";
  QString border_color = "#606060";
  QString text_color = "white";
  QString hover_color = "#3A3A3A";

  QString default_file_name_label_text = "No file selected";

  // Sizes
  double text_container_width_percent = 0.4;
  double button_width_percent = (1.0 - text_container_width_percent) / 2.0;
  double label_width_percent = button_width_percent;

  int border_radius = 5;
  int text_padding = 5;
  int label_margin = 5;

  int text_container_border_size = 1;

  QMargins zero_margins{0, 0, 0, 0};
  int zero_spacing = 0;

  // Fonts
  int label_font_size = 15;
  int file_name_font_size = 12;

  // Tooltip
  QString tooltip_background = "#2C2B2B";
  QString tooltip_border_color = "#606060";
  int tooltip_border_size = 1;
  int tooltip_border_radius = 3;
  int tooltip_padding = 5;
  int tooltip_font_size = 12;

  // Animation copying
  int copy_message_duration = 2000;
  QString copy_message_text = "Copied :)";

  // Container margins
  int container_left_margin = 5;
  int container_right_margin = container_left_margin;
};

} // namespace s21

#endif // FILE_DIALOG_PANEL_STYLE_H_
