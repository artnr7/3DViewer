#include "panel_items.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qnamespace.h>
#include <qwidget.h>

namespace s21 {

PanelItem::PanelItem(const QString& name, int font_size, QWidget* parent)
  : QWidget(parent) {
  name_label_ = new QLabel(name, this);
  QString name_label_style = QString(R"(
      QLabel {
        background-color: transparent;
        border: none;
        color: white;
        font-size: %1px;
      }
    )").arg(font_size);

  name_label_->setStyleSheet(name_label_style);
}

PanelItemValueController::PanelItemValueController(const QString& name,
                                                   int width, int height, int font_size,
                                                   Qt::Orientation orientation, QWidget* parent)
  : PanelItem(name, font_size, parent) {

  QWidget* container = new QWidget(this);
  container->setFixedSize(width, height);

  if (orientation == Qt::Vertical) {
    QVBoxLayout* layout = new QVBoxLayout(container);
    valcontroll_ = new ValueController(width, height*0.7);
    name_label_->setAlignment(Qt::AlignCenter);
    name_label_->setFixedWidth(valcontroll_->GetWidth());
    layout->addWidget(valcontroll_);
    layout->addWidget(name_label_);

    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
  } else {
    QHBoxLayout* layout = new QHBoxLayout(container);
    layout->addWidget(name_label_);

    valcontroll_ = new ValueController();
    layout->addWidget(valcontroll_);
  }

  container->setStyleSheet(R"(
    border: 1px solid white;
  )");

  QLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->addWidget(container);
}

} // namespace s21