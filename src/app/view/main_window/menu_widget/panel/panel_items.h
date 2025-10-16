#ifndef PANEL_ITEMS_H_
#define PANEL_ITEMS_H_

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "../value_controller.h"

namespace s21 {

class PanelItem: public QWidget {
  Q_OBJECT
 public:
  explicit PanelItem(const QString& name, int font_size, QWidget* parent = nullptr);
 protected:
  QLabel* name_label_;
};

class PanelItemValueController: public PanelItem {
  Q_OBJECT
 public:
  explicit PanelItemValueController(const QString& name,
                                    int width, int height, int font_size,
                                    Qt::Orientation orientation, QWidget* parent);
 private:
  ValueController* valcontroll_;
};


} // namespace s21

#endif // PANEL_ITEMS_H_