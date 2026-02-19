#ifndef COLOR_PICKER_H_
#define COLOR_PICKER_H_

#include <QColor>
#include <QWidget>

#include "style_configs/color_picker_style.h"

namespace s21 {

class ColorSelectionDialog;

class ColorPicker : public QWidget {
  Q_OBJECT

 public:
  explicit ColorPicker(int width, int height, QWidget* parent = nullptr);

  /* Color Managment Mutators */
  void SetColor(const QColor& color);

 signals:
  void ColorChanged(const QColor& color);

 protected:
  /* Event Handlers */
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;

 private:
  /* Fields */
  ColorPickerStyle style_;

  int width_;
  int height_;
};

}  // namespace s21

#endif  // COLOR_PICKER_H_
