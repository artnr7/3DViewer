#include "trash_button.h"

#include <QToolTip>
#include <QCoreApplication>
#include <QDir>

TrashButton::TrashButton(int width, int height, QWidget* parent)
    : style_{}, tooltip_text_(style_.tooltip_text), QPushButton(parent) {
  setFixedSize(width, height);
  SetupStyle();
  SetupTooltipStyle();
}

void TrashButton::AddIcon(const QString& icon_path) {
  if (icon_path.isEmpty()) {
    qWarning() << "Attempting to add empty icon path to TrashButton";
    return;
  }
  QString absolute_path = QDir::cleanPath(
    QCoreApplication::applicationDirPath() + "/../" + icon_path);
  int icon_size = qMin(width(), height()) - style_.padding;

  setIcon(QIcon(absolute_path));
  setIconSize(QSize(icon_size, icon_size));
}

void TrashButton::SetupStyle() {
  setStyleSheet(
    QString(R"(
      QPushButton {
        background-color: %1;
        border-radius: %2px;
      }
      QPushButton:hover {
        background-color: %3;
      }
      QPushButton:pressed {
        background-color: %4;
      }
      QPushButton:focus {
        outline: none;
    })")
    .arg(style_.background_color)
    .arg(style_.border_radius)
    .arg(style_.hover_color)
    .arg(style_.pressed_color));
}

void TrashButton::SetupTooltipStyle() {
  if (!tooltip_text_.isEmpty()) {
    setToolTip(tooltip_text_);

    QString tooltip_style = QString(R"(
      QToolTip {
        background-color: %1;
        color: %2;
        border: %3px solid %4;
        border-radius: %5px;
        padding: %6px;
        font-size: %7px;
      }
        )")
        .arg(style_.tooltip_background)
        .arg(style_.tooltip_text_color)
        .arg(style_.tooltip_border_size)
        .arg(style_.tooltip_border_color)
        .arg(style_.tooltip_border_radius)
        .arg(style_.tooltip_padding)
        .arg(style_.tooltip_font_size);

    setStyleSheet(styleSheet() + tooltip_style);
  }
}
