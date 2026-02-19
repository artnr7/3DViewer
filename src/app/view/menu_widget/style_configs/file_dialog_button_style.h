#ifndef FILE_DIALOG_BUTTON_STYLE_H_
#define FILE_DIALOG_BUTTON_STYLE_H_

#include <QString>

namespace s21 {

struct FileDialogStyle {
  QString background_color = "#2C2B2B";
  QString text_color = "#FFFFFF";
  QString widget_background = "#3D3D3D";
  QString border_color = "#555555";
  QString selection_color = "#555555";
  QString hover_color = "#4A4A4A";

  int border_radius = 4;
  int button_border_radius = 5;
  int padding = 5;
  int button_padding_vertical = 8;
  int button_padding_horizontal = 16;
  int min_button_width = 80;
  int text_border_size = 1;

  QString filter = "OBJ Files (*.obj)";
  QString dialog_title = "Select OBJ File";
};

struct FileDialogButtonStyle {
  QString background_color = "#5A5A5A";
  QString hover_color = "#484848";
  QString pressed_color = "#404040";
  QString border_color = "#7A7A7A";
  QString hover_border_color = "#6A6A6A";
  QString text_color = "white";
  int font_size = 12;
  int border_radius = 5;
  int text_border_size = 1;
};

} // namespace s21

#endif // FILE_DIALOG_BUTTON_STYLE_H_