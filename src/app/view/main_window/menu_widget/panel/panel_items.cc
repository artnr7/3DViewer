#include "panel_items.h"

#include "buttons/exclusive_double_button.h"
#include "buttons/independent_double_button.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDir>

namespace s21 {

//** PanelItem **//

PanelItem::PanelItem(const QString& name, QWidget* parent)
  : QWidget(parent),
  style_{} {
  if (!name.isEmpty()) {
    name_label_ = new QLabel(name, this);
    name_label_->setStyleSheet(CreateLabelStyle(style_.default_font_size));
  }
}

/* Setup Label */
QString PanelItem::CreateLabelStyle(int font_size) const {
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
// Setup Label

//// PanelItem

//** PanelItemValueController **//

PanelItemValueController::PanelItemValueController(const QString& name,
                                                   int width, int height,
                                                   Qt::Orientation orientation,
                                                   QWidget* parent)
    : PanelItem(name, parent),
    orientation_(orientation) {

  container_ = new QWidget(this);
  container_->setFixedSize(width, height);
  /* FOR DEBUG */
  container_->setStyleSheet(R"(
    border: 1px solid white;
    background-color: transparent;
  )");
  // FOR DEBUG

  int font_size = height * style_.font_size_ratio;
  name_label_->setStyleSheet(CreateLabelStyle(font_size));

  if (orientation == Qt::Vertical) {
    SetupVerticalLayout(width, height);
  } else {
    SetupHorizontalLayout();
  }

  QLayout* main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(style_.zero_margins);
  main_layout->addWidget(container_);

  SetupConnections();
}

/* Value Management Accessors */
int PanelItemValueController::GetCurrentValue() const {
  return valcontroll_->GetCurrentValue();
}
// Value Management Accessors

/* Value Management Mutators */
void PanelItemValueController::SetCurrentValue(int value) {
  valcontroll_->SetCurrentValue(value);
}

void PanelItemValueController::SetRange(int min_value, int max_value) {
  valcontroll_->SetMinValue(min_value);
  valcontroll_->SetMaxValue(max_value);
}
// Value Management Mutators

/* Setup */
void PanelItemValueController::SetupVerticalLayout(int width, int height) {
  QVBoxLayout* layout = new QVBoxLayout(container_);
  layout->setContentsMargins(style_.zero_margins);
  layout->setSpacing(style_.zero_spacing);

  int controller_height = height * style_.controller_hight_ratio;
  int label_height = height * style_.label_hight_ratio;

  valcontroll_ = new ValueController(width, controller_height);

  name_label_->setAlignment(Qt::AlignCenter);
  name_label_->setFixedSize(width, label_height);

  layout->addWidget(valcontroll_);
  layout->addWidget(name_label_);
}

void PanelItemValueController::SetupHorizontalLayout() {
  QHBoxLayout* layout = new QHBoxLayout(container_);
  layout->addWidget(name_label_);

  valcontroll_ = new ValueController();
  layout->addWidget(valcontroll_);
}


void PanelItemValueController::SetupConnections() {
  connect(valcontroll_, &ValueController::CurrentValueChanged, this,
          &PanelItemValueController::CurrentValueChanged);
}
// Setup

//// PanelItemValueController

PanelItemDoubleButton::PanelItemDoubleButton(int width, int height,
                                             bool is_exclusive,
                                             QWidget* parent)
  : PanelItem("", parent) {

  QWidget* container = new QWidget(this);
  container->setFixedSize(width, height);

  QVBoxLayout* layout = new QVBoxLayout(container);
  if (is_exclusive) {
    dbutton_ = new ExclusiveDoubleButton("perspective", "orthography", width, height*0.7, this);
  } else {
    dbutton_ = new IndependentDoubleButton("GIF", "Image", width, height*0.7, this);
  }

  layout->addWidget(dbutton_);

  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);

  container->setStyleSheet(R"(
    border: 1px solid white;
    background-color: transparent;
  )");

  QLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->addWidget(container);
}


PanelItemFileManagment::PanelItemFileManagment(int width, int height,
                                                const QString& button_text,
                                                                        const QString& label_text,
                                               QWidget* parent)
  : PanelItem("", parent) {

  QWidget* debug_container = new QWidget(this);
  debug_container->setFixedSize(width, height);
  // debug_container->setStyleSheet(R"(
  //   border: 2px solid white;
  //   background-color: transparent;
  // )");

  FileDialogPanel* file_panel_ = new FileDialogPanel(width, height,
                                                   button_text,
                                                   label_text,
                                                   debug_container);

  QLayout* main_layout = new QVBoxLayout(this);
  main_layout->setContentsMargins(0, 0, 0, 0);
  main_layout->addWidget(debug_container);
}

PanelItemComboBox::PanelItemComboBox(const QString& name, int width, int height,
                                               QWidget* parent)
  : PanelItem(name, parent) {

  int font_size = height * 0.3;
  QWidget* container = new QWidget(this);
  container->setFixedSize(width, height);

  name_label_->setStyleSheet(QString(R"(
    QLabel {
      border: none;
      color: white;
      font-size: %1px;
      font-weight: bold;
    }
  )").arg(font_size));

  QVBoxLayout* layout = new QVBoxLayout(container);
  combo_box_ = new CustomComboBox(width, height*0.7);
  // combo_box_->SetArrows("open_arrow.png", "close_arrow.png");
  // combo_box_->AddItems("square.png", "circle.png");

  name_label_->setAlignment(Qt::AlignCenter);
  name_label_->setFixedWidth(width);
  layout->addWidget(combo_box_);
  layout->addWidget(name_label_);

  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);

  QLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(0, 0, 0, 0);

  // container->setStyleSheet(R"(
  //   border: 1px solid white;
  //   background-color: transparent;
  // )");
  mainLayout->addWidget(container);
}

PanelItemColorPicker::PanelItemColorPicker(const QString& name, int width, int height,
                                               QWidget* parent)
  : PanelItem(name, parent) {

  int font_size = height * 0.3;
  QWidget* container = new QWidget(this);
  container->setFixedSize(width, height);

  name_label_->setStyleSheet(QString(R"(
    QLabel {
      border: none;
      color: white;
      font-size: %1px;
      font-weight: bold;
    }
  )").arg(font_size));

  QVBoxLayout* layout = new QVBoxLayout(container);
  color_picker_ = new ColorPicker(width, height*0.7);
  // combo_box_->SetArrows("open_arrow.png", "close_arrow.png");
  // combo_box_->AddItems("square.png", "circle.png");

  name_label_->setAlignment(Qt::AlignCenter);
  name_label_->setFixedWidth(width);
  layout->addWidget(color_picker_);
  layout->addWidget(name_label_);

  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);

  QLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(0, 0, 0, 0);

  // container->setStyleSheet(R"(
  //   border: 1px solid white;
  //   background-color: transparent;
  // )");
  mainLayout->addWidget(container);
}

} // namespace s21
