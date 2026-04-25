#ifndef TRASH_BUTTON_H_
#define TRASH_BUTTON_H_

#include <QPushButton>

#include "style_configs/trash_button_style.h"

class TrashButton : public QPushButton {
 public:
  explicit TrashButton(int width = 40, int height = 40,
                       QWidget* parent = nullptr);

  void AddIcon(const QString& icon_path);
  void SetTooltip(const QString& text);

  TrashButtonStyle style_;

 private:
  void SetupStyle();
  void SetupTooltipStyle();

  QString tooltip_text_;
};

#endif  // TRASH_BUTTON_H_