#ifndef DOUBLE_BUTTON_BASE_H_
#define DOUBLE_BUTTON_BASE_H_

#include <QButtonGroup>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

class DoubleButtonBase : public QWidget {
  Q_OBJECT
 public:
  explicit DoubleButtonBase(const QString& left_button_name,
                            const QString& right_button_name, int width,
                            int height, QWidget* parent = nullptr);

 private:
  virtual void SetupStyles();
  void SetupLayout();
  void SetupButtonSize();

 protected:
  QPushButton* left_button_;
  QPushButton* right_button_;

 private:
  QHBoxLayout* main_layout_;
  QSize widget_size_;
};

#endif  // DOUBLE_BUTTON_BASE_H_
