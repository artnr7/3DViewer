#include "panel_items.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qnamespace.h>

namespace s21 {

PanelItem::PanelItem(const QString& name, QWidget* parent)
  : QWidget(parent) {
  name_label_ = new QLabel(name, this);
  name_label_->setStyleSheet(R"(
      QLabel {
        background-color: transparent;
        color: white;
      }
    )");
  }

PanelItemValueController::PanelItemValueController(const QString& name, Qt::Orientation orientation, QWidget* parent)
  : PanelItem(name, parent) {

  if (orientation == Qt::Vertical) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    valcontroll_ = new ValueController();
    name_label_->setAlignment(Qt::AlignCenter);

    name_label_->setFixedWidth(valcontroll_->GetWidth());
    layout->addWidget(valcontroll_);
    layout->addWidget(name_label_);
  } else {
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(name_label_);

    valcontroll_ = new ValueController();
    layout->addWidget(valcontroll_);
  }
}

} // namespace s21