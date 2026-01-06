#include "panel_items.h"

#include "buttons/exclusive_double_button.h"
#include "buttons/independent_double_button.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

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

  int font_size = height * 0.4;
  QWidget* container = new QWidget(this);
  container->setFixedSize(width, height);

  name_label_->setStyleSheet(QString(R"(
    QLabel {
      background-color: transparent;
      border: none;
      color: white;
      font-size: 15px;
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
    background-color: transparent;
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
    background-color: transparent;
  )");

  QLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->addWidget(container);
}


PanelItemFileManagment::PanelItemFileManagment(int width, int height,
                                               QWidget* parent)
  : PanelItem("", parent) {

  QWidget* container = new QWidget(this);
  container->setFixedSize(width, height);

  QHBoxLayout* layout = new QHBoxLayout(container);

  QPushButton* open_button_ = new QPushButton("Open", this);
  open_button_->setFixedSize(width/3, height);
  open_button_->setStyleSheet(R"(
      QPushButton {
        background-color: #5A5A5A;
        color: white;
        border: 1px solid #7A7A7A;
        font-size: 12px;
        border-radius: 4px;
      }
      QPushButton:hover {
        background-color: #484848;
      }
      QPushButton:pressed {
        background-color: #404040;
      }
    )");

  QLabel* plainTextLabel = new QLabel("File name:", this);
  plainTextLabel->setFixedSize(width/3, height * 0.7);
  plainTextLabel->setStyleSheet(R"(
      QLabel {
        background-color: transparent;
        color: white;
        border: none;
        font-size: 15px;
        padding: 5px;
      }
    )");
  plainTextLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

  QWidget* textContainer = new QWidget(this);
  textContainer->setFixedSize(width, height);
  textContainer->setStyleSheet(R"(
      QWidget {
          background-color: #202020;
          border: 1px solid #606060;
          border-radius: 2px;
      }
  )");

  QHBoxLayout* textLayout = new QHBoxLayout(textContainer);
  textLayout->setContentsMargins(2, 2, 2, 2);

  QLabel* framedTextLabel = new QLabel("majorswe_dogывппвыладлыдавларолоыаврло", textContainer);
  framedTextLabel->setStyleSheet(R"(
      QLabel {
          background-color: transparent;
          color: white;
          border: none;
          font-size: 12px;
          padding: 4px;
      }
    )");
  framedTextLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

  layout->addWidget(open_button_);
  layout->addWidget(plainTextLabel);
  textLayout->addWidget(framedTextLabel);

  layout->addWidget(textContainer);

  layout->setAlignment(open_button_, Qt::AlignLeft);

  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);

  container->setStyleSheet(R"(
    border: 1px solid white;
    background-color: transparent;
  )");

  QLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->addWidget(container);
}

PanelItemComboBox::PanelItemComboBox(const QString& name, int width, int height,
                                               QWidget* parent)
  : PanelItem(name, parent) {

  int font_size = height * 0.2;
  QWidget* container = new QWidget(this);
  container->setFixedSize(width, height);

  name_label_->setStyleSheet(QString(R"(
    QLabel {
      border: none;
      color: white;
      font-size: %1px;
      font-weight: bold;
    }
  )").arg(font_size));

  QVBoxLayout* layout = new QVBoxLayout(container);
  combo_box_ = new CustomComboBox(width, height*0.7);
  name_label_->setAlignment(Qt::AlignCenter);
  name_label_->setFixedWidth(width);
  layout->addWidget(combo_box_);
  layout->addWidget(name_label_);

  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);

  QLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->addWidget(container);
}

} // namespace s21
