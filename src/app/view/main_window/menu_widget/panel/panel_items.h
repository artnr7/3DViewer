#ifndef PANEL_ITEMS_H_
#define PANEL_ITEMS_H_

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "value_controller/value_controller.h"
#include "buttons/double_button_base.h"
#include "combobox/combo_box.h"

namespace s21 {

class PanelItem: public QWidget {
  Q_OBJECT
 public:
  explicit PanelItem(const QString& name, QWidget* parent = nullptr);
 protected:
  QLabel* name_label_;
};

class PanelItemValueController: public PanelItem {
  Q_OBJECT
 public:
  explicit PanelItemValueController(const QString& name,
                                    int width, int height,
                                    Qt::Orientation orientation, QWidget* parent = nullptr);
 private:
  ValueController* valcontroll_;
};

class PanelItemDoubleButton: public PanelItem {
  Q_OBJECT
 public:
  explicit PanelItemDoubleButton(int width, int height,
                                 bool is_exclusive,
                                 QWidget* parent = nullptr);
 private:
  DoubleButtonBase* dbutton_;
};

class PanelItemFileManagment: public PanelItem {
  Q_OBJECT
 public:
  explicit PanelItemFileManagment(int width, int height,
                                  QWidget* parent = nullptr);
 private:
  QPushButton* open_button_;
};

class PanelItemComboBox: public PanelItem {
  Q_OBJECT
 public:
  explicit PanelItemComboBox(const QString& name, int width, int height,
                                  QWidget* parent = nullptr);
 private:
  CustomComboBox* combo_box_;
};

} // namespace s21

#endif // PANEL_ITEMS_H_
