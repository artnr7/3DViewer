#include "color_picker.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>

#include "color_select_dialog.h"

namespace s21 {

ColorPicker::ColorPicker(int widht, int height, QWidget* parent)
    : QWidget(parent), style_{}, width_(widht), height_(height) {
  setFixedSize(widht, height);
}

/* Event Handlers */
void ColorPicker::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  QRect outerRect(0, 0, width_, height_);
  painter.setBrush(style_.outer_border_color);
  painter.setPen(Qt::NoPen);
  painter.drawRoundedRect(outerRect, style_.outer_border_radius,
                          style_.outer_border_radius);

  QRect innerRect(style_.border_thickness, style_.border_thickness,
                  width_ - 2 * style_.border_thickness,
                  height_ - 2 * style_.border_thickness);

  painter.setBrush(style_.default_color);
  painter.setPen(Qt::NoPen);
  painter.drawRoundedRect(innerRect, style_.inner_border_radius,
                          style_.inner_border_radius);
}

void ColorPicker::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    ColorSelectionDialog dialog(style_.color_selection_dialog_width,
                                style_.color_selection_dialog_height,
                                style_.default_color, this);

    QPoint dialogPos = mapToGlobal(QPoint(0, 0));
    dialogPos.setY(dialogPos.y() - dialog.height() - style_.dialog_offset_y);
    dialog.move(dialogPos);

    connect(&dialog, &ColorSelectionDialog::ColorChanged,
            [this](const QColor& color) {
              style_.default_color = color;
              update();
              emit ColorChanged(style_.default_color);
            });
    dialog.exec();
  }
}
// Event Handlers

}  // namespace s21
