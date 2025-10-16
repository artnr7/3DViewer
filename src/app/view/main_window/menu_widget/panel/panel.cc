#include "panel.h"
#include <qboxlayout.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <qwidget.h>

namespace s21 {

SubPanel::SubPanel(const QString &name, QWidget *parent)
  : QWidget(parent) {

  QVBoxLayout* main_layout = new QVBoxLayout(this);

  name_label_ = new QLabel(name);
  name_label_->setStyleSheet(R"(
    QLabel {
      background-color: transparent;
      color: white;
      font-size: 14px;
    }
  )");

  main_layout->addWidget(name_label_);

  items_layout_ = new QHBoxLayout();
  main_layout->addLayout(items_layout_);
}

void SubPanel::AddItem(PanelItem* item) {
  items_layout_->addWidget(item);
}

int SubPanel::GetWidth() const {
  return items_layout_->geometry().width();
}

Panel::Panel(const QString &name, QWidget *parent)
  : QWidget(parent) {
//  this->setContentsMargins(0, 0, 0, 0);

  QWidget* container = new QWidget();
  container->setObjectName("panel_container");
  container->setStyleSheet(R"(
    QWidget#panel_container {
      background-color: #3D3D3D;
      border-radius: 10px;
      border: solid;
    }
  )");

  panel_name_label_ = new QLabel(name);
  panel_name_label_->setAlignment(Qt::AlignCenter);
  panel_name_label_->setStyleSheet(R"(
    QLabel {
      background-color: transparent;
      color: white;
      font-weight: bold;
      font-size: 14px;
    }
  )");

  main_layout_ = new QVBoxLayout(container);
  main_layout_->setContentsMargins(0, 0, 0, 0);
  main_layout_->setSpacing(0);
  main_layout_->addWidget(panel_name_label_);

  QVBoxLayout* outer_layout = new QVBoxLayout(this);
  outer_layout->addWidget(container);
}

void Panel::AddMiniPanel(SubPanel* mini_panel) {
  main_layout_->addWidget(mini_panel);
}

} // namespace s21