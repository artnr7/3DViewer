#ifndef FILE_DIALOG_BUTTON_H_
#define FILE_DIALOG_BUTTON_H_

#include <QPushButton>
#include <QString>

#include "style_configs/file_dialog_button_style.h"

namespace s21 {

class FileDialogButton : public QPushButton {
  Q_OBJECT

 public:
  explicit FileDialogButton(int width, int height, const QString& name,
                            QWidget* parent = nullptr);

  /* File Management Accessors */
  QString GetSelectedFile() const;

 signals:
  void FileSelected(const QString& filePath);

 private:
  /* UI Setup & Connections */
  void SetupStyle();
  void SetupConnection();
  QString SetupDialogStyle();

  /* Dialog Management */
  QString OpenFileDialog();

 private slots:
  /* Slot Management */
  void HandleClick();

 private:
  /* Fields */
  FileDialogButtonStyle style_button_;
  FileDialogStyle style_dialog_;

  QString filter_;
  QString dialog_title_;
  QString current_file_;
};

}  // namespace s21

#endif  // FILE_DIALOG_BUTTON_H_
