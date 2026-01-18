#include "panel.h"
#include "config.h"

namespace s21 {

SubPanel::SubPanel(const QString &name, QWidget *parent)
  : QWidget(parent) {

  QVBoxLayout* main_layout = new QVBoxLayout(this);

  if (!name.isEmpty()) {
    name_label_ = new QLabel(name);
    name_label_->setStyleSheet(R"(
      QLabel {
        background-color: transparent;
        color: white;
        font-size: 14px;
      }
    )");

    main_layout->addWidget(name_label_);
  }

  items_layout_ = new QHBoxLayout();
  main_layout->addLayout(items_layout_);
}

void SubPanel::AddItem(PIBase* item) {
  items_layout_->addWidget(item);
}

int SubPanel::GetWidth() const {
  return items_layout_->geometry().width();
}

Panel::Panel(const QString &name, QWidget *parent)
  : QWidget(parent) {
//  this->setContentsMargins(0, 10, 0, 10);

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
  main_layout_->setContentsMargins(0, 10, 0, 0);
  main_layout_->setSpacing(0);
  main_layout_->addWidget(panel_name_label_);

  QVBoxLayout* outer_layout = new QVBoxLayout(this);
  outer_layout->setContentsMargins(0, 0, 0, 0);
  outer_layout->setSpacing(0);
  outer_layout->addWidget(container);
}

void Panel::AddSubPanel(SubPanel* mini_panel) {
  main_layout_->addWidget(mini_panel);
}


ToolBar::ToolBar(int width, int height, QWidget *parent)
  : QWidget(parent) {

  setFixedSize(width, height);

  QVBoxLayout* main_layout_ = new QVBoxLayout(this);
  main_layout_->setContentsMargins(0, 0, 0, 0);
  main_layout_->setSpacing(0);

  background_ = new QWidget(this);
  setObjectName("ToolBar");
  background_->setObjectName("ToolBarBackground");
  background_->setStyleSheet(R"(
    #ToolBarBackground {
      background-color: #2C2B2B;
  })");
  main_layout_->addWidget(background_);

  layout_ = new QVBoxLayout(background_);
  int space = 10;
  layout_->setContentsMargins(space, space, space, space);
  layout_->setSpacing(8);
}

void ToolBar::AddPanel(Panel* panel) {
  layout_->addWidget(panel);
}

StatusBar::StatusBar(int width, int height, QWidget *parent)
  : QWidget(parent) {
  setFixedSize(width, height);
  setStyleSheet("background-color: #3D3D3D;");

  QVBoxLayout* layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
}

void StatusBar::AddPanel(Panel* panel) {
  layout()->addWidget(panel);
}

} // namespace s21
