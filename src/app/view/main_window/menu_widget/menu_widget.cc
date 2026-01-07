#include "menu_widget.h"
#include "config.h"
#include "panel/panel.h"
#include "panel/panel_items.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QDebug>
#include <qboxlayout.h>
#include <qlabel.h>
#include <qwidget.h>

s21::MenuWidget::MenuWidget(QWidget *parent)
  : QWidget(parent) {
  setFixedSize(INIT_W_MENU_WIDGET, INIT_H_MENU_WIDGET);
  setContentsMargins(0, 0, 0, 0);
  SetupUI();
}

void s21::MenuWidget::SetupUI() {
  QVBoxLayout *main_layout = new QVBoxLayout(this);
  int spacing = 0;
  main_layout->setSpacing(spacing);
  main_layout->setContentsMargins(spacing, spacing, spacing, spacing);

  const int status_bar_h = 30;
  ToolBar* tool_bar = new ToolBar(INIT_W_MENU_WIDGET, INIT_H_MENU_WIDGET - status_bar_h, this);

  // TRANSFORM PANEL //
  Panel* transform_panel = new Panel("Transform", tool_bar);

  SubPanel* translation = new SubPanel("Translation");
  SubPanel* rotation = new SubPanel("Rotation");
  SubPanel* scale = new SubPanel("Scale");

  int panel_width = INIT_W_MENU_WIDGET - 20;
  int item_height = 44;
  int item_width = panel_width * 0.3;

  translation->AddItem(new PanelItemValueController("x", item_width, item_height, Qt::Vertical));
  translation->AddItem(new PanelItemValueController("y", item_width, item_height, Qt::Vertical));
  translation->AddItem(new PanelItemValueController("z", item_width, item_height, Qt::Vertical));

  rotation->AddItem(new PanelItemValueController("x", item_width, item_height, Qt::Vertical));
  rotation->AddItem(new PanelItemValueController("y", item_width, item_height, Qt::Vertical));
  rotation->AddItem(new PanelItemValueController("z", item_width, item_height, Qt::Vertical));

  scale->AddItem(new PanelItemValueController("z", item_width, item_height, Qt::Vertical));

  transform_panel->AddMiniPanel(translation);
  transform_panel->AddMiniPanel(rotation);
  transform_panel->AddMiniPanel(scale);

  // SHADING PANEL //
  Panel* shading_panel = new Panel("Shading");
  SubPanel* vertices = new SubPanel("Vertices");
  SubPanel* edges = new SubPanel("Edges");
  SubPanel* background = new SubPanel("Background");

  PanelItemComboBox* pcmb1 = new PanelItemComboBox("style", item_width, item_height);
  PanelItemComboBox* pcmb2 = new PanelItemComboBox("style", item_width, item_height);
  pcmb1->SetArrows("assets/icons/open_arrow.png", "assets/icons/close_arrow.png");
  pcmb1->AddItems("assets/icons/square.png", "assets/icons/circle.png");
  pcmb2->SetArrows("assets/icons/open_arrow.png", "assets/icons/close_arrow.png");
  pcmb2->AddItems("assets/icons/line.png", "assets/icons/line_dash.png");

  vertices->AddItem(new PanelItemValueController("size", item_width, item_height, Qt::Vertical));
  vertices->AddItem(pcmb1);
  edges->AddItem(new PanelItemValueController("size", item_width, item_height, Qt::Vertical));
  edges->AddItem(pcmb2);

  shading_panel->AddMiniPanel(vertices);
  shading_panel->AddMiniPanel(edges);
  shading_panel->AddMiniPanel(background);

  // PROJECTION PANEL //
  Panel* projection_panel = new Panel("Projection");
  SubPanel* pr_pan = new SubPanel("");

  pr_pan->AddItem(new PanelItemDoubleButton(panel_width-20, item_height, true));

  projection_panel->AddMiniPanel(pr_pan);

  // RENDER PANEL //
  Panel* render_panel = new Panel("Render");
  SubPanel* re_pan = new SubPanel("");

  re_pan->AddItem(new PanelItemDoubleButton(panel_width-20, item_height, false));

  render_panel->AddMiniPanel(re_pan);

  // FILES PANEL //
  Panel* files_panel = new Panel("Files");
  SubPanel* fi_pan = new SubPanel("");
  fi_pan->AddItem(new PanelItemFileManagment(panel_width-20, item_height));

  files_panel->AddMiniPanel(fi_pan);

  StatusBar* status_bar = new StatusBar(INIT_W_MENU_WIDGET, status_bar_h, this);
  status_bar->AddPanel(new Panel("as"));

  tool_bar->AddPanel(transform_panel);
  tool_bar->AddPanel(shading_panel);
  tool_bar->AddPanel(projection_panel);
  tool_bar->AddPanel(render_panel);
  tool_bar->AddPanel(files_panel);

  main_layout->addWidget(tool_bar);
  main_layout->addWidget(status_bar);
  main_layout->addStretch();
}
