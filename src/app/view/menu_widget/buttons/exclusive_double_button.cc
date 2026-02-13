#include "exclusive_double_button.h"

#include "double_button_base.h"

ExclusiveDoubleButton::ExclusiveDoubleButton(const QString& left_button_name,
                                             const QString& right_button_name,
                                             int width, int height,
                                             QWidget* parent)
    : DoubleButtonBase(left_button_name, right_button_name, width, height,
                       parent),
      button_group_(new QButtonGroup) {
  left_button_->setCheckable(true);
  right_button_->setCheckable(true);

  button_group_->addButton(left_button_, LEFT_BUTTON_ID);
  button_group_->addButton(right_button_, RIGHT_BUTTON_ID);
  button_group_->setExclusive(true);

  left_button_->setChecked(true);

  SetupStyles();

  connect(button_group_,
          QOverload<QAbstractButton*, bool>::of(&QButtonGroup::buttonToggled),
          this, &ExclusiveDoubleButton::OnButtonToggled);
}

void ExclusiveDoubleButton::OnButtonToggled(QAbstractButton* button,
                                            bool checked) {
  if (checked) {
    int id = button_group_->id(button);
    if (id == LEFT_BUTTON_ID) {
      emit ButtonToggled(ButtonSide::kLeft);
    } else if (id == RIGHT_BUTTON_ID) {
      emit ButtonToggled(ButtonSide::kRight);
    }
  }
}

void ExclusiveDoubleButton::SetupStyles() {
  QString checked_style = R"(
    QPushButton:checked {
      background-color: #303030;
      border-color: #505050;
    }
  )";
  left_button_->setStyleSheet(left_button_->styleSheet() + checked_style);
  right_button_->setStyleSheet(right_button_->styleSheet() + checked_style);
}
