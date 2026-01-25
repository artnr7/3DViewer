#ifndef MENU_WIDGET_HPP_
#define MENU_WIDGET_HPP_

#include "menu_builder/builder_contexts.h"
#include <QWidget>

namespace s21 {

struct MenuWidgetStyle {
  QMargins zero_margins = QMargins(0, 0, 0, 0);
  int zero_spacing = 0;

  /* StatuBar */
  double status_bar_height_ratio = 0.03;
  double tool_bar_height_ratio = 1.0 - status_bar_height_ratio;

  /* ToolBar */
  int edge_margin = 10;
  int buttons_edge_margin_in_panel = 10;
  int item_height = 44;
  double item_width_ratio = 0.3;
};

class MenuWidget : public QWidget {
 public:
  MenuWidget(QWidget *parent = nullptr);
 private:
  void SetupUI();
  void SetupToolBar(IBuilder& builder, int buttons_menu_width, int buttons_menu_height);

  /* Fields */
  MenuWidgetStyle style_;
};

}  // namespace s21

#endif
