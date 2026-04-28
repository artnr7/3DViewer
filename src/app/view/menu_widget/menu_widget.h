#ifndef MENU_WIDGET_HPP_
#define MENU_WIDGET_HPP_

#include <QWidget>
#include <iostream>
#include <string>
#include <type_traits>

#include "action_types.h"
#include "menu_builder/builder_contexts.h"
#include "menu_builder/status_bar_builder.h"
#include "panel/panel_items.h"

namespace s21 {

struct MenuWidgetStyle {
  QMargins zero_margins = QMargins(0, 0, 0, 0);
  int zero_spacing = 0;

  /* StatusInfo */
  double status_info_width_ratio = 0.9;
  double trash_button_width_ratio = 1.0 - status_info_width_ratio;
  int trash_button_height_padding = 4;

  /* StatuBar */
  double status_bar_height_ratio = 0.04;
  double tool_bar_height_ratio = 1.0 - status_bar_height_ratio;

  /* ToolBar */
  int edge_margin = 10;
  int buttons_edge_margin_in_panel = 10;
  int item_height = 44;
  double item_width_ratio = 0.3;

  // Transform values
  float trnsfrm_min_value = -3.0f;
  float trnsfrmmax_value = 3.0f;
  float trnsfrm_center_value = 0.0f;
  float trnsfrm_step_size = 0.001f;

  // Rotate values
  float rot_cur_val = 0.0f;
  float rot_step_size = 0.05f;
  float rot_min_val = -1080.0f;
  float rot_max_val = 1080.0f;

  // Scale values
  float scale_cur_val = 1.0f;
  float scale_step_size = 0.01f;
  float scale_min_val = 0.01f;
  float scale_max_val = 10.0f;

  // Thickness & Size values
  float thick_size_cur_val = 1.0f;
  float thick_size_step_size = 0.05f;
  float thick_size_min_val = 0.01f;
  float thick_size_max_val = 50.0f;

  template <typename T>
  struct Config {
    T current, min, max, step;
  };

  Config<float> GetTransformConfig() const {
    return {trnsfrm_center_value, trnsfrm_min_value,
            trnsfrmmax_value, trnsfrm_step_size};
  }

  Config<float> GetRotationConfig() const {
    return {rot_cur_val, rot_min_val, rot_max_val, rot_step_size};
  }

  Config<float> GetScaleConfig() const {
    return {scale_cur_val, scale_min_val, scale_max_val, scale_step_size};
  }

  Config<float> GetThicknessSizeConfig() const {
    return {thick_size_cur_val, thick_size_min_val,
            thick_size_max_val, thick_size_step_size};
  }
};

class MenuWidget : public QWidget {
  Q_OBJECT
public:
  MenuWidget(int width, int height, QWidget *parent = nullptr);

public slots:
  void OnActionTriggered(SceneAction action, ActionData data);

signals:
  void ActionTriggered(SceneAction action, ActionData data);

  void SetIntValue(SceneAction action, int value);
  void SetFloatValue(SceneAction action, float value);
  void SetColorValue(SceneAction action, const QColor& color);
  void SetButtonSide(SceneAction action, ButtonSide side);
  void SetFilenameValue(SceneAction action, const QString& filename);
  void SetStatusInfoValue(int vertices, int edges);
  void SetStatusErrorValue(const QString& msg);

private:
  void SetupUI();
  void SetupToolBar(IBuilder *builder, int buttons_menu_width,
                    int buttons_menu_height);
  void SetupStatusBar(StatusBarBuilder *builder, int status_bar_height, int status_bar_width);
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

  auto ConnectControllerWithConfig(const MenuWidgetStyle::Config<float>& config, SceneAction action);
  auto ConnectColorPicker(SceneAction action);

  template <typename EnumType>
  auto ConnectComboBox(SceneAction action, std::initializer_list<std::pair<QString, int>> items);

  template <typename EnumType, typename Item, typename DataType>
  auto ConnectEnum(SceneAction action, void (Item::*signal)(DataType));

  template <typename EnumType>
  auto ConnectDoubleButton(SceneAction action);
  auto ConnectFileManagement(SceneAction action);
  auto ConnectStatusInfo();

  void SetValueForControllers(SceneAction action, const ActionData& data);

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
auto MenuWidget::ConnectDoubleButton(SceneAction action) {
  return [this, action](PIDoubleButton* button) {
    connect(this, &MenuWidget::SetButtonSide,
            button, [button, action](SceneAction target, ButtonSide side) {
      if (target == action) {
        button->SetButtonSide(side);
      }
    });
    ConnectEnum<EnumType>(action, &PIDoubleButton::ButtonToggled)(button);
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

template <typename EnumType>
auto MenuWidget::ConnectComboBox(SceneAction action, std::initializer_list<std::pair<QString, int>> items) {
  return [this, action, items](PIComboBox* combo) {
    connect(this, &MenuWidget::SetIntValue,
            combo, [combo, action](SceneAction target, int index) {
      if (target == action) {
        combo->SetCurrentIndex(index);
      }
    });
    GetComboBoxConnection<EnumType>(action, items)(combo);
  };
}

} // namespace s21

#endif
