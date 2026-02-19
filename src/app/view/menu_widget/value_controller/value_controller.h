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
                           QWidget* parent = nullptr);

  /* Value & Size Management Accessors */
  int GetCurrentValue() const;
  int GetWidth() const;
  int GetHeight() const;
  QSize GetSize() const;

  /* Value Management Mutators */
  void SetCurrentValue(int value);
  void SetMinValue(int value);
  void SetMaxValue(int value);

 signals:
  void CurrentValueChanged(int value);

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
  bool eventFilter(QObject* obj, QEvent* event) override;

 private:
  /* Internal Helpers */
  bool MouseButtonDblClickEvent(QEvent* event);
  bool MouseButtonPressEvent(QEvent* event);
  bool MouseMoveEvent(QEvent* event);
  bool MouseButtonReleaseEvent();
  bool KeyPressEvent(QEvent* event);
  bool FocusOutEvent();
  void EditFinished();

  /* Value Management Update */
  void UpdateValueField();

 private:
  /* Fields */
  QSize widget_size_;

  ValueControllerStyle style_;

  int current_value_;
  int min_value_;
  int max_value_;
  int step_size_;
  int step_speed_;

  bool is_dragging_;
  QPoint drag_start_pos_;
  int drag_start_value_;

  QHBoxLayout* main_layout_;
  QPushButton* left_button_;
  QPushButton* right_button_;
  QLineEdit* value_field_;
};

}  // namespace s21

#endif  // VALUE_CONTROLLER_H_
