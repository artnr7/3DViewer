#ifndef MENU_WIDGET_HPP_
#define MENU_WIDGET_HPP_

#include <QWidget>
#include <iostream>
#include <string>

#include "action_types.h"
#include "menu_builder/builder_contexts.h"
// #include "model_types.h"

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

public slots:
  // void OnUpdateObjectInfo(ModelUpdateData data);

signals:
  void ActionTriggered(SceneAction action, ActionData data);
  void FilenameSet( const std::string &filename);

private:
signals:
  void UpdateInfo(int vertices_count, int edges_count);
  void ShowError(const QString &msg);

private:
  void SetupUI();
  void SetupToolBar(IBuilder *builder, int buttons_menu_width,
                    int buttons_menu_height);
  void SetupStatusBar(StatusBar *status_bar);
  void SetupTransformPanel(IBuilder *builder);
  void SetupShadingPanel(IBuilder *builder);
  void SetupButtonsPanel(IBuilder *builder, int buttons_menu_width,
                         int buttons_menu_height);

  template <typename EnumType>
  auto
  GetComboBoxConnection(SceneAction action,
                        std::initializer_list<std::pair<QString, int>> items);

  template <typename Item, typename DataType>
  auto Connect(SceneAction action, void (Item::*signal)(DataType));

  template <typename EnumType, typename Item, typename DataType>
  auto ConnectEnum(SceneAction action, void (Item::*signal)(DataType));

  /* Fields */
  MenuWidgetStyle style_;
  int width_;
  int height_;
};

template <typename Item, typename DataType>
auto MenuWidget::Connect(SceneAction action, void (Item::*signal)(DataType)) {
  return [this, action, signal](Item *item) {
    connect(item, signal, this, [this, action](DataType value) {
      emit ActionTriggered(action, value);
    });
  };
}

template <typename EnumType, typename Item, typename DataType>
auto MenuWidget::ConnectEnum(SceneAction action,
                             void (Item::*signal)(DataType)) {
  return [this, action, signal](Item *item) {
    connect(item, signal, this, [this, action](DataType value) {
      emit ActionTriggered(action, static_cast<EnumType>(value));
    });
  };
}

template <typename EnumType>
auto MenuWidget::GetComboBoxConnection(
    SceneAction action, std::initializer_list<std::pair<QString, int>> items) {
  return [this, action, items](PIComboBox *combo) {
    this->ConnectEnum<EnumType>(action,
                                &PIComboBox::CurrentIndexChanged)(combo);
    combo->SetArrows("assets/icons/open_arrow.png",
                     "assets/icons/close_arrow.png");
    combo->AddItems(items);
  };
}

} // namespace s21

#endif
