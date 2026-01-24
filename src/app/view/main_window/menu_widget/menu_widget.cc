#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QDebug>
#include <qnamespace.h>

#include "menu_widget.h"
#include "config.h"
#include "menu_builder/menu_builder.h"
#include "panel/panel.h"
#include "panel/panel_items.h"

namespace s21 {

MenuWidget::MenuWidget(QWidget *parent)
  : QWidget(parent) {
  setFixedSize(INIT_W_MENU_WIDGET, INIT_H_MENU_WIDGET);
  setContentsMargins(0, 0, 0, 0);
  SetupUI();
}

void MenuWidget::SetupUI() {
  QVBoxLayout *main_layout = new QVBoxLayout(this);
  int spacing = 0;
  main_layout->setSpacing(spacing);
  main_layout->setContentsMargins(spacing, spacing, spacing, spacing);

  const int status_bar_h = 30;

  ToolBar* tool_bar = new ToolBar(INIT_W_MENU_WIDGET, INIT_H_MENU_WIDGET - status_bar_h);
  StatusBar* status_bar = new StatusBar(INIT_W_MENU_WIDGET, status_bar_h);

  int panel_width = INIT_W_MENU_WIDGET - 20;
  int item_height = 44;
  int item_width = panel_width * 0.3;


  /* TODO: FIX SIGNALS */
  MenuBuilder tool_builder(tool_bar, item_width, item_height);

  tool_builder.AddPanel("Transform")
      .AddSubPanel("Translation")
        .Add<PIValueController>("x", nullptr, Qt::Vertical)
        .Add<PIValueController>("y", nullptr, Qt::Vertical)
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
        .Add<PIDoubleButton>("", nullptr, "perspective", "ortography", true)
    .AddPanel("Render")
      .AddSubPanel("")
        .Add<PIDoubleButton>("", nullptr, "GIF", "Image", false)
    .AddPanel("Files")
      .AddSubPanel("")
        .Add<PIFileManagement>("", nullptr, "Open", "File name:");

  // pcmb1->SetArrows("assets/icons/open_arrow.png", "assets/icons/close_arrow.png");
  // pcmb1->AddItems("assets/icons/square.png", "assets/icons/circle.png");
  // pcmb2->SetArrows("assets/icons/open_arrow.png", "assets/icons/close_arrow.png");
  // pcmb2->AddItems("assets/icons/line.png", "assets/icons/line_dash.png");

  main_layout->addWidget(tool_bar);
  main_layout->addWidget(status_bar);
  // main_layout->addStretch();
}

} // namespace s21
