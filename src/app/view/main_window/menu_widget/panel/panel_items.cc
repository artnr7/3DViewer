#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDir>
#include <qnamespace.h>

#include "panel_items.h"
#include "buttons/exclusive_double_button.h"
#include "buttons/independent_double_button.h"

namespace s21 {

//** PI Base **//
PIBase::PIBase(const QString& name, QWidget* parent)
  : QWidget(parent),
  style_{} {
  if (!name.isEmpty()) {
    name_label_ = new QLabel(name, this);
  }
}

/* Setup */
void PIBase::Initialize(int width, int height, Qt::Orientation orientation) {
  /* FOR DEBUG */
  QWidget* container = new QWidget(this);
  container->setFixedSize(width, height);
  container->setStyleSheet(R"(
    border: 1px solid white;
    background-color: transparent;
  )");
  // FOR DEBUG

  int content_height = height * style_.buttons_hight_ratio;

  if (name_label_) {
    int font_size = height * style_.font_size_ratio;
    int label_height = height * style_.label_hight_ratio;
    name_label_->setStyleSheet(CreateLabelStyle(font_size));
    name_label_->setFixedSize(width, label_height);
    content_height = height * style_.controller_hight_ratio;
  }
  QWidget* content = CreateContentWidget(width, content_height);
  QBoxLayout* inner_layout;

  if (orientation == Qt::Vertical) {
    inner_layout = new QVBoxLayout(container);
    inner_layout->addWidget(content);
    if (name_label_) {
      name_label_->setAlignment(Qt::AlignCenter);
      inner_layout->addWidget(name_label_);
    }
  } else {
    inner_layout = new QVBoxLayout(container);
    if (name_label_) {
      inner_layout->addWidget(name_label_);
    }
    inner_layout->addWidget(content);
  }

  inner_layout->setContentsMargins(style_.zero_margins);
  inner_layout->setSpacing(style_.zero_spacing);

  QVBoxLayout* main_layout = new QVBoxLayout(this);
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
  )").arg(style_.border)
    .arg(style_.text_color)
    .arg(font_size)
    .arg(style_.font_weight);
}
// Setup
//// PIBase

/* PIValueController */
PIValueController::PIValueController(const QString& name,
                                                   int width, int height,
                                                   Qt::Orientation orientation, QWidget* parent)
  : PIBase(name, parent) {
    Initialize(width, height, orientation);
  }

/* Value Management Accessors */
int PIValueController::GetCurrentValue() const {
  return valcontroll_->GetCurrentValue();
}
// Value Management Accessors

/* Value Management Mutators */
void PIValueController::SetCurrentValue(int value) {
  valcontroll_->SetCurrentValue(value);
}

void PIValueController::SetRange(int min_value, int max_value) {
  valcontroll_->SetMinValue(min_value);
  valcontroll_->SetMaxValue(max_value);
}
// Value Management Mutators

/* Setup */
QWidget* PIValueController::CreateContentWidget(int width, int height) {
  valcontroll_ = new ValueController(width, height);
  return valcontroll_;
}

void PIValueController::SetupContentConnections() {
  connect(valcontroll_, &ValueController::CurrentValueChanged, this,
          &PIValueController::CurrentValueChanged);
}
// Setup
//// PIValueController

/* PIComboBox */
 PIComboBox::PIComboBox(const QString& name, int width, int height,
                                               QWidget* parent)
  : PIBase(name, parent) {
  Initialize(width, height);
}

/* Value Management Mutators */
void PIComboBox::SetArrows(const QString& up_icon_path,
                           const QString& down_icon_path) {
  combo_box_->SetArrows(up_icon_path, down_icon_path);
}
// Value Management Mutators

/* Setup */
QWidget* PIComboBox::CreateContentWidget(int width, int height) {
  combo_box_ = new CustomComboBox(width, height, this);
  return combo_box_;
}

// TODO: Fix signals
void PIComboBox::SetupContentConnections() {
}
// Setup
//// PIComboBox

/* PIColorPicker */
PIColorPicker::PIColorPicker(const QString& name,
                             int width, int height,
                             QWidget* parent)
  : PIBase(name, parent) {
  Initialize(width, height);
}

/* Setup */
QWidget* PIColorPicker::CreateContentWidget(int width, int height) {
  color_picker_ = new ColorPicker(width, height, this);
  return color_picker_;
}

// TODO: Fix signals
void PIColorPicker::SetupContentConnections() {
}
// Setup
//// PIColorPicker

/* PIDoubleButton */
PIDoubleButton::PIDoubleButton(int width, int height,
                               const QString& left_text,
                               const QString& right_text,
                               bool is_exclusive,
                               QWidget* parent)
  : PIBase("", parent)
  , is_exclusive_(is_exclusive)
  , left_text_(left_text)
  , right_text_(right_text) {

  Initialize(width, height);
}

/* Setup */
QWidget* PIDoubleButton::CreateContentWidget(int width, int height) {
  if (is_exclusive_) {
    double_button_ = new ExclusiveDoubleButton(left_text_, right_text_, width, height, this);
  } else {
    double_button_ = new IndependentDoubleButton(left_text_, right_text_, width, height, this);
  }

  return double_button_;
}

// TODO: Fix signals
void PIDoubleButton::SetupContentConnections() {
}
// Setup

//// PIDoubleButton

/* PIFileManagement */
PIFileManagement::PIFileManagement(int width, int height,
                                 const QString& button_text,
                                 const QString& label_text,
                                 QWidget* parent)
  : PIBase("", parent)
  , button_text_(button_text)
  , label_text_(label_text) {

  Initialize(width, height);
}

/* Setup */
QWidget* PIFileManagement::CreateContentWidget(int width, int height) {
  file_panel_ = new FileDialogPanel(width, height, button_text_, label_text_, this);

  return file_panel_;
}

// TODO: Fix signals
void PIFileManagement::SetupContentConnections() {
}
// Setup
//// PIFileManagement

} // namespace s21
