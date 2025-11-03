#include "double_button_base.h"
#include <QtMath>

DoubleButtonBase::DoubleButtonBase(const QString& left_button_name,
                                   const QString& right_button_name,
                                   int width, int height,
                                   QWidget* parent)
  : QWidget(parent)
  , left_button_(new QPushButton(left_button_name))
  , right_button_(new QPushButton(right_button_name))
  , main_layout_(new QHBoxLayout(this))
  , widget_size_(width, height) {

  setFixedSize(widget_size_);
  SetupLayout();
  SetupButtonSize();
  SetupStyles();
}

void DoubleButtonBase::SetupLayout() {
  int spacing = 0;
  main_layout_->setSpacing(spacing);
  main_layout_->setContentsMargins(spacing, spacing, spacing, spacing);

  main_layout_->addWidget(left_button_);
  main_layout_->addWidget(right_button_);
}

void DoubleButtonBase::SetupButtonSize() {
  int button_width = widget_size_.width() / 2;
  int button_height = widget_size_.height();

  left_button_->setFixedSize(button_width, button_height);
  right_button_->setFixedSize(button_width, button_height);
}

void DoubleButtonBase::SetupStyles() {
  int button_width = width() / 2;
  int button_height = height();
  int button_area = button_width * button_height;

  int font_size = qSqrt(button_area) * 0.2;
  auto create_button_style = [font_size] (int radius_tl, int radius_tr,
                                          int radius_bl, int radius_br) {
    return QString(R"(
      QPushButton {
        background-color: #5A5A5A;
        color: white;
        border: 1px solid #7A7A7A;
        font-size: %1px;
        border-top-left-radius: %2px;
        border-bottom-left-radius: %3px;
        border-top-right-radius: %4px;
        border-bottom-right-radius: %5px;
      }
      QPushButton:hover {
        background-color: #484848;
      }
      QPushButton:pressed {
        background-color: #404040;
      }
    )")
      .arg(font_size)
      .arg(radius_tl)
      .arg(radius_bl)
      .arg(radius_tr)
      .arg(radius_br);
  };

  left_button_->setStyleSheet(create_button_style(4, 0, 4, 0));
  right_button_->setStyleSheet(create_button_style(0, 4, 0, 4));
}