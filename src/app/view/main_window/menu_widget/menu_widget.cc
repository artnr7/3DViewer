#include "menu_widget.h"
#include "../config.hpp"
#include "panel/panel.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QDebug>

s21::MenuWidget::MenuWidget(QWidget *parent)
  : QWidget(parent) {
  setStyleSheet("background-color: #2C2B2B; color: white;");
  setFixedSize(INIT_W_MENU_WIDGET, INIT_H_MENU_WIDGET);
  SetupUI();
}

void s21::MenuWidget::SetupUI() {
  QVBoxLayout *main_layout = new QVBoxLayout(this);
  int spacing = 0;
  main_layout->setSpacing(spacing);
  main_layout->setContentsMargins(spacing, spacing, spacing, spacing);

  // TRANSFORM PANEL //
  Panel* transform_panel = new Panel("Transform", this);
  SubPanel* translation = new SubPanel("Translation", this);
  SubPanel* rotation = new SubPanel("Rotation", this);
  SubPanel* scale = new SubPanel("Scale", this);

  // int panel_width = transform_panel->width();
  // int item_width = panel_width * 0.9;
  // int item_height = transform_panel->height();
  // int font_size = item_height*0.4;

  int panel_width = INIT_W_MENU_WIDGET - 20;
  int item_height = 43;
  int item_width = panel_width * 0.3;
  int font_size = item_height * 0.3;

  translation->AddItem(new PanelItemValueController("x", item_width, item_height, font_size, Qt::Vertical, this));
  translation->AddItem(new PanelItemValueController("y", item_width, item_height, font_size, Qt::Vertical, this));
  translation->AddItem(new PanelItemValueController("z", item_width, item_height, font_size, Qt::Vertical, this));

  rotation->AddItem(new PanelItemValueController("x", item_width, item_height, font_size, Qt::Vertical, this));
  rotation->AddItem(new PanelItemValueController("y", item_width, item_height, font_size, Qt::Vertical, this));
  rotation->AddItem(new PanelItemValueController("z", item_width, item_height, font_size, Qt::Vertical, this));

  scale->AddItem(new PanelItemValueController("z", item_width, item_height, font_size, Qt::Vertical, this));

  transform_panel->AddMiniPanel(translation);
  transform_panel->AddMiniPanel(rotation);
  transform_panel->AddMiniPanel(scale);

  // SHADING PANEL //
  Panel* shading_panel = new Panel("Shading", this);
  SubPanel* vertices = new SubPanel("Vertices", this);
  SubPanel* edges = new SubPanel("Edges", this);
  SubPanel* background = new SubPanel("Background", this);

  vertices->AddItem(new PanelItemValueController("size", item_width, item_height, font_size, Qt::Vertical, this));
  edges->AddItem(new PanelItemValueController("size", item_width, item_height, font_size, Qt::Vertical, this));

  shading_panel->AddMiniPanel(vertices);
  shading_panel->AddMiniPanel(edges);
  shading_panel->AddMiniPanel(background);

  // PROJECTION PANEL //
  Panel* projection_panel = new Panel("Projection", this);

  // RENDER PANEL //
  Panel* render_panel = new Panel("Render", this);

  // FILES PANEL //
  Panel* files_panel = new Panel("Files", this);

  main_layout->addWidget(transform_panel);
  main_layout->addWidget(shading_panel);
  main_layout->addWidget(projection_panel);
  main_layout->addWidget(render_panel);
  main_layout->addWidget(files_panel);
  main_layout->addStretch();
}
