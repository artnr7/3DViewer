#ifndef BRIGHTNESS_SLIDER_H_
#define BRIGHTNESS_SLIDER_H_

#include <QWidget>

#include "style_configs/brightness_slider_style.h"

namespace s21 {

class BrightnessSlider : public QWidget {
  Q_OBJECT

 public:
  explicit BrightnessSlider(int widht, int height, QWidget* parent = nullptr);

 signals:
  void BrightnessChanged(int brightness);

 protected:
  /* Event Handlers */
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;

 private:
  /* Configure */
  void CalculateRanges();
  void GenerateBrightnessBar();

  /* Value Update */
  void UpdateBrightnessFromPos(int x);
  void UpdatePositionFromBrightness();
  int TransformValue(int value, int from_min, int from_max, int to_min,
                     int to_max);

 public:
  /* Brightness Managment Mutators*/
  void SetBrightness(int brightness);

  BrightnessSliderStyle style_;
  QPixmap brightness_bar_;

  int brightness_;
  int current_pos_;

  int bar_width_;
  int bar_height_;

  int slider_min_;
  int slider_max_;
  int slider_margin_;
  int slider_range_;
  int line_height_;
};

}  // namespace s21

#endif  // BRIGHTNESS_SLIDER_H_
