#include "panel_items.h"

#include "../button/exclusive_double_button.h"
#include "../button/independent_double_button.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qnamespace.h>
#include <qwidget.h>

namespace s21 {

PanelItem::PanelItem(const QString& name, QWidget* parent)
  : QWidget(parent) {

  if (!name.isEmpty()) {
    name_label_ = new QLabel(name, this);

    name_label_->setStyleSheet(R"(
        QLabel {
          background-color: transparent;
          border: none;
          color: white;
          font-size: 10px;
        }
      )");
  }
}

PanelItemValueController::PanelItemValueController(const QString& name,
                                                   int width, int height,
                                                   Qt::Orientation orientation, QWidget* parent)
  : PanelItem(name, parent) {

  int font_size = height * 0.3;
  QWidget* container = new QWidget(this);
  container->setFixedSize(width, height);

  name_label_->setStyleSheet(QString(R"(
    QLabel {
      background-color: transparent;
      border: none;
      color: white;
      font-size: 10px;
    }
  )").arg(font_size));

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

PanelItemDoubleButton::PanelItemDoubleButton(int width, int height,
                                             bool is_exclusive,
                                             QWidget* parent)
  : PanelItem("", parent) {

  QWidget* container = new QWidget(this);
  container->setFixedSize(width, height);

  QVBoxLayout* layout = new QVBoxLayout(container);
  if (is_exclusive) {
    dbutton_ = new ExclusiveDoubleButton("perspective", "orthography", width, height*0.7, this);
  } else {
    dbutton_ = new IndependentDoubleButton("GIF", "Image", width, height*0.7, this);
  }

  layout->addWidget(dbutton_);

  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);

  container->setStyleSheet(R"(
    border: 1px solid white;
  )");

  QLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->addWidget(container);
}

} // namespace s21