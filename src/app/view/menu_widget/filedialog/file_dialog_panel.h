#ifndef FILE_DIALOG_PANEL_H
#define FILE_DIALOG_PANEL_H

#include <QWidget>
#include <QLabel>

#include "file_dialog_button.h"
#include "style_configs/file_dialog_panel_style.h"

namespace s21 {

class FileDialogPanel : public QWidget {
  Q_OBJECT

public:
  explicit FileDialogPanel(int width, int height,
                          const QString& button_text,
                          const QString& label_text,
                          QWidget* parent = nullptr);

  /* File Management Accessors */
  QString GetSelectedFile() const;

 signals:
  void FileSelected(const QString& filePath);

protected:
  /* Event Handlers */
  bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
  /* Slot Management */
  void OnFileSelected(const QString& file_path);

private:
  /* UI Setup */
  void SetupUI();
  void SetupStyles();
  QString SetupToolTipText(const QString& file_path);

  /* Fields */
  FileDialogPanelStyle style_;

  int width_;
  int height_;
  QString button_text_;
  QString label_text_;

  QString current_file_;

  FileDialogButton* button_;
  QLabel* text_label_;
  QLabel* file_name_label_;
};

} // namespace s21

#endif // FILE_DIALOG_PANEL_H
