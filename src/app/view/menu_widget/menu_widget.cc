#include "menu_widget.h"

#include <qnamespace.h>
#include <qstringview.h>

#include <QDebug>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <type_traits>

#include "action_types.h"
#include "menu_builder/menu_builder.h"
#include "panel/panel.h"
#include "panel/panel_items.h"
#include "status_bar/status_bar.h"

#include "../../utils/logger.h"

namespace s21 {

MenuWidget::MenuWidget(int width, int height, QWidget *parent)
    : QWidget(parent), width_(width), height_(height), style_{} {
  Lg::Log()->Info(std::string(__func__) + " constuctor");
  setFixedSize(width_, height_);
  setContentsMargins(style_.zero_margins);
  SetupUI();
}

void MenuWidget::SetupUI() {
  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setSpacing(style_.zero_spacing);
  main_layout->setContentsMargins(style_.zero_margins);

  const int status_bar_width = width_;
  const int status_bar_height = height_ * style_.status_bar_height_ratio;
  const int tool_bar_width = width_;
  const int tool_bar_height = height_ * style_.tool_bar_height_ratio;

  const int panel_width = tool_bar_width - 2 * style_.edge_margin;
  const int buttons_menu_width =
      panel_width - 2 * style_.buttons_edge_margin_in_panel;

  const int item_width = panel_width * style_.item_width_ratio;
  const int item_height = style_.item_height;

  ToolBar *tool_bar = new ToolBar(tool_bar_width, tool_bar_height);
  StatusBar *status_bar = new StatusBar(status_bar_width, status_bar_height);

  /* TODO: FIX SIGNALS */
  MenuBuilder tool_builder(tool_bar, item_width, item_height);
  SetupToolBar(&tool_builder, buttons_menu_width, item_height);
  SetupStatusBar(status_bar);

  main_layout->addWidget(tool_bar);
  main_layout->addWidget(status_bar);
}

auto MenuWidget::ConnectControllerWithConfig(const MenuWidgetStyle::Config<float>& config, SceneAction action) {
  return [this, config, action](PIValueControllerFloat* controller) {
    controller->Configure(config.current, config.min, config.max, config.step);
    Connect(action, &PIValueControllerFloat::CurrentValueChanged)(controller);
  };
}

void MenuWidget::SetupToolBar(IBuilder *builder, int buttons_menu_width,
                              int buttons_menu_height) {
  SetupTransformPanel(builder);
  SetupShadingPanel(builder);
  SetupButtonsPanel(builder, buttons_menu_width, buttons_menu_height);
}

void MenuWidget::SetupTransformPanel(IBuilder *builder) {
  builder->AddPanel("Transform")
      .AddSubPanel("Translation")
      .Add<PIValueControllerFloat>("x",
          ConnectControllerWithConfig(
            style_.GetTransformConfig(),
            SceneAction::kTranslateX),
          Qt::Vertical)
      .Add<PIValueControllerFloat>("y",
          ConnectControllerWithConfig(
            style_.GetTransformConfig(),
            SceneAction::kTranslateY),
          Qt::Vertical)
      .Add<PIValueControllerFloat>("z",
          ConnectControllerWithConfig(
            style_.GetTransformConfig(),
            SceneAction::kTranslateZ),
          Qt::Vertical)
      .AddSubPanel("Rotation")
      .Add<PIValueControllerFloat>("x",
          ConnectControllerWithConfig(
            style_.GetRotationConfig(),
            SceneAction::kRotateX),
          Qt::Vertical)
      .Add<PIValueControllerFloat>("y",
          ConnectControllerWithConfig(
            style_.GetRotationConfig(),
            SceneAction::kRotateY),
          Qt::Vertical)
      .Add<PIValueControllerFloat>("z",
          ConnectControllerWithConfig(
            style_.GetRotationConfig(),
            SceneAction::kRotateZ),
          Qt::Vertical)
      .AddSubPanel("Scale")
      .Add<PIValueControllerFloat>(
          "value",
          ConnectControllerWithConfig(
            style_.GetScaleConfig(),
            SceneAction::kScale),
          Qt::Horizontal);
}

/* TODO: Add new icon for empty-vertex */
void MenuWidget::SetupShadingPanel(IBuilder *builder) {
  builder->AddPanel("Shading")
      .AddSubPanel("Vertices")
      .Add<PIValueControllerFloat>(
        "size",
        ConnectControllerWithConfig(
          style_.GetThicknessSizeConfig(),
          SceneAction::kVertexSize),
        Qt::Vertical)
      .Add<PIComboBox>("style",
                       GetComboBoxConnection<VertexStyle>(
                           SceneAction::kVertexStyle,
                           {{"assets/icons/circle_empty.png",
                             static_cast<int>(VertexStyle::kEmpty)},
                            {"assets/icons/circle.png",
                             static_cast<int>(VertexStyle::kCircle)},
                             {"assets/icons/square.png",
                             static_cast<int>(VertexStyle::kSquare)}}),
                       Qt::Vertical)
      .Add<PIColorPicker>(
          "color",
          Connect(SceneAction::kVertexColor, &PIColorPicker::ColorChanged),
          Qt::Vertical)
      .AddSubPanel("Edges")
      .Add<PIValueControllerFloat>(
        "thickness",
        ConnectControllerWithConfig(
          style_.GetThicknessSizeConfig(),
          SceneAction::kEdgeThickness),
        Qt::Vertical)
      .Add<PIComboBox>(
          "style",
          GetComboBoxConnection<EdgeStyle>(
              SceneAction::kEdgeStyle,
              {{"assets/icons/line.png", static_cast<int>(EdgeStyle::kLine)},
               {"assets/icons/line_dash.png",
                static_cast<int>(EdgeStyle::kDashLine)}}),
          Qt::Vertical)
      .Add<PIColorPicker>(
          "color",
          Connect(SceneAction::kEdgeColor, &PIColorPicker::ColorChanged),
          Qt::Vertical)
      .AddSubPanel("Background")
      .Add<PIColorPicker>(
          "color",
          Connect(SceneAction::kBackgroundColor, &PIColorPicker::ColorChanged),
          Qt::Horizontal);
}

void MenuWidget::SetupButtonsPanel(IBuilder *builder, int buttons_menu_width,
                                   int buttons_menu_height) {
  builder->AddPanel("Projection")
      .AddSubPanel("")
      .SetSize(buttons_menu_width, buttons_menu_height)
      .Add<PIDoubleButton>(
          "",
          ConnectEnum<ProjectionType>(SceneAction::kProjection,
                                      &PIDoubleButton::ButtonToggled),
          "perspective", "ortography", true)
      .AddPanel("Render")
      .AddSubPanel("")
      .SetSize(buttons_menu_width, buttons_menu_height)
      .Add<PIDoubleButton>(
          "",
          ConnectEnum<RenderType>(SceneAction::kRender,
                                  &PIDoubleButton::ButtonClicked),
          "GIF", "Image", false)
      .AddPanel("Files")
      .AddSubPanel("")
      .SetSize(buttons_menu_width, buttons_menu_height)
      .Add<PIFileManagement>(
          "", Connect(SceneAction::kOpenFile, &PIFileManagement::FileSelected),
          "Open", "File name:");
}

void MenuWidget::SetupStatusBar(StatusBar *status_bar) {
  connect(this, &MenuWidget::UpdateInfo, status_bar, &StatusBar::OnUpdateInfo);
  connect(this, &MenuWidget::ShowError, status_bar, &StatusBar::OnShowError);
}
void MenuWidget::OnUpdateObjectInfo() {}

// void MenuWidget::OnUpdateObjectInfo(ModelUpdateData data) {
//   std::visit(
//       [this](auto&& arg) {
//         using T = std::decay_t<decltype(arg)>;
//
//         if constexpr (std::is_same_v<T, ObjectInfo>) {
//           emit UpdateInfo(arg.vertices, arg.edges);
//         } else if constexpr (std::is_same_v<T, QString>) {
//           emit ShowError(arg);
//         }
//       },
//       data);
// }

} // namespace s21
