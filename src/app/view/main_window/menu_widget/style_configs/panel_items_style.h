#ifndef PANEL_ITEMS_STYLE_H_
#define PANEL_ITEMS_STYLE_H_

#include <QMargins>
#include <QString>

struct PanelItemStyle {
  const QMargins zero_margins{0, 0, 0, 0};
  const int zero_spacing = 0;

  QString border = "none";
  QString text_color = "#FFFFFF";
  QString font_weight = "bold";

  double controller_hight_ratio = 0.65;
  double label_hight_ratio = 1.0 - controller_hight_ratio;
  double font_size_ratio = label_hight_ratio - 0.1;
  int default_font_size = 10;
};

#endif // PANEL_ITEMS_STYLE_H_
