#include "file_dialog_panel.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QApplication>
#include <QClipboard>
#include <QMouseEvent>
#include <QTimer>

namespace s21 {

FileDialogPanel::FileDialogPanel(int width, int height,
                               const QString& button_text,
                               const QString& label_text,
                               QWidget* parent)
  : QWidget(parent),
    style_{},
    width_(width),
    height_(height),
    button_text_(button_text),
    label_text_(label_text),
    current_file_("") {

  SetupUI();
  SetupStyles();
  file_name_label_->installEventFilter(this);
}

/* File Management Accessors */
QString FileDialogPanel::GetSelectedFile() const {
  return current_file_;
}
// File Management Accessors

/* Event Handlers */
bool FileDialogPanel::eventFilter(QObject* obj, QEvent* event) {
  if (obj != file_name_label_ || event->type() != QEvent::MouseButtonDblClick) {
    return QWidget::eventFilter(obj, event);
  }

  if (!current_file_.isEmpty()) {
    QApplication::clipboard()->setText(current_file_);
    QString original_text = file_name_label_->text();
    file_name_label_->setText(style_.copy_message_text);

    QTimer::singleShot(style_.copy_message_duration, [this, original_text]() {
        file_name_label_->setText(original_text);
    });
  }
  return true;
}
// Event Handlers

/* Slot Management */
void FileDialogPanel::OnFileSelected(const QString& file_path) {
  current_file_ = file_path;
  QString file_name = QFileInfo(file_path).fileName();

  int available_width = file_name_label_->width();
  QFontMetrics metrics(file_name_label_->font());

  if (metrics.horizontalAdvance(file_name) > available_width) {
    file_name_label_->setText(metrics.elidedText(file_name, Qt::ElideRight, available_width));
  } else {
    file_name_label_->setText(file_name);
  }

  file_name_label_->setToolTip(SetupToolTipText(current_file_));

  emit FileSelected(current_file_);
}
// Slot Management

/* UI Setup */
void FileDialogPanel::SetupUI() {
  QHBoxLayout* main_layout = new QHBoxLayout(this);
  main_layout->setContentsMargins(style_.zero_margins);
  main_layout->setSpacing(style_.zero_spacing);

  int button_width = width_ * style_.button_width_percent;
  int label_width = width_ * style_.label_width_percent;
  int text_container_width = width_ * style_.text_container_width_percent;

  button_ = new FileDialogButton(button_width, height_, button_text_, this);

  text_label_ = new QLabel(label_text_, this);
  text_label_->setFixedSize(label_width, height_);
  text_label_->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  text_label_->setMargin(style_.label_margin);

  QWidget* text_container = new QWidget(this);
  text_container->setFixedSize(text_container_width, height_);

  QHBoxLayout* text_container_layout = new QHBoxLayout(text_container);
  text_container_layout->setContentsMargins(style_.container_left_margin, 0, style_.container_right_margin, 0);
  text_container_layout->setSpacing(style_.zero_spacing);

  file_name_label_ = new QLabel(style_.default_file_name_label_text, text_container);
  file_name_label_->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  text_container_layout->addWidget(file_name_label_);

  main_layout->addWidget(button_);
  main_layout->addWidget(text_label_);
  main_layout->addWidget(text_container);

  QVBoxLayout* widget_layout = new QVBoxLayout(this);
  widget_layout->setContentsMargins(style_.zero_margins);
  widget_layout->addWidget(this);

  connect(button_, &FileDialogButton::FileSelected,
          this, &FileDialogPanel::OnFileSelected);
}

void FileDialogPanel::SetupStyles() {
  text_label_->setStyleSheet(QString(R"(
    QLabel {
      background-color: transparent;
      color: %1;
      border: none;
      font-size: %2px;
    }
  )")
  .arg(style_.text_color)
  .arg(style_.label_font_size));

  QWidget* text_container = file_name_label_->parentWidget();
  text_container->setStyleSheet(QString(R"(
    QWidget {
      background-color: %1;
      border: %2px solid %3;
      border-radius: %4px;
    }
  )")
  .arg(style_.background_color)
  .arg(style_.text_container_border_size)
  .arg(style_.border_color)
  .arg(style_.border_radius));

  file_name_label_->setStyleSheet(QString(R"(
    QLabel {
      background-color: transparent;
      color: %1;
      border: none;
      font-size: %2px;
    }
    QLabel:hover {
      background-color: %3;
    }
  )")
  .arg(style_.text_color)
  .arg(style_.file_name_font_size)
  .arg(style_.hover_color));
}

QString FileDialogPanel::SetupToolTipText(const QString& file_path) {
  return QString(R"(
    <div style='
    background-color: %1;
    color: %2;
    border: %3px solid %4;
    border-radius: %5px;
    padding: %6px;
    font-size: %7px;'>
    <b>Double-click to copy</b><br>
    %8
    </div>
  )").arg(style_.tooltip_background)
     .arg(style_.text_color)
     .arg(style_.tooltip_border_size)
     .arg(style_.tooltip_border_color)
     .arg(style_.tooltip_border_radius)
     .arg(style_.tooltip_padding)
     .arg(style_.tooltip_font_size)
     .arg(file_path);
}
// UI Setup

} // namespace s21
