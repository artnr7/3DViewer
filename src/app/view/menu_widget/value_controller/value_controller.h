#ifndef VALUE_CONTROLLER_H_
#define VALUE_CONTROLLER_H_

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "style_configs/value_controller_style.h"

namespace s21 {

class ValueController : public QWidget {
  Q_OBJECT

public:
  explicit ValueController(int width = 100, int height = 40,
                           QWidget *parent = nullptr);

  /* Value & Size Management Accessors */
  int GetCurrentValue() const;
  int GetWidth() const;
  int GetHeight() const;
  QSize GetSize() const;

  /* Value Management Mutators */
  void SetCurrentValue(float value);
  void SetMinValue(float value);
  void SetMaxValue(float value);
  void SetStepSize(float step_size);

signals:
  void CurrentValueChanged(float value);

private:
  /* Setup */
  void SetupUI();
  void SetupConnections();

  /* Style Management */
  QString CreateContainerStyle() const;
  QString CreateButtonStyle(int font_size, int radius_tl, int radius_tr,
                            int radius_bl, int radius_br) const;
  QString CreateValueFieldStyle(int font_size) const;

protected:
  /* Event Handlers */
  bool eventFilter(QObject *obj, QEvent *event) override;

private:
  /* Internal Helpers */
  bool MouseButtonDblClickEvent(QEvent *event);
  bool MouseButtonPressEvent(QEvent *event);
  bool MouseMoveEvent(QEvent *event);
  bool MouseButtonReleaseEvent();
  bool KeyPressEvent(QEvent *event);
  bool FocusOutEvent();
  void EditFinished();

  /* Value Management Update */
  void UpdateValueField();

public:
  ValueControllerStyle style_;

private:
  /* Fields */
  QSize widget_size_;

  float current_value_;
  float min_value_;
  float max_value_;
  float step_size_;
  float step_speed_;

  bool is_dragging_;
  QPoint drag_start_pos_;
  // sundaeka
  float drag_start_value_;

  QHBoxLayout *main_layout_;
  QPushButton *left_button_;
  QPushButton *right_button_;
  QLineEdit *value_field_;

  // sundaeka
  // Может быть можно сделать геттер, хз
  // public:
  // ValueControllerStyle style_;
};

} // namespace s21

#endif // VALUE_CONTROLLER_H_
