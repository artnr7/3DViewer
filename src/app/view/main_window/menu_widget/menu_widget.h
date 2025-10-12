#ifndef MENU_WIDGET_HPP_
#define MENU_WIDGET_HPP_

#include <QWidget>

namespace s21 {
class MenuWidget : public QWidget {
 private:
 public:
  MenuWidget(QWidget *parent = nullptr);
  void SetupUI();
};
}  // namespace s21

#endif