#include <QHBoxLayout>

#include "status_bar.h"

namespace s21 {

StatusBar::StatusBar(int width, int height, QWidget* parrent)
    : QWidget(parrent), style_{} {
  setFixedSize(width, height);

  QHBoxLayout* main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(style_.zero_margins);
  stack_ = new QStackedWidget(this);

  /* Statistics page */
  status_page_ = new QWidget();
  status_page_->setContentsMargins(style_.statistics_space, style_.zero_space, style_.statistics_space, style_.zero_space);

  vertices_label_ =
      new QLabel(GetValueLabel(style_.vertices_label, style_.default_value), status_page_);
  edges_label_ =
      new QLabel(GetValueLabel(style_.edges_label, style_.default_value), status_page_);

  QHBoxLayout* status_layout = new QHBoxLayout(status_page_);
  status_layout->addWidget(vertices_label_, style_.stretch_factor);
  status_layout->addWidget(edges_label_, style_.stretch_factor);
  // Statistics page

  /* Errors page */
  error_page_ = new QWidget();
  QHBoxLayout* error_layout = new QHBoxLayout(error_page_);

  error_label_ = new QLabel(error_page_);
  error_layout->addWidget(error_label_);
  error_layout->addStretch();
  // Errors page

  stack_->addWidget(status_page_);
  stack_->addWidget(error_page_);
  main_layout->addWidget(stack_);

  SetupStyles();
  SetupAnimation();
}

/* Setup */
void StatusBar::SetupStyles() {
  setStyleSheet(QString(R"(
    background-color: %1;
    border: %2;
  )")
  .arg(style_.background_color)
  .arg(style_.background_border));

  QString status_labels_style = GetLabelStyle(style_.status_text_color);
  vertices_label_->setStyleSheet(status_labels_style);
  edges_label_->setStyleSheet(status_labels_style);
  error_label_->setStyleSheet(GetLabelStyle(style_.error_text_color.name()));
}

QString StatusBar::GetLabelStyle(const QString& color) const {
  return QString(R"(
    color: %1;
    font-size: %2px;
    font-weight: %3;
  )")
      .arg(color)
      .arg(style_.text_font_size)
      .arg(style_.text_font_weight);
}

void StatusBar::SetupAnimation() {
  blink_anim_ = new QVariantAnimation(this);
  blink_anim_->setDuration(style_.animation_duration);
  blink_anim_->setStartValue(style_.animation_start_value);
  blink_anim_->setEndValue(style_.animation_end_value);
  blink_anim_->setEasingCurve(QEasingCurve::InOutQuad);
  blink_anim_->setLoopCount(style_.animation_loop_count);

  connect(blink_anim_, &QVariantAnimation::valueChanged,
          [this](const QVariant& value) {
            QColor new_color = style_.error_text_color;
            new_color.setAlphaF(value.toDouble());
            error_label_->setStyleSheet(
                GetLabelStyle(new_color.name(QColor::HexArgb)));
          });

  connect(blink_anim_, &QAbstractAnimation::finished, [this]() {
    error_label_->setStyleSheet(GetLabelStyle(style_.error_text_color.name()));
  });
}
// Setup

/* Slots */
void StatusBar::OnUpdateInfo(int vertices_count, int edges_count) {
  if (blink_anim_->state() == QAbstractAnimation::Running) {
    blink_anim_->stop();
  }
  vertices_label_->setText(GetValueLabel(style_.vertices_label, vertices_count));
  edges_label_->setText(GetValueLabel(style_.edges_label, edges_count));
  stack_->setCurrentIndex(style_.statistics_page_index);
}

void StatusBar::OnShowError(const QString& msg) {
  error_label_->setText(style_.error_label + ": " + msg);
  stack_->setCurrentIndex(style_.error_page_index);
  blink_anim_->start();
}
// Slots

/* Value Management */
QString StatusBar::GetValueLabel(const QString& label, int value) {
  QString formatted_value;

  if (value >= style_.millions_threshold) {
    double millions = value / static_cast<double>(style_.millions_threshold);
    formatted_value = QString("%1м").arg(millions, 0, 'f', style_.decimal_places);
  } else if (value >= style_.thousands_threshold) {
    double thousands = value / static_cast<double>(style_.thousands_threshold);
    formatted_value = QString("%1к").arg(thousands, 0, 'f', style_.decimal_places);
  } else {
    formatted_value = QString::number(value);
  }

  if (formatted_value.contains(style_.decimal_point)) {
    while (formatted_value.endsWith(style_.zero_char)) {
      formatted_value.chop(style_.chop_count);
    }
    if (formatted_value.endsWith(style_.decimal_point)) {
      formatted_value.chop(style_.chop_count);
    }
  }

  return QString("%1: %2").arg(label).arg(formatted_value);
}
// Value Management

}  // namespace s21
