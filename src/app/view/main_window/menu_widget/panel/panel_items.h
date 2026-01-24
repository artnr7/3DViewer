#ifndef PANEL_ITEMS_H_
#define PANEL_ITEMS_H_

#include <QWidget>
#include <QPushButton>
#include <QLabel>

#include "style_configs/panel_items_style.h"
#include "value_controller/value_controller.h"
#include "combobox/combo_box.h"
#include "colordialog/color_picker.h"
#include "buttons/double_button_base.h"
#include "filedialog/file_dialog_panel.h"
#include "status_bar/status_bar.h"

namespace s21 {

/* PIBASe */
class PIBase: public QWidget {
 Q_OBJECT

 public:
  explicit PIBase(const QString& name, QWidget* parent = nullptr);
  virtual ~PIBase() = default;

 protected:
  /* Setup */
  void Initialize(int width, int height, Qt::Orientation orientation = Qt::Vertical);
  QString CreateLabelStyle(int font_size) const;

  virtual QWidget* CreateContentWidget(int width, int height) = 0;
  virtual void SetupContentConnections() = 0;

 protected:
  /* Fields */
  PIStyle style_;
  QLabel* name_label_ = nullptr;
};
//// PIBase

/* PIValueController */
class PIValueController: public PIBase {
 Q_OBJECT

 public:
  explicit PIValueController(const QString& name,
                                    int width, int height,
                                    Qt::Orientation orientation,
                                    QWidget* parent = nullptr);
  /* Value Management Accessors */
  int GetCurrentValue() const;

  /* Value Management Mutators */
  void SetCurrentValue(int value);
  void SetRange(int min_value, int max_value);

 signals:
  /* Signals */
  void CurrentValueChanged(int value);

 protected:
  /* Setup */
  QWidget* CreateContentWidget(int width, int height) override;
  void SetupContentConnections() override;

 private:
  /* Fields */
  ValueController* valcontroll_ = nullptr;
};
//// PIValueController

/* PIComboBox */
class PIComboBox: public PIBase {
  Q_OBJECT
 public:
  explicit PIComboBox(const QString& name,
                      int width, int height,
                      Qt::Orientation orientation,
                      QWidget* parent = nullptr);

  /* Value Management Accessors */

  /* Value Management Mutators */
  template <typename... Args>
  void AddItems(Args&&... args);

  void SetArrows(const QString& up_icon_path,
                 const QString& down_icon_path);

  // TODO: Fix signals
   // signals:
    /* Signals */
   // void CurrentValueChanged(int value);

 protected:
  /* Setup */
  QWidget* CreateContentWidget(int width, int height) override;
  void SetupContentConnections() override;

 private:
  CustomComboBox* combo_box_;
};

/* Value Management Mutators */
template <typename... Args>
void PIComboBox::AddItems(Args&&... args) {
  combo_box_->AddItems(std::forward<Args>(args)...);
}
// Value Management Mutators
//// PIComboBox

/* PIColorPicker */
class PIColorPicker: public PIBase {
  Q_OBJECT
 public:
  explicit PIColorPicker(const QString& name,
                         int width, int height,
                         Qt::Orientation orientation,
                         QWidget* parent = nullptr);
  /* Value Management Accessors */
  /* Value Management Mutators */

  // TODO: Fix signals
   // signals:
    /* Signals */
   // void CurrentValueChanged(int value);

 protected:
  /* Setup */
  QWidget* CreateContentWidget(int width, int height) override;
  void SetupContentConnections() override;

 private:
 /* Fields */
  ColorPicker* color_picker_;
};
//// PIColorPicker

/* PIDoubleButton */
class PIDoubleButton: public PIBase {
 Q_OBJECT

 public:
  explicit PIDoubleButton(const QString& name,
                          int width, int height,
                          const QString& left_text,
                          const QString& right_text,
                          bool is_exclusive,
                          QWidget* parent = nullptr);

  /* Value Management Accessors */
  /* Value Management Mutators */

 // TODO: Fix signals
 // signals:
  /* Signals */
 // void CurrentValueChanged(int value);

 protected:
  /* Setup */
  QWidget* CreateContentWidget(int width, int height) override;
  void SetupContentConnections() override;

 private:
  /* Fields */
  DoubleButtonBase* double_button_;
  bool is_exclusive_;
  QString left_text_;
  QString right_text_;
};
//// PIDoubleButton

/* PIFileManagement */
class PIFileManagement: public PIBase {
 Q_OBJECT

 public:
  explicit PIFileManagement(const QString& name,
                            int width, int height,
                            const QString& button_text,
                            const QString& label_text,
                            QWidget* parent = nullptr);

  /* Value Management Accessors */
  /* Value Management Mutators */

 // TODO: Fix signals
 // signals:
  /* Signals */
 // void CurrentValueChanged(int value);

 protected:
  /* Setup */
  QWidget* CreateContentWidget(int width, int height) override;
  void SetupContentConnections() override;

 private:
  /* Fields */
  FileDialogPanel* file_panel_;
  QString button_text_;
  QString label_text_;
};
//// PIFileManagement

} // namespace s21

#endif // PANEL_ITEMS_H_
