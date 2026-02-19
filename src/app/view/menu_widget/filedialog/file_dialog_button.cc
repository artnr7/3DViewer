#include "file_dialog_button.h"

#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>

namespace s21 {

FileDialogButton::FileDialogButton(int width, int height, const QString& text,
                                   QWidget* parent)
    : QPushButton(text, parent) {
  setFixedSize(width, height);
  SetupStyle();
  SetupConnection();
}

/* File Management Accessors */
QString FileDialogButton::GetSelectedFile() const { return current_file_; }
// File Management Accessors

/* UI Setup & Connections */
void FileDialogButton::SetupStyle() {
  setStyleSheet(QString(R"(
    QPushButton {
        background-color: %1;
        color: %2;
        border: %3px solid %4;
        font-size: %5px;
        border-radius: %6px;
    }
    QPushButton:hover {
        background-color: %7;
        border: %3px solid %8;
    }
    QPushButton:pressed {
        background-color: %9;
    }
  )")
                    .arg(style_button_.background_color)
                    .arg(style_button_.text_color)
                    .arg(style_button_.text_border_size)
                    .arg(style_button_.border_color)
                    .arg(style_button_.font_size)
                    .arg(style_button_.border_radius)
                    .arg(style_button_.hover_color)
                    .arg(style_button_.hover_border_color)
                    .arg(style_button_.pressed_color));
}

void FileDialogButton::SetupConnection() {
  connect(this, &QPushButton::clicked, this, &FileDialogButton::HandleClick);
}

QString FileDialogButton::SetupDialogStyle() {
  return QString(R"(
    QFileDialog {
      background-color: %1;
      color: %2;
    }
    QFileDialog QLabel {
        color: %2;
    }
    QFileDialog QTreeView,
    QFileDialog QListView {
      background-color: %3;
      color: %2;
      border: %13px solid %4;
      selection-background-color: %5;
    }
    QFileDialog QLineEdit {
      background-color: %3;
      color: %2;
      border: %13px solid %4;
      border-radius: %6px;
      padding: %7px;
    }
    QFileDialog QPushButton {
      background-color: %3;
      color: %2;
      border: %13px solid %4;
      border-radius: %8px;
      padding: %9px %10px;
      min-width: %11px;
    }
    QFileDialog QPushButton:hover {
        background-color: %12;
    }
  )")
      .arg(style_dialog_.background_color)
      .arg(style_dialog_.text_color)
      .arg(style_dialog_.widget_background)
      .arg(style_dialog_.border_color)
      .arg(style_dialog_.selection_color)
      .arg(style_dialog_.border_radius)
      .arg(style_dialog_.padding)
      .arg(style_dialog_.button_border_radius)
      .arg(style_dialog_.button_padding_vertical)
      .arg(style_dialog_.button_padding_horizontal)
      .arg(style_dialog_.min_button_width)
      .arg(style_dialog_.hover_color)
      .arg(style_dialog_.text_border_size);
}
// UI Setup & Connections

/* Dialog Management */
QString FileDialogButton::OpenFileDialog() {
  QFileDialog dialog(parentWidget());

  dialog.setStyleSheet(SetupDialogStyle());

  dialog.setWindowTitle(style_dialog_.dialog_title);
  dialog.setNameFilter(style_dialog_.filter);
  dialog.setDirectory(QDir::homePath());
  dialog.setFileMode(QFileDialog::ExistingFile);

  QString file = QString();
  if (dialog.exec() == QDialog::Accepted) {
    file = dialog.selectedFiles().first();
  }

  return file;
}
// Dialog Management

/* Slot Management */
void FileDialogButton::HandleClick() {
  QString file_path = OpenFileDialog();

  if (!file_path.isEmpty()) {
    current_file_ = file_path;

    QString file_name = QFileInfo(current_file_).fileName();

    emit FileSelected(current_file_);
  }
}
// Slot Management

}  // namespace s21
