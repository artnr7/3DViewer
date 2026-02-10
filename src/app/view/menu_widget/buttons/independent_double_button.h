#ifndef INDEPENDET_DOUBLE_BUTTON_H_
#define INDEPENDET_DOUBLE_BUTTON_H_

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

#include "double_button_base.h"

class IndependentDoubleButton : public DoubleButtonBase {
  Q_OBJECT
 public:
  explicit IndependentDoubleButton(const QString& left_button_name,
                                   const QString& right_button_name, int width,
                                   int height, QWidget* parent = nullptr);

 signals:
  void LeftButtonClicked();
  void RightButtonClicked();

 private slots:
  void OnLeftButtonClicked();
  void OnRightButtonClicked();
};

#endif  // INDEPENDET_DOUBLE_BUTTON_H_
