#ifndef EXCLUSIVE_DOUBLE_BUTTON_H_
#define EXCLUSIVE_DOUBLE_BUTTON_H_

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

#include "double_button_base.h"

#define LEFT_BUTTON_ID 0
#define RIGHT_BUTTON_ID 1

class ExclusiveDoubleButton : public DoubleButtonBase {
  Q_OBJECT
 public:
  explicit ExclusiveDoubleButton(const QString& left_button_name,
                                 const QString& right_button_name, int width,
                                 int height, QWidget* parent = nullptr);

 signals:
  void LeftButtonToggled(bool checked);
  void RightButtonToggled(bool checked);

 private:
  void SetupStyles() override;

  QButtonGroup* button_group_;

 private slots:
  void OnButtonToggled(QAbstractButton* button, bool checked);
};

#endif  // EXCLUSIVE_DOUBLE_BUTTON_H_
