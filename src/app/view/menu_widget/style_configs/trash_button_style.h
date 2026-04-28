#ifndef TRASH_BUTTON_STYLE_H_
#define TRASH_BUTTON_STYLE_H_

#include <QString>

struct TrashButtonStyle {
  QString background_color = "#5A5A5A";
  QString hover_color = "#484848";
  QString pressed_color = "#404040";
  int border_radius = 5;
  int padding = 10;

  /* Tooltip styles */
  QString tooltip_background = "#3A3A3A";
  QString tooltip_border_color = "#6A6A6A";
  int tooltip_border_size = 1;
  int tooltip_border_radius = 5;
  int tooltip_padding = 3;
  int tooltip_font_size = 12;
  QString tooltip_text_color = "white";
  QString tooltip_text = "Clear menu config";
};

#endif  // TRASH_BUTTON_STYLE_H_
