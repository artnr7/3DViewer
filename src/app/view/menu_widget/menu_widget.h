#ifndef MENU_WIDGET_HPP_
#define MENU_WIDGET_HPP_

#include "menu_builder/builder_contexts.h"
#include "action_types.h"

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
  Q_OBJECT
 public:
  MenuWidget(int width, int height, QWidget *parent = nullptr);

 signals:
  void ActionTriggered(SceneAction action, ActionData data);

 private:
  void SetupUI();
  void SetupToolBar(IBuilder& builder, int buttons_menu_width, int buttons_menu_height);

  template <typename WidgetType, typename DataType>
  void Bind(WidgetType* widget, SceneAction action, void (WidgetType::*signal)(DataType));

  template <typename Item, typename DataType>
  auto Connect(SceneAction action, void (Item::*signal)(DataType));

  /* Fields */
  MenuWidgetStyle style_;
  int width_;
  int height_;
};

template <typename WidgetType, typename DataType>
void MenuWidget::Bind(WidgetType* widget, SceneAction action, void (WidgetType::*signal)(DataType)) {
  connect(widget, signal, this, [this, action](DataType value) {
    emit ActionTriggered(action, value);
  });
}

template <typename Item, typename DataType>
auto MenuWidget::Connect(SceneAction action, void (Item::*signal)(DataType)) {
  return [this, action, signal](Item* item) {
    this->Bind(item, action, signal);
  };
}

}  // namespace s21

#endif
