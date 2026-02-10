#include "custom_delegate.h"

#include <QPainter>
#include <QPainterPath>

namespace s21 {

CenterIconDelegate::CenterIconDelegate(CustomComboBox* combo_box,
                                       QObject* parent)
    : QStyledItemDelegate(parent),
      combo_box_(combo_box),
      style_(&combo_box_->GetStyle()),
      colors_(style_->colors) {}

/* Paint Handlers */
void CenterIconDelegate::paint(QPainter* painter,
                               const QStyleOptionViewItem& option,
                               const QModelIndex& index) const {
  QStyleOptionViewItem opt = option;
  initStyleOption(&opt, index);

  QRect rect = opt.rect;

  painter->save();
  painter->setRenderHint(QPainter::Antialiasing);

  bool isLastItem = (index.row() == index.model()->rowCount() - 1);

  DrawBackground(painter, rect, option, isLastItem);

  if (!opt.icon.isNull()) {
    QSize iconSize = CalculateIconSize(rect, opt.icon);

    QPoint iconPos(rect.left() + (rect.width() - iconSize.width()) / 2,
                   rect.top() + (rect.height() - iconSize.height()) / 2);

    QPixmap pixmap = opt.icon.pixmap(iconSize);
    painter->drawPixmap(QRect(iconPos, iconSize), pixmap);
  }

  painter->restore();
}

QSize CenterIconDelegate::sizeHint(const QStyleOptionViewItem& option,
                                   const QModelIndex& index) const {
  Q_UNUSED(option);
  Q_UNUSED(index);
  return QSize(option.rect.width(), combo_box_->ItemHeight());
}
// Paint Handlers

/* Internal Helpers */
QSize CenterIconDelegate::CalculateIconSize(const QRect& rect,
                                            const QIcon& icon) const {
  int fallback_width = rect.width() * style_->current_icon_max_scale;
  int fallback_height = rect.height() * style_->icon_scale_factor;
  int fallback_size = qMin(fallback_width, fallback_height);

  QSize availableSize = icon.availableSizes().isEmpty()
                            ? QSize(fallback_size, fallback_size)
                            : icon.availableSizes().first();

  qreal aspectRatio = qreal(availableSize.width()) / availableSize.height();

  QSize iconSize;
  int max_icon_width = rect.width() * style_->current_icon_max_scale;
  int max_icon_height = rect.height() * style_->icon_scale_factor;
  if (aspectRatio >= style_->hotizontal_thresold) {
    // Horizontal icons
    int width =
        qMin(static_cast<int>(max_icon_height * aspectRatio), max_icon_width);
    int height = width / aspectRatio;
    iconSize = QSize(width, height);
  } else {
    // Vertical icons
    int height =
        qMin(max_icon_height, static_cast<int>(max_icon_width / aspectRatio));
    int width = height * aspectRatio;
    iconSize = QSize(width, height);
  }

  return iconSize;
}

void CenterIconDelegate::DrawBackground(QPainter* painter, const QRect& rect,
                                        const QStyleOptionViewItem& option,
                                        bool isLastItem) const {
  QColor bgColor = colors_.background;

  if (option.state & QStyle::State_Selected) {
    bgColor = colors_.selected;
  } else if (option.state & QStyle::State_MouseOver) {
    bgColor = colors_.hover;
  }

  QPainterPath path;

  if (isLastItem && style_->border_radius > 0) {
    int roundedHeight = style_->border_radius * 2;

    QPainterPath topPart;
    topPart.addRect(rect.left() + style_->default_item_border, rect.top(),
                    rect.width() - style_->default_item_border * 2,
                    rect.height() - style_->border_radius);

    QPainterPath bottomPart;
    bottomPart.addRoundedRect(rect.left() + style_->default_item_border,
                              rect.top() + rect.height() - roundedHeight,
                              rect.width() - style_->default_item_border * 2,
                              roundedHeight, style_->border_radius,
                              style_->border_radius);

    path = topPart.united(bottomPart);
  } else {
    path.addRect(rect.adjusted(style_->default_item_border, 0,
                               -style_->default_item_border, 0));
  }

  painter->fillPath(path, bgColor);
}
// Internal Helpers

}  // namespace s21
