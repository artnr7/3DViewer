#ifndef MENU_WIDGET_HPP_
#define MENU_WIDGET_HPP_

#include <qtmetamacros.h>

#include <QWidget>


namespace s21 {
class MenuWidget : public QWidget {
  Q_OBJECT
 private:
  void Connections();

  QTimer* temp_timer;

 public:
  MenuWidget(QWidget* parent = nullptr);

 signals:
  void NewFilenameEntered(const std::string& obj_filename);

 private slots:
  void CreateNewObjectImitated();
};
}  // namespace s21

#endif