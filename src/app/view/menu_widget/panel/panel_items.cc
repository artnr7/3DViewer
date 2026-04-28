#include "panel_items.h"

#include <qnamespace.h>

#include <QDir>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <qobject.h>
#include <qsharedpointer.h>

#include "buttons/exclusive_double_button.h"
#include "buttons/independent_double_button.h"
#include "iostream"

namespace s21 {

/* PIBase */
PIBase::PIBase(const QString &name, Qt::Orientation orientation,
               QWidget *parent)
    : QWidget(parent), orientation_(orientation), style_{} {
  if (!name.isEmpty()) {
    name_label_ = new QLabel(name, this);
  }
}

/* Setup */
void PIBase::Initialize(int width, int height) {
  /* FOR DEBUG */
  int total_width = orientation_ == Qt::Horizontal ? 1.5 * width : width;

  setFixedSize(total_width, height);
  int content_height = height * style_.buttons_hight_ratio;

  if (name_label_) {
    int font_size = height * style_.font_size_ratio;
    name_label_->setStyleSheet(CreateLabelStyle(font_size));
    int label_height = height * style_.label_hight_ratio;
    content_height = height * style_.controller_hight_ratio;

    if (orientation_ == Qt::Horizontal) {
      name_label_->setFixedSize(0.5 * width, label_height);
    }
  }

  QWidget *container = new QWidget(this);
  container->setFixedSize(total_width, height);
  container->setStyleSheet(R"(
      border: 1px solid white;
      background-color: transparent;
    )");
  // FOR DEBUG

  QWidget *content = CreateContentWidget(width, content_height);

  QBoxLayout *inner_layout;

  if (orientation_ == Qt::Vertical) {
    inner_layout = new QVBoxLayout(container);
    inner_layout->addWidget(content);
    if (name_label_) {
      name_label_->setAlignment(Qt::AlignCenter);
      inner_layout->addWidget(name_label_);
    }
  } else {
    inner_layout = new QHBoxLayout(container);
    if (name_label_) {
      name_label_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
      inner_layout->addWidget(name_label_);
    }
    inner_layout->addWidget(content);
  }

  inner_layout->setContentsMargins(style_.zero_margins);
  inner_layout->setSpacing(style_.zero_spacing);

  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(style_.zero_margins);
  main_layout->addWidget(container);

  SetupContentConnections();
}

QString PIBase::CreateLabelStyle(int font_size) const {
  return QString(R"(
    QLabel {
      border: %1;
      color: %2;
      font-size: %3px;
      font-weight: %4;
      background-color: transparent;
    }
  )")
      .arg(style_.border)
      .arg(style_.text_color)
      .arg(font_size)
      .arg(style_.font_weight);
}
// Setup

Qt::Orientation PIBase::GetOrientation() { return orientation_; }

//// PIBase

/* PIValueControllerFloat */
PIValueControllerFloat::PIValueControllerFloat(const QString &name, int width,
                                               int height,
                                               Qt::Orientation orientation,
                                               QWidget *parent)
    : PIBase(name, orientation, parent) {
  Initialize(width, height);
}

/* Value Management Accessors */
float PIValueControllerFloat::GetCurrentValue() const {
  return valcontroll_->GetCurrentValue();
}

/* Value Management Mutators */
void PIValueControllerFloat::Configure(float value, float min_value, float max_value, float step_size) {
  valcontroll_->SetCurrentValue(value);
  valcontroll_->SetMinValue(min_value);
  valcontroll_->SetMaxValue(max_value);
  valcontroll_->SetStepSize(step_size);
}

void PIValueControllerFloat::SetCurrentValue(float value) {
  valcontroll_->SetCurrentValue(value);
}

/* Setup */
QWidget *PIValueControllerFloat::CreateContentWidget(int width, int height) {
  valcontroll_ = new ValueControllerFloat(width, height);
  return valcontroll_;
}

void PIValueControllerFloat::SetupContentConnections() {
  connect(valcontroll_, &ValueControllerFloat::CurrentValueChanged, this,
          &PIValueControllerFloat::CurrentValueChanged);
}
//// PIValueControllerFloat

/* PIValueControllerInt */
PIValueControllerInt::PIValueControllerInt(const QString &name, int width,
                                           int height,
                                           Qt::Orientation orientation,
                                           QWidget *parent)
    : PIBase(name, orientation, parent) {
  Initialize(width, height);
}

/* Value Management Accessors */
int PIValueControllerInt::GetCurrentValue() const {
  return valcontroll_->GetCurrentValue();
}

/* Value Management Mutators */
void PIValueControllerInt::Configure(int value, int min_value, int max_value, int step_size) {
  valcontroll_->SetCurrentValue(value);
  valcontroll_->SetMinValue(min_value);
  valcontroll_->SetMaxValue(max_value);
  valcontroll_->SetStepSize(step_size);
}

void PIValueControllerInt::SetCurrentValue(int value) {
  valcontroll_->SetCurrentValue(value);
}

void PIValueControllerInt::SetRange(int min_value, int max_value) {
  valcontroll_->SetMinValue(min_value);
  valcontroll_->SetMaxValue(max_value);
}

/* Setup */
QWidget *PIValueControllerInt::CreateContentWidget(int width, int height) {
  valcontroll_ = new ValueControllerInt(width, height);
  return valcontroll_;
}

void PIValueControllerInt::SetupContentConnections() {
  connect(valcontroll_, &ValueControllerInt::CurrentValueChanged, this,
          &PIValueControllerInt::CurrentValueChanged);
}
//// PIValueControllerInt

/* PIComboBox */
PIComboBox::PIComboBox(const QString &name, int width, int height,
                       Qt::Orientation orientation, QWidget *parent)
    : PIBase(name, orientation, parent) {
  Initialize(width, height);
}

/* Value Management Mutators */
void PIComboBox::AddItems(
    std::initializer_list<std::pair<QString, int>> items) {
  combo_box_->AddItems(items);
}

void PIComboBox::AddItem(const QString &icon_path, int value) {
  combo_box_->AddItem(icon_path, value);
}

void PIComboBox::SetArrows(const QString &up_icon_path,
                           const QString &down_icon_path) {
  combo_box_->SetArrows(up_icon_path, down_icon_path);
}
// Value Management Mutators

/* Setup */
QWidget *PIComboBox::CreateContentWidget(int width, int height) {
  combo_box_ = new CustomComboBox(width, height, this);
  return combo_box_;
}

void PIComboBox::SetupContentConnections() {
  connect(combo_box_, &CustomComboBox::CurrentIndexChanged, this,
          &PIComboBox::CurrentIndexChanged);
}

void PIComboBox::SetCurrentIndex(int index) {
  combo_box_->SetCurrentIndex(index);
}
// Setup
//// PIComboBox

/* PIColorPicker */
PIColorPicker::PIColorPicker(const QString &name, int width, int height,
                             Qt::Orientation orientation, QWidget *parent)
    : PIBase(name, orientation, parent) {
  Initialize(width, height);
}

/* Setup */
QWidget *PIColorPicker::CreateContentWidget(int width, int height) {
  color_picker_ = new ColorPicker(width, height, this);
  return color_picker_;
}

void PIColorPicker::SetupContentConnections() {
  connect(color_picker_, &ColorPicker::ColorChanged, this,
          &PIColorPicker::ColorChanged);
}

void PIColorPicker::SetColor(const QColor &color) {
  color_picker_->SetColor(color);
}
// Setup
//// PIColorPicker

/* PIDoubleButton */
PIDoubleButton::PIDoubleButton(const QString &name, int width, int height,
                               const QString &left_text,
                               const QString &right_text, bool is_exclusive,
                               QWidget *parent)
    : PIBase(name, Qt::Vertical, parent), is_exclusive_(is_exclusive),
      left_text_(left_text), right_text_(right_text) {
  Initialize(width, height);
}

/* Setup */
QWidget *PIDoubleButton::CreateContentWidget(int width, int height) {
  if (is_exclusive_) {
    double_button_ =
        new ExclusiveDoubleButton(left_text_, right_text_, width, height, this);
  } else {
    double_button_ = new IndependentDoubleButton(left_text_, right_text_, width,
                                                 height, this);
  }

  return double_button_;
}

void PIDoubleButton::SetupContentConnections() {
  if (is_exclusive_) {
    auto *exclusive_button =
        qobject_cast<ExclusiveDoubleButton *>(double_button_);
    connect(exclusive_button, &ExclusiveDoubleButton::ButtonToggled, this,
            &PIDoubleButton::ButtonToggled);
  } else {
    auto *independent_button =
        qobject_cast<IndependentDoubleButton *>(double_button_);
    connect(independent_button, &IndependentDoubleButton::ButtonClicked, this,
            &PIDoubleButton::ButtonClicked);
  }
}

void PIDoubleButton::SetButtonSide(ButtonSide side) {
  auto *exclusive_button =
      qobject_cast<ExclusiveDoubleButton *>(double_button_);
  if (exclusive_button) {
    exclusive_button->SetButtonSide(side);
  }
}
// Setup

//// PIDoubleButton

/* PIFileManagement */
PIFileManagement::PIFileManagement(const QString &name, int width, int height,
                                   const QString &button_text,
                                   const QString &label_text, QWidget *parent)
    : PIBase("", Qt::Vertical, parent), button_text_(button_text),
      label_text_(label_text) {
  Initialize(width, height);
}

/* Setup */
QWidget *PIFileManagement::CreateContentWidget(int width, int height) {
  file_panel_ =
      new FileDialogPanel(width, height, button_text_, label_text_, this);

  return file_panel_;
}

void PIFileManagement::SetupContentConnections() {
  connect(file_panel_, &FileDialogPanel::FileSelected, this,
          &PIFileManagement::FileSelected);
}

void PIFileManagement::SetFilename(const QString &filename) {
  file_panel_->SetFilename(filename);
}
// Setup
//// PIFileManagement

} // namespace s21
