#ifndef VALUE_CONTROLLER_H_
#define VALUE_CONTROLLER_H_

#include "value_controller_base.h"

namespace s21 {

class ValueControllerFloat : public ValueControllerBase<float> {
  Q_OBJECT

 public:
  explicit ValueControllerFloat(int width = 100, int height = 40,
                                QWidget *parent = nullptr)
      : ValueControllerBase<float>(width, height, parent) {}

 signals:
  void CurrentValueChanged(float value);

 protected:
  void ValueChanged(float value) override {
    emit CurrentValueChanged(value);
  }

  void UpdateValueField() override {
    value_field_->setText(QString::number(current_value_, 'f', 3));
  }
};

class ValueControllerInt : public ValueControllerBase<int> {
  Q_OBJECT

 public:
  explicit ValueControllerInt(int width = 100, int height = 40,
                              QWidget *parent = nullptr)
      : ValueControllerBase<int>(width, height, parent) {}

 signals:
  void CurrentValueChanged(int value);

 protected:
  void ValueChanged(int value) override {
    emit CurrentValueChanged(value);
  }
};

}  // namespace s21

#endif  // VALUE_CONTROLLER_H_
