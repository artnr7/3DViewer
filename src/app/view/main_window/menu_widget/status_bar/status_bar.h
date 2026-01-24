#ifndef STATUS_BAR_H_
#define STATUS_BAR_H_

#include <QLabel>
#include <QStackedWidget>
#include <QVariantAnimation>
#include <QWidget>

#include "style_configs/status_bar_style.h"

namespace s21 {

class StatusBar : public QWidget {
  Q_OBJECT

 public:
  StatusBar(int width, int height, QWidget* parrent = nullptr);

 public slots:
  /* Slots */
  void UpdateState(int vertices_count, int edges_count);
  void ShowError(const QString& msg);

 private:
  /* Setup */
  void SetupStyles();
  QString GetLabelStyle(const QString& color) const;
  void SetupAnimation();

  /* Value Management */
  QString GetValueLabel(const QString& label, int value);

  /* Fields */
  StatusBarStyle style_;

  QStackedWidget* stack_;
  QLabel *vertices_label_, *edges_label_, *error_label_;
  QWidget *status_page_, *error_page_;
  QVariantAnimation* blink_anim_;
};

}  // namespace s21

#endif  // STATUS_BAR_H_
