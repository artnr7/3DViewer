#ifndef PANEL_ITEMS_H_
#define PANEL_ITEMS_H_

#include <qnamespace.h>

#include <QLabel>
#include <QPushButton>
#include <QWidget>

#include "buttons/double_button_base.h"
#include "colordialog/color_picker.h"
#include "combobox/combo_box.h"
#include "filedialog/file_dialog_panel.h"
#include "status_info/status_info.h"
#include "style_configs/panel_items_style.h"
#include "value_controller/value_controller.h"

namespace s21 {

/* PIBASe */
class PIBase : public QWidget {
  Q_OBJECT

public:
  explicit PIBase(const QString &name, Qt::Orientation orientation,
                  QWidget *parent = nullptr);
  virtual ~PIBase() = default;
  Qt::Orientation GetOrientation();

protected:
  /* Setup */
  void Initialize(int width, int height);

  QString CreateLabelStyle(int font_size) const;

  virtual QWidget *CreateContentWidget(int width, int height) = 0;
  virtual void SetupContentConnections() = 0;

protected:
  /* Fields */
  PIStyle style_;
  Qt::Orientation orientation_;
  QLabel *name_label_ = nullptr;
};
//// PIBase

/* PIValueControllerFloat */
class PIValueControllerFloat : public PIBase {
  Q_OBJECT

 public:
  explicit PIValueControllerFloat(const QString &name, int width, int height,
                                  Qt::Orientation orientation,
                                  QWidget *parent = nullptr);

  /* Value Management Accessors */
  [[nodiscard]] float GetCurrentValue() const;

  /* Value Management Mutators */
  void Configure(float value, float min_value, float max_value, float step_size);

 signals:
  void CurrentValueChanged(float value);

 protected:
  /* Setup */
  QWidget *CreateContentWidget(int width, int height) override;
  void SetupContentConnections() override;

 private:
  ValueControllerFloat *valcontroll_ = nullptr;
};

/* PIValueControllerInt */
class PIValueControllerInt : public PIBase {
  Q_OBJECT

 public:
  explicit PIValueControllerInt(const QString &name, int width, int height,
                                Qt::Orientation orientation,
                                QWidget *parent = nullptr);

  /* Value Management Accessors */
  [[nodiscard]] int GetCurrentValue() const;

  /* Value Management Mutators */
  void Configure(int value, int min_value, int max_value, int step_size);
  void SetCurrentValue(int value);
  void SetRange(int min_value, int max_value);

 signals:
  void CurrentValueChanged(int value);

 protected:
  /* Setup */
  QWidget *CreateContentWidget(int width, int height) override;
  void SetupContentConnections() override;

 private:
  ValueControllerInt *valcontroll_ = nullptr;
};

/* PIComboBox */
class PIComboBox : public PIBase {
  Q_OBJECT
public:
  explicit PIComboBox(const QString &name, int width, int height,
                      Qt::Orientation orientation, QWidget *parent = nullptr);

  /* Value Management Accessors */

  /* Value Management Mutators */
  void AddItems(std::initializer_list<std::pair<QString, int>> items);
  void AddItem(const QString &icon_path, int value);

  void SetArrows(const QString &up_icon_path, const QString &down_icon_path);

signals:
  /* Signals */
  void CurrentIndexChanged(int index);

protected:
  /* Setup */
  QWidget *CreateContentWidget(int width, int height) override;
  void SetupContentConnections() override;

private:
  CustomComboBox *combo_box_;
};

/* Value Management Mutators */
// template <typename... Args>
// void PIComboBox::AddItems(Args&&... args) {
//   combo_box_->AddItems(std::forward<Args>(args)...);
// }
// Value Management Mutators
//// PIComboBox

/* PIColorPicker */
class PIColorPicker : public PIBase {
  Q_OBJECT
public:
  explicit PIColorPicker(const QString &name, int width, int height,
                         Qt::Orientation orientation,
                         QWidget *parent = nullptr);
  /* Value Management Accessors */
  /* Value Management Mutators */

signals:
  /* Signals */
  void ColorChanged(const QColor &color);

protected:
  /* Setup */
  QWidget *CreateContentWidget(int width, int height) override;
  void SetupContentConnections() override;

private:
  /* Fields */
  ColorPicker *color_picker_;
};
//// PIColorPicker

/* PIDoubleButton */
class PIDoubleButton : public PIBase {
  Q_OBJECT

public:
  explicit PIDoubleButton(const QString &name, int width, int height,
                          const QString &left_text, const QString &right_text,
                          bool is_exclusive, QWidget *parent = nullptr);

  /* Value Management Accessors */
  /* Value Management Mutators */

signals:
  /* Signals for ExclusiveDoubleButton */
  void ButtonToggled(ButtonSide side);
  /* Signals for IndependentDoubleButton */
  void ButtonClicked(ButtonSide side);

protected:
  /* Setup */
  QWidget *CreateContentWidget(int width, int height) override;
  void SetupContentConnections() override;

private:
  /* Fields */
  DoubleButtonBase *double_button_;
  bool is_exclusive_;
  QString left_text_;
  QString right_text_;
};
//// PIDoubleButton

/* PIFileManagement */
class PIFileManagement : public PIBase {
  Q_OBJECT

public:
  explicit PIFileManagement(const QString &name, int width, int height,
                            const QString &button_text,
                            const QString &label_text,
                            QWidget *parent = nullptr);

  /* Value Management Accessors */
  /* Value Management Mutators */

  // TODO: Fix signals
signals:
  /* Signals */
  void FileSelected(const QString &filePath);

protected:
  /* Setup */
  QWidget *CreateContentWidget(int width, int height) override;
  void SetupContentConnections() override;

private:
  /* Fields */
  FileDialogPanel *file_panel_;
  QString button_text_;
  QString label_text_;
};
//// PIFileManagement

} // namespace s21

#endif // PANEL_ITEMS_H_
