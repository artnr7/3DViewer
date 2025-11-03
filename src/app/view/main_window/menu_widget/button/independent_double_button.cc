#include "independent_double_button.h"

IndependentDoubleButton::IndependentDoubleButton(const QString& left_button_name,
                                                 const QString& right_button_name,
                                                 int width, int height,
                                                 QWidget* parent)
  : DoubleButtonBase(left_button_name, right_button_name, width, height, parent) {

  connect(right_button_, &QPushButton::clicked, this, &IndependentDoubleButton::OnLeftButtonClicked);
  connect(left_button_, &QPushButton::clicked, this, &IndependentDoubleButton::OnRightButtonClicked);
}

void IndependentDoubleButton::OnLeftButtonClicked() {
  emit LeftButtonClicked();
}

void IndependentDoubleButton::OnRightButtonClicked() {
  emit RightButtonClicked();
}