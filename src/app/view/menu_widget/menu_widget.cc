#include "menu_widget.h"

#include <QDebug>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <type_traits>

#include "../../utils/logger.h"
#include "action_types.h"
#include "buttons/trash_button.h"
#include "menu_builder/menu_builder.h"
#include "panel/panel.h"
#include "panel/panel_items.h"
#include "status_info/status_info.h"

namespace s21 {

MenuWidget::MenuWidget(int width, int height, QWidget* parent)
    : QWidget(parent), width_(width), height_(height), style_{} {
  Lg::Log()->Info(std::string(__func__) + " constuctor");
  setFixedSize(width_, height_);
  setContentsMargins(style_.zero_margins);
  SetupUI();
}

void MenuWidget::SetupUI() {
  QVBoxLayout* main_layout = new QVBoxLayout(this);
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

  ToolBar* tool_bar = new ToolBar(tool_bar_width, tool_bar_height);
  StatusBar* status_bar = new StatusBar(status_bar_width, status_bar_height);

  /* TODO: FIX SIGNALS */
  MenuBuilder tool_builder(tool_bar, item_width, item_height);
  SetupToolBar(&tool_builder, buttons_menu_width, item_height);

  StatusBarBuilder status_builder(status_bar);
  SetupStatusBar(&status_builder, status_bar_width, status_bar_height);

  main_layout->addWidget(tool_bar);
  main_layout->addWidget(status_bar);
}

auto MenuWidget::ConnectControllerWithConfig(
    const MenuWidgetStyle::Config<float>& config, SceneAction action) {
  return [this, config, action](PIValueControllerFloat* controller) {
    controller->Configure(config.current, config.min, config.max, config.step);

    connect(this, &MenuWidget::SetFloatValue, controller,
            [controller, action](SceneAction target, float val) {
              if (target == action) {
                controller->SetCurrentValue(val);
              }
            });

    Connect(action, &PIValueControllerFloat::CurrentValueChanged)(controller);
  };
}

auto MenuWidget::ConnectColorPicker(SceneAction action) {
  return [this, action](PIColorPicker* picker) {
    connect(this, &MenuWidget::SetColorValue, picker,
            [picker, action](SceneAction target, const QColor& color) {
              if (target == action) {
                picker->SetColor(color);
              }
            });
    Connect(action, &PIColorPicker::ColorChanged)(picker);
  };
}

auto MenuWidget::ConnectFileManagement(SceneAction action) {
  return [this, action](PIFileManagement* file_mgmt) {
    connect(this, &MenuWidget::SetFilenameValue, file_mgmt,
            [file_mgmt, action](SceneAction target, const QString& filename) {
              if (target == action) {
                file_mgmt->SetFilename(filename);
              }
            });
    Connect(action, &PIFileManagement::FileSelected)(file_mgmt);
  };
}

auto MenuWidget::ConnectStatusInfo() {
  return [this](StatusInfo* info) {
    connect(this, &MenuWidget::SetStatusInfoValue, info,
            &StatusInfo::OnUpdateInfo);
    connect(this, &MenuWidget::SetStatusErrorValue, info,
            &StatusInfo::OnShowError);
  };
}

void MenuWidget::OnActionTriggered(SceneAction action, ActionData data) {
  std::visit(
      [this, action](auto&& value) {
        using T = std::decay_t<decltype(value)>;

        if constexpr (std::is_same_v<T, float>) {
          // std::fprintf(stderr, "hello");

          emit SetFloatValue(action, value);
        } else if constexpr (std::is_same_v<T, QColor>) {
          emit SetColorValue(action, value);
        } else if constexpr (std::is_same_v<T, int>) {
          emit SetIntValue(action, value);
        } else if constexpr (std::is_same_v<T, VertexStyle>) {
          emit SetIntValue(action, static_cast<int>(value));
        } else if constexpr (std::is_same_v<T, EdgeStyle>) {
          emit SetIntValue(action, static_cast<int>(value));
        } else if constexpr (std::is_same_v<T, ProjectionType>) {
          emit SetButtonSide(action, value == ProjectionType::kPerspective
                                         ? ButtonSide::kLeft
                                         : ButtonSide::kRight);
        } else if constexpr (std::is_same_v<T, QString>) {
          if (action == SceneAction::kShowError) {
            emit SetStatusErrorValue(value);
          } else {
            emit SetFilenameValue(action, value);
          }
        } else if constexpr (std::is_same_v<T, std::pair<int, int>>) {
          emit SetStatusInfoValue(value.first, value.second);
        } else if constexpr (std::is_same_v<T, std::monostate>) {
          // For config clean
        }
      },
      data);
}

void MenuWidget::SetupToolBar(IBuilder* builder, int buttons_menu_width,
                              int buttons_menu_height) {
  SetupTransformPanel(builder);
  SetupShadingPanel(builder);
  SetupButtonsPanel(builder, buttons_menu_width, buttons_menu_height);
}

void MenuWidget::SetupTransformPanel(IBuilder* builder) {
  builder->AddPanel("Transform")
      .AddSubPanel("Translation")
      .Add<PIValueControllerFloat>(
          "x",
          ConnectControllerWithConfig(style_.GetTransformConfig(),
                                      SceneAction::kTranslateX),
          Qt::Vertical)
      .Add<PIValueControllerFloat>(
          "y",
          ConnectControllerWithConfig(style_.GetTransformConfig(),
                                      SceneAction::kTranslateY),
          Qt::Vertical)
      .Add<PIValueControllerFloat>(
          "z",
          ConnectControllerWithConfig(style_.GetTransformConfig(),
                                      SceneAction::kTranslateZ),
          Qt::Vertical)
      .AddSubPanel("Rotation")
      .Add<PIValueControllerFloat>(
          "x",
          ConnectControllerWithConfig(style_.GetRotationConfig(),
                                      SceneAction::kRotateX),
          Qt::Vertical)
      .Add<PIValueControllerFloat>(
          "y",
          ConnectControllerWithConfig(style_.GetRotationConfig(),
                                      SceneAction::kRotateY),
          Qt::Vertical)
      .Add<PIValueControllerFloat>(
          "z",
          ConnectControllerWithConfig(style_.GetRotationConfig(),
                                      SceneAction::kRotateZ),
          Qt::Vertical)
      .AddSubPanel("Scale")
      .Add<PIValueControllerFloat>(
          "value",
          ConnectControllerWithConfig(style_.GetScaleConfig(),
                                      SceneAction::kScale),
          Qt::Horizontal);
}

void MenuWidget::SetupShadingPanel(IBuilder* builder) {
  builder->AddPanel("Shading")
      .AddSubPanel("Vertices")
      .Add<PIValueControllerFloat>(
          "size",
          ConnectControllerWithConfig(style_.GetThicknessSizeConfig(),
                                      SceneAction::kVertexSize),
          Qt::Vertical)
      .Add<PIComboBox>("style",
                       ConnectComboBox<VertexStyle>(
                           SceneAction::kVertexStyle,
                           {{"assets/icons/circle_empty.png",
                             static_cast<int>(VertexStyle::kEmpty)},
                            {"assets/icons/circle.png",
                             static_cast<int>(VertexStyle::kCircle)},
                            {"assets/icons/square.png",
                             static_cast<int>(VertexStyle::kSquare)}}),
                       Qt::Vertical)
      .Add<PIColorPicker>(
          "color", ConnectColorPicker(SceneAction::kVertexColor), Qt::Vertical)
      .AddSubPanel("Edges")
      .Add<PIValueControllerFloat>(
          "thickness",
          ConnectControllerWithConfig(style_.GetThicknessSizeConfig(),
                                      SceneAction::kEdgeThickness),
          Qt::Vertical)
      .Add<PIComboBox>(
          "style",
          ConnectComboBox<EdgeStyle>(
              SceneAction::kEdgeStyle,
              {{"assets/icons/line.png", static_cast<int>(EdgeStyle::kLine)},
               {"assets/icons/line_dash.png",
                static_cast<int>(EdgeStyle::kDashLine)}}),
          Qt::Vertical)
      .Add<PIColorPicker>("color", ConnectColorPicker(SceneAction::kEdgeColor),
                          Qt::Vertical)
      .AddSubPanel("Background")
      .Add<PIColorPicker>("color",
                          ConnectColorPicker(SceneAction::kBackgroundColor),
                          Qt::Horizontal);
}

void MenuWidget::SetupButtonsPanel(IBuilder* builder, int buttons_menu_width,
                                   int buttons_menu_height) {
  builder->AddPanel("Projection")
      .AddSubPanel("")
      .SetSize(buttons_menu_width, buttons_menu_height)
      .Add<PIDoubleButton>(
          "", ConnectDoubleButton<ProjectionType>(SceneAction::kProjection),
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
      .Add<PIFileManagement>("", ConnectFileManagement(SceneAction::kOpenFile),
                             "Open", "File name:");
}

void MenuWidget::SetupStatusBar(StatusBarBuilder* builder, int status_bar_width,
                                int status_bar_height) {
  int status_info_width = status_bar_width * style_.status_info_width_ratio;
  int trash_button_width = status_bar_width * style_.trash_button_width_ratio;
  int trash_button_height =
      status_bar_height - style_.trash_button_height_padding;

  builder
      ->Add<TrashButton>(
          [this](TrashButton* btn) {
            btn->AddIcon("assets/icons/trash.png");
            connect(btn, &QPushButton::clicked, this, [this]() {
              emit ActionTriggered(SceneAction::kClearConfig, std::monostate{});
            });
          },
          trash_button_width, trash_button_height)
      .Add<StatusInfo>(ConnectStatusInfo(), status_info_width,
                       status_bar_height);
}

}  // namespace s21
