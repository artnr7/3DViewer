#ifndef COLOR_SELECT_DIALOG_H_
#define COLOR_SELECT_DIALOG_H_

#include <QColor>
#include <QDialog>
#include <QMargins>
#include <QPushButton>

#include "brightness_slider.h"
#include "color_wheel.h"
#include "panel/panel_items.h"
#include "style_configs/color_select_dialog_style.h"

namespace s21 {

class ColorSelectionDialog : public QDialog {
  Q_OBJECT

 public:
  explicit ColorSelectionDialog(int widht, int height,
                                const QColor& initialColor,
                                QWidget* parent = nullptr);

 signals:
  void ColorChanged(const QColor& color);

 private:
  /* Setup */
  void SetupUI();
  void SetupStyles();
  void SetupConnections();
  void SetupRGBControls(int width, int height);

  /* Element Management */
  void AddColorSelectionArea(int wheel_width, int slider_width,
                             int slider_height);
  void AddCloseButton(int button_size);
  QPushButton* CreateCloseButton(int width, int height);
  void AddRGBLabel();
  void AddRGBControllers(int width, int height);

  /* Event Handlers */
  void OnColorWheelChanged(const QColor& color);
  void OnRGBValueChanged();

  /* Fields */
  ColorSelectionDialogStyle style_;
  QColor selected_color_;

  QVBoxLayout* main_layout_;
  int width_, height_;

  ColorWheel* color_wheel_;
  BrightnessSlider* brightness_slider_;

  PIValueController* red_controller_;
  PIValueController* green_controller_;
  PIValueController* blue_controller_;
};

}  // namespace s21

#endif  // COLOR_SELECT_DIALOG_H_
