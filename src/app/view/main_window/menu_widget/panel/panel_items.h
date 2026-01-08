#ifndef PANEL_ITEMS_H_
#define PANEL_ITEMS_H_

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <qvariant.h>

#include "style_configs/panel_items_style.h"
#include "value_controller/value_controller.h"
#include "buttons/double_button_base.h"
#include "combobox/combo_box.h"
#include "colordialog/color_picker.h"

namespace s21 {

class PanelItem: public QWidget {
 Q_OBJECT
 public:
  explicit PanelItem(const QString& name, QWidget* parent = nullptr);

 protected:
  /* Setup Label */
  QString CreateLabelStyle(int font_size) const;

  /* Fields */
  QLabel* name_label_;
  PanelItemStyle style_;
};

class PanelItemValueController: public PanelItem {
  Q_OBJECT
 public:
  explicit PanelItemValueController(const QString& name,
                                    int width, int height,
                                    Qt::Orientation orientation,
                                    QWidget* parent = nullptr);
  /* Value Management Accessors */
  int GetCurrentValue() const;

  /* Value Management Mutators */
  void SetCurrentValue(int value);
  void SetRange(int min_value, int max_value);

 signals:
  void CurrentValueChanged(int value);

 private:
  /* Setup */
  void SetupVerticalLayout(int width, int height);
  void SetupHorizontalLayout();
  void SetupConnections();

 private:
  /* Fields */
  ValueController* valcontroll_;
  Qt::Orientation orientation_;
  QWidget* container_;
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
  template <typename... Args>
  void AddItems(Args&&... args) {
    combo_box_->AddItems(std::forward<Args>(args)...);
  }

  void SetArrows(const QString& up_icon_path,
                 const QString& down_icon_path) {
    combo_box_->SetArrows(up_icon_path, down_icon_path);
  }

 private:
  CustomComboBox* combo_box_;
};

class PanelItemColorPicker: public PanelItem {
  Q_OBJECT
 public:
  explicit PanelItemColorPicker(const QString& name, int width, int height,
                                  QWidget* parent = nullptr);
 private:
  ColorPicker* color_picker_;
};

} // namespace s21

#endif // PANEL_ITEMS_H_
