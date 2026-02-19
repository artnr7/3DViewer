#ifndef COLOR_WHEEL_H_
#define COLOR_WHEEL_H_

#include <QMouseEvent>
#include <QWidget>

#include "style_configs/color_wheel_style.h"

namespace s21 {

class ColorWheel : public QWidget {
  Q_OBJECT

 public:
  explicit ColorWheel(int size, QWidget* parent = nullptr);

  /* Color Management Mutators */
  void SetColor(const QColor& color);

 public slots:
  void SetBrightness(int brightness);

 signals:
  void ColorChanged(const QColor& color);

 protected:
  /* Event Handlers */
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;

 private:
  void MouseEvent(QMouseEvent* event);

  /* Color Management */
  QColor CoordToColor(int dx, int dy, int radius, int brightness) const;
  QColor GetColorAtPosition(const QPoint& pos) const;

  /* Wheel Management */
  void GenerateColorWheel();
  void ApplyBrightnessToWheel();

  /* State Management */
  void UpdatePositionFromColor(const QColor& color);

  /* Fields */
  ColorWheelStyle style_;

  QPixmap color_wheel_;
  QPoint current_pos_;
  int wheel_size_;
  int wheel_radius_;
  int brightness_;
  QColor current_color_;

  QPixmap base_color_wheel_;
  bool base_wheel_generated_ = false;
};

}  // namespace s21

#endif  // COLOR_WHEEL_H_
