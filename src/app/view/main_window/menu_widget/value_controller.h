#ifndef VALUE_CONTROLLER_H_
#define VALUE_CONTROLLER_H_

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

namespace s21 {

class ValueController : public QWidget {
  Q_OBJECT

 public:
  explicit ValueController(int width = 160, int height = 65,
                           QWidget* parent = nullptr);

  int GetCurrentValue() const;
  int GetMaxValue() const;
  int GetMinValue() const;

 private:
  void SetupUI();
  QString CreateContainerStyle(int border_radius) const;
  QString CreateButtonStyle(int font_size, int radius_tl, int radius_tr,
                            int radius_bl, int radius_br) const;
  QString CreateValueFieldStyle(int font_size) const;

  void SetupConntctions();

  bool MouseButtonDblClickEvent(QEvent* event);
  bool MouseButtonPressEvent(QEvent* event);
  bool MouseMoveEvent(QEvent* event);
  bool MouseButtonReleaseEvent();
  bool FocusOutEvent();
  bool KeyPressEvent(QEvent* event);
  void EditFinished();

  void SetCurrentValue(int value);
  void UpdateValueField();

 protected:
  bool eventFilter(QObject* obj, QEvent* event) override;

 signals:
  void CurrentValueChanged(int value);

 private:
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

  QSize widget_size_;
};

} // namespace s21

#endif  // VALUE_CONTROLLER_H
