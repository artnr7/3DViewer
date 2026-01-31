#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QDebug>
#include <qnamespace.h>
#include <qstringview.h>
#include <type_traits>

#include "menu_widget.h"
#include "menu_builder/menu_builder.h"
#include "panel/panel.h"
#include "panel/panel_items.h"
#include "status_bar/status_bar.h"

namespace s21 {

MenuWidget::MenuWidget(int width, int height, QWidget *parent)
  : QWidget(parent)
  , width_(width)
  , height_(height)
  , style_{} {
  setFixedSize(width_, height_);
  setContentsMargins(style_.zero_margins);
  SetupUI();
}

void MenuWidget::SetupUI() {
  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setSpacing(style_.zero_spacing);
  main_layout->setContentsMargins(style_.zero_margins);

  const int status_bar_width = width_;
  const int status_bar_height = height_*style_.status_bar_height_ratio;
  const int tool_bar_width = width_;
  const int tool_bar_height = height_*style_.tool_bar_height_ratio;

  const int panel_width = tool_bar_width - 2*style_.edge_margin;
  const int buttons_menu_width = panel_width - 2*style_.buttons_edge_margin_in_panel;

  const int item_width = panel_width * style_.item_width_ratio;
  const int item_height = style_.item_height;

  ToolBar* tool_bar = new ToolBar(tool_bar_width, tool_bar_height);
  StatusBar* status_bar = new StatusBar(status_bar_width, status_bar_height);

  /* TODO: FIX SIGNALS */
  MenuBuilder tool_builder(tool_bar, item_width, item_height);
  SetupToolBar(tool_builder, buttons_menu_width, item_height);
  SetupStatusBar(status_bar);

  // pcmb1->SetArrows("assets/icons/open_arrow.png", "assets/icons/close_arrow.png");
  // pcmb1->AddItems("assets/icons/square.png", "assets/icons/circle.png");
  // pcmb2->SetArrows("assets/icons/open_arrow.png", "assets/icons/close_arrow.png");
  // pcmb2->AddItems("assets/icons/line.png", "assets/icons/line_dash.png");

  main_layout->addWidget(tool_bar);
  main_layout->addWidget(status_bar);
}

void MenuWidget::SetupToolBar(IBuilder& builder, int buttons_menu_width, int buttons_menu_height) {
  builder.AddPanel("Transform")
      .AddSubPanel("Translation")
        .Add<PIValueController>("x",
            Connect(SceneAction::kTranslateX, &PIValueController::CurrentValueChanged),
            Qt::Vertical)
        .Add<PIValueController>("y", Connect(SceneAction::kTranslateY, &PIValueController::CurrentValueChanged), Qt::Vertical)
        .Add<PIValueController>("z", nullptr, Qt::Vertical)
      .AddSubPanel("Rotation")
        .Add<PIValueController>("x", nullptr, Qt::Vertical)
        .Add<PIValueController>("y", nullptr, Qt::Vertical)
        .Add<PIValueController>("z", nullptr, Qt::Vertical)
      .AddSubPanel("Scale")
        .Add<PIValueController>("value", nullptr, Qt::Horizontal)
    .AddPanel("Shading")
      .AddSubPanel("Vertices")
        .Add<PIValueController>("size", nullptr, Qt::Vertical)
        .Add<PIComboBox>("style", nullptr, Qt::Vertical)
        .Add<PIColorPicker>("color", nullptr, Qt::Vertical)
      .AddSubPanel("Edges")
        .Add<PIValueController>("thickness", nullptr, Qt::Vertical)
        .Add<PIComboBox>("style", nullptr, Qt::Vertical)
        .Add<PIColorPicker>("color", nullptr, Qt::Vertical)
      .AddSubPanel("Background")
        .Add<PIColorPicker>("color", nullptr, Qt::Horizontal)
    .AddPanel("Projection")
      .AddSubPanel("")
        .SetSize(buttons_menu_width, buttons_menu_height)
        .Add<PIDoubleButton>("", nullptr, "perspective", "ortography", true)
    .AddPanel("Render")
      .AddSubPanel("")
        .SetSize(buttons_menu_width, buttons_menu_height)
        .Add<PIDoubleButton>("", nullptr, "GIF", "Image", false)
    .AddPanel("Files")
      .AddSubPanel("")
        .SetSize(buttons_menu_width, buttons_menu_height)
        .Add<PIFileManagement>("", nullptr, "Open", "File name:");
}

void MenuWidget::SetupStatusBar(StatusBar* status_bar) {
  connect(this, &MenuWidget::UpdateInfo, status_bar, &StatusBar::OnUpdateInfo);
  connect(this, &MenuWidget::ShowError, status_bar, &StatusBar::OnShowError);
}

void MenuWidget::OnUpdateObjectInfo(ModelUpdateData data){
  std::visit([this](auto&& arg){
    using T = std::decay_t<decltype(arg)>;

    if constexpr (std::is_same_v<T, ObjectInfo>) {
      emit UpdateInfo(arg.vertices, arg.edges);
    } else if constexpr (std::is_same_v<T, QString>) {
      emit ShowError(arg);
    }
  }, data);
}

} // namespace s21
