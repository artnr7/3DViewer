#include "color_select_dialog.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>

#define CAST_INT(value) static_cast<int>(value)

namespace s21 {

ColorSelectionDialog::ColorSelectionDialog(int width, int height,
                                           const QColor& initial_color,
                                           QWidget* parent)
    : QDialog(parent),
      style_{},
      selected_color_(initial_color),
      main_layout_(new QVBoxLayout(this)),
      width_(width),
      height_(height),
      color_wheel_(nullptr),
      brightness_slider_(nullptr),
      red_controller_(nullptr),
      green_controller_(nullptr),
      blue_controller_(nullptr) {
  SetupUI();
  SetupStyles();
  SetupConnections();
}

/* Setup */
void ColorSelectionDialog::SetupUI() {
  setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
  setFixedSize(width_, height_);

  /* Calc sizes */
  int available_width = width_ - 2 * style_.dialog_margin;
  int available_height = height_ - 2 * style_.dialog_margin;

  int wheel_width = CAST_INT(available_width * style_.wheel_size_percent);
  int slider_width = CAST_INT(available_width * style_.slider_width_percent);
  int slider_height = CAST_INT(available_width * style_.slider_height_percent);

  int total_spacing_height = 2 * style_.dialog_spacing;
  int available_height_without_wheel_and_spacing =
      available_height - wheel_width - total_spacing_height;
  int close_button_size =
      CAST_INT(available_height_without_wheel_and_spacing *
               style_.close_button_remaining_height_percent);

  int rgb_controller_height =
      CAST_INT(available_height_without_wheel_and_spacing *
               style_.rgb_controller_remaining_height_percent);
  int rgb_controller_width = CAST_INT(available_width);
  // Calc sizes

  main_layout_->setContentsMargins(style_.dialog_margin, style_.dialog_margin,
                                   style_.dialog_margin, style_.dialog_margin);
  main_layout_->setSpacing(style_.zero_spacing);

  AddCloseButton(close_button_size);
  AddColorSelectionArea(wheel_width, slider_width, slider_height);
  SetupRGBControls(rgb_controller_width, rgb_controller_height);

  main_layout_->addStretch();
}

void ColorSelectionDialog::SetupStyles() {
  setStyleSheet(QString(R"(
    QDialog {
      background-color: %1;
      border: %2px solid %3;
      border-radius: %4px;
    }
  )")
                    .arg(style_.background_color)
                    .arg(style_.border_width)
                    .arg(style_.border_color)
                    .arg(style_.border_radius));
}

void ColorSelectionDialog::SetupConnections() {
  connect(color_wheel_, &ColorWheel::ColorChanged, this,
          &ColorSelectionDialog::OnColorWheelChanged);

  connect(brightness_slider_, &BrightnessSlider::BrightnessChanged,
          color_wheel_, &ColorWheel::SetBrightness);

  connect(red_controller_, &PIValueController::CurrentValueChanged, this,
          [this](int value) { OnRGBValueChanged(); });
  connect(green_controller_, &PIValueController::CurrentValueChanged, this,
          [this](int value) { OnRGBValueChanged(); });
  connect(blue_controller_, &PIValueController::CurrentValueChanged, this,
          [this](int value) { OnRGBValueChanged(); });
}

void ColorSelectionDialog::SetupRGBControls(int width, int height) {
  /* Calc sizes */
  int text_height = CAST_INT(height * style_.text_height_percent);
  int controllers_height = height - text_height - style_.dialog_spacing;
  int controller_width = (width - 2 * style_.spacing_between_controllers) / 3;
  // Calc sizes

  AddRGBLabel();
  AddRGBControllers(controller_width, controllers_height);
}
// Setup

/* Element Management */
void ColorSelectionDialog::AddColorSelectionArea(int wheel_width,
                                                 int slider_width,
                                                 int slider_height) {
  QHBoxLayout* color_layout = new QHBoxLayout();
  color_layout->setContentsMargins(style_.zero_margins);
  color_layout->setSpacing(style_.zero_spacing);

  color_wheel_ = new ColorWheel(wheel_width, this);
  color_wheel_->SetColor(selected_color_);

  brightness_slider_ = new BrightnessSlider(slider_width, slider_height, this);
  brightness_slider_->SetBrightness(selected_color_.value());

  color_layout->addWidget(color_wheel_);
  color_layout->addWidget(brightness_slider_);
  color_layout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

  main_layout_->addLayout(color_layout);
  main_layout_->addSpacing(style_.dialog_spacing);
}

void ColorSelectionDialog::AddCloseButton(int button_size) {
  QHBoxLayout* button_layout = new QHBoxLayout();
  button_layout->addStretch();
  button_layout->addWidget(CreateCloseButton(button_size, button_size));
  main_layout_->addLayout(button_layout);
  main_layout_->addSpacing(style_.dialog_spacing);
}

QPushButton* ColorSelectionDialog::CreateCloseButton(int width, int height) {
  QPushButton* close_button = new QPushButton("X", this);
  close_button->setFixedSize(width, height);
  QString cbutton_style =
      QString(R"(
      QPushButton {
        background-color: %1;
        color: %2;
        border: none;
        border-radius: %3px;
        font-size: %4px;
        font-weight: bold;
      }
      QPushButton:hover {
        background-color: %5;
      }
    )")
          .arg(style_.cbutton_normal_color, style_.cbutton_text_color)
          .arg(style_.cbutton_border_radius)
          .arg(style_.cbutton_font_size)
          .arg(style_.cbutton_hover_color);
  close_button->setStyleSheet(cbutton_style);

  connect(close_button, &QPushButton::clicked, this, &QDialog::reject);
  return close_button;
}

void ColorSelectionDialog::AddRGBLabel() {
  QLabel* rgb_label = new QLabel(style_.label_text);
  rgb_label->setStyleSheet(QString(R"(
    QLabel {
      background-color: transparent;
      border: none;
      color: %1;
      font-size: %2px;
      font-weight: %3;
    }
  )")
                               .arg(style_.label_color)
                               .arg(style_.label_font_size)
                               .arg(style_.label_font_weight));

  QHBoxLayout* label_layout = new QHBoxLayout();
  label_layout->setContentsMargins(style_.zero_margins);
  label_layout->setSpacing(style_.zero_spacing);
  label_layout->addWidget(rgb_label);
  label_layout->addStretch();

  main_layout_->addLayout(label_layout);
  main_layout_->addSpacing(style_.dialog_spacing);
}

void ColorSelectionDialog::AddRGBControllers(int width, int height) {
  auto CreateController = [this, width, height](const QString& label,
                                                int value) {
    PIValueController* controller =
        new PIValueController(label, width, height, Qt::Vertical, this);
    controller->SetRange(style_.min_rgb_value, style_.max_rgb_value);
    controller->SetCurrentValue(value);
    return controller;
  };

  red_controller_ = CreateController("R", selected_color_.red());
  green_controller_ = CreateController("G", selected_color_.green());
  blue_controller_ = CreateController("B", selected_color_.blue());

  QHBoxLayout* rgb_layout = new QHBoxLayout();
  rgb_layout->setAlignment(Qt::AlignTop);
  rgb_layout->setSpacing(style_.spacing_between_controllers);
  rgb_layout->setContentsMargins(style_.zero_margins);

  rgb_layout->addWidget(red_controller_);
  rgb_layout->addWidget(green_controller_);
  rgb_layout->addWidget(blue_controller_);

  main_layout_->addLayout(rgb_layout);
}

void ColorSelectionDialog::OnColorWheelChanged(const QColor& color) {
  selected_color_ = color;

  red_controller_->blockSignals(true);
  green_controller_->blockSignals(true);
  blue_controller_->blockSignals(true);

  red_controller_->SetCurrentValue(color.red());
  green_controller_->SetCurrentValue(color.green());
  blue_controller_->SetCurrentValue(color.blue());

  red_controller_->blockSignals(false);
  green_controller_->blockSignals(false);
  blue_controller_->blockSignals(false);

  brightness_slider_->SetBrightness(color.value());

  emit ColorChanged(selected_color_);
}

void ColorSelectionDialog::OnRGBValueChanged() {
  QColor new_color(red_controller_->GetCurrentValue(),
                   green_controller_->GetCurrentValue(),
                   blue_controller_->GetCurrentValue());

  if (new_color.isValid() && new_color != selected_color_) {
    selected_color_ = new_color;

    color_wheel_->SetColor(selected_color_);

    brightness_slider_->SetBrightness(selected_color_.value());

    emit ColorChanged(selected_color_);
  }
}

}  // namespace s21
