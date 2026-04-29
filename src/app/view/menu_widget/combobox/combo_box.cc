#include "combo_box.h"

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QScreen>
#include <QStyledItemDelegate>
#include <QTimer>
#include <QVBoxLayout>

#include "custom_delegate.h"

namespace s21 {

CustomComboBox::CustomComboBox(int width, int height, QWidget* parent)
    : QWidget(parent),
      // Data members
      current_index_(-1),
      expanded_(false),

      // Dimensions
      width_(width),
      height_(height),
      style_{},

      // Colors initialization
      colors_(style_.colors),

      // Widget pointers (инициализируем nullptr)
      current_icon_label_(nullptr),
      list_widget_(nullptr),
      popup_(nullptr),
      animation_(nullptr) {
  SetupUI();
  SetupConnections();

  setFixedSize(width_, height_);
  setFocusPolicy(Qt::StrongFocus);
}

/* Arrow Icon Management */
void CustomComboBox::SetArrows(const QString& up_icon_path,
                               const QString& down_icon_path) {
  QString absolute_path_up = QDir::cleanPath(
      QCoreApplication::applicationDirPath() + "/../" + up_icon_path);
  QString absolute_path_down = QDir::cleanPath(
      QCoreApplication::applicationDirPath() + "/../" + down_icon_path);

  // qDebug() << "Absolute path up:" << absolute_path_up;
  // qDebug() << "Absolute path down :" << absolute_path_down;

  SetUpArrow(absolute_path_up);
  SetDownArrow(absolute_path_down);
}

void CustomComboBox::SetUpArrow(const QString& up_icon_path) {
  SetArrow(arrow_up_pixmap_, up_icon_path);
}

void CustomComboBox::SetDownArrow(const QString& down_icon_path) {
  SetArrow(arrow_down_pixmap_, down_icon_path);
}

void CustomComboBox::SetArrow(QPixmap& pixmap, const QString& pixmap_path) {
  QPixmap new_pixmap(pixmap_path);

  if (new_pixmap.isNull()) {
    qWarning() << "Failed to load arrow icon from:" << pixmap_path;
  }

  pixmap = new_pixmap;
  update();
}

void CustomComboBox::SetArrowAreaWidth(int width) {
  style_.minimum_arrow_area_width =
      qMax(style_.minimum_arrow_area_width, width);
  update();
}
// Arrow Icon Management

/* Size calculations */
int CustomComboBox::IconSize() const {
  return static_cast<int>(height_ * style_.icon_scale_factor);
}

int CustomComboBox::ItemMargin() const {
  return static_cast<int>((height_ - IconSize()) / 2);
}

int CustomComboBox::ItemHeight() const { return IconSize() + ItemMargin() * 2; }
// Size calculations

/* Color managment mutator*/
void CustomComboBox::SetBackgroundColor(const QColor& color) {
  colors_.background = color;
  update();
}

void CustomComboBox::SetBorderColor(const QColor& color) {
  colors_.border = color;
  update();
}

void CustomComboBox::SetHoverColor(const QColor& color) {
  colors_.hover = color;
  update();
}

void CustomComboBox::SetSelectedColor(const QColor& color) {
  colors_.selected = color;
  update();
}
// Color managment mutator

/* Color managment accessors*/
QColor CustomComboBox::GetBackgroundColor() const { return colors_.background; }
QColor CustomComboBox::GetBorderColor() const { return colors_.border; }
QColor CustomComboBox::GetHoverColor() const { return colors_.hover; }
QColor CustomComboBox::GetSelectedColor() const { return colors_.selected; }

const ComboBoxStyle::Color& CustomComboBox::GetColor() const { return colors_; }
// Color managment accessors

/* Item management */
void CustomComboBox::AddItem(const QString& icon_path, int value) {
  QString absolute_path = QDir::cleanPath(
      QCoreApplication::applicationDirPath() + "/../" + icon_path);

  // qDebug() << "Original path:" << icon_path;
  // qDebug() << "Absolute path:" << absolute_path;

  AddItem(QIcon(absolute_path), value);
}

void CustomComboBox::AddItem(const QIcon& icon, int value) {
  if (icon.isNull()) {
    qWarning() << "Attempting to add null icon to CustomComboBox";
    return;
  }

  items_.append(icon);
  QListWidgetItem* list_item = new QListWidgetItem(list_widget_);

  list_item->setIcon(icon);
  list_item->setData(Qt::UserRole, value);
  list_item->setText("");
  list_item->setTextAlignment(Qt::AlignCenter);
  list_item->setSizeHint(QSize(width_, ItemHeight()));

  if (current_index_ == -1) {
    SetCurrentIndex(0);
  }

  UpdateCurrentDisplay();
}

void CustomComboBox::AddItems(
    std::initializer_list<std::pair<QString, int>> items) {
  for (const auto& item : items) {
    AddItem(item.first, item.second);
  }
}

void CustomComboBox::Clear() {
  items_.clear();
  list_widget_->clear();
  current_index_ = -1;
  UpdateCurrentDisplay();
}
// Item management

/* State Control */
void CustomComboBox::SetCurrentIndex(int index) {
  if (index >= 0 && index < items_.size() && index != current_index_) {
    current_index_ = index;
    UpdateCurrentDisplay();

    int actual_value = list_widget_->item(index)->data(Qt::UserRole).toInt();
    emit CurrentIndexChanged(actual_value);
  }
}

void CustomComboBox::SetExpanded(bool expanded) {
  expanded_ = expanded;
  update();
}
// State Control

/* Setup & Update */
void CustomComboBox::SetupUI() {
  QVBoxLayout* mainLayout = new QVBoxLayout(this);
  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->setSpacing(0);

  QWidget* currentWidget = new QWidget(this);
  currentWidget->setFixedHeight(height_);

  QHBoxLayout* currentLayout = new QHBoxLayout(currentWidget);
  currentLayout->setContentsMargins(0, 0, 0, 0);
  currentLayout->setSpacing(0);

  current_icon_label_ = new QLabel(currentWidget);
  current_icon_label_->setAlignment(Qt::AlignCenter);
  current_icon_label_->setScaledContents(false);

  currentLayout->addStretch();
  currentLayout->addWidget(current_icon_label_);
  currentLayout->addStretch();

  mainLayout->addWidget(currentWidget);

  popup_ = new QWidget(nullptr);
  popup_->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint |
                         Qt::NoDropShadowWindowHint);
  popup_->setAttribute(Qt::WA_TranslucentBackground);
  popup_->setAttribute(Qt::WA_ShowWithoutActivating);

  popup_->installEventFilter(this);

  QVBoxLayout* popupLayout = new QVBoxLayout(popup_);
  popupLayout->setContentsMargins(0, 0, 0, 0);
  popupLayout->setSpacing(0);

  list_widget_ = new QListWidget(popup_);
  list_widget_->setFrameShape(QFrame::NoFrame);
  list_widget_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  list_widget_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  list_widget_->setSelectionMode(QAbstractItemView::SingleSelection);
  list_widget_->setMouseTracking(true);

  list_widget_->setItemDelegate(new CenterIconDelegate(this, list_widget_));

  list_widget_->setStyleSheet(QString(R"(
    QListWidget {
      background-color: %1;
      border: none;
      border-bottom-left-radius: %2px;
      border-bottom-right-radius: %3px;
    }
  )")
                                  .arg(colors_.background.name())
                                  .arg(style_.border_radius)
                                  .arg(style_.border_radius));

  popupLayout->addWidget(list_widget_);

  animation_ = new QPropertyAnimation(popup_, "geometry", this);
  animation_->setDuration(style_.animation_duration_ms);
  animation_->setEasingCurve(style_.easing_curve);
}

void CustomComboBox::SetupConnections() {
  connect(list_widget_, &QListWidget::itemClicked, this,
          &CustomComboBox::OnItemClicked);
  connect(animation_, &QPropertyAnimation::finished, this,
          &CustomComboBox::OnAnimationFinished);
}

void CustomComboBox::UpdateCurrentDisplay() {
  if (current_index_ >= 0 && current_index_ < items_.size()) {
    const QIcon& icon = items_[current_index_];

    int available_width = width_ - style_.minimum_arrow_area_width;
    int available_height = height_;

    int max_width =
        static_cast<int>(available_width * style_.current_icon_max_scale);
    int max_height =
        static_cast<int>(available_height * style_.current_icon_max_scale);

    int fallback_size = IconSize() * 2;
    QList<QSize> available_sizes = icon.availableSizes();
    QSize original_size = available_sizes.isEmpty()
                              ? QSize(fallback_size, fallback_size)
                              : available_sizes.first();

    qreal aspectRatio = qreal(original_size.width()) / original_size.height();

    QSize targetSize;
    if (aspectRatio >= 1.0) {
      int width = qMin(max_width, static_cast<int>(max_height * aspectRatio));
      int height = static_cast<int>(width / aspectRatio);
      targetSize = QSize(width, height);
    } else {
      int height = qMin(max_height, static_cast<int>(max_width / aspectRatio));
      int width = static_cast<int>(height * aspectRatio);
      targetSize = QSize(width, height);
    }

    QPixmap pixmap = icon.pixmap(original_size);
    QPixmap scaledPixmap = pixmap.scaled(targetSize, Qt::KeepAspectRatio,
                                         Qt::SmoothTransformation);

    current_icon_label_->setPixmap(scaledPixmap);
    current_icon_label_->setFixedSize(targetSize);

  } else {
    current_icon_label_->clear();
  }
}
// Setup & Update

/* Event Handlers */

void CustomComboBox::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  PaintBackground(painter);
  PaintArrow(painter);
}

void CustomComboBox::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    if (!expanded_) {
      int itemHeightVal = ItemHeight();
      int totalHeight = itemHeightVal * items_.size();

      popup_->setFixedSize(width(), totalHeight);
      list_widget_->setFixedSize(width(), totalHeight);

      QPoint globalPos = mapToGlobal(QPoint(0, height_));

      QRect startRect(globalPos.x(), globalPos.y(), width(), 0);
      QRect endRect(globalPos.x(), globalPos.y(), width(), totalHeight);

      popup_->move(globalPos);
      animation_->setStartValue(startRect);
      animation_->setEndValue(endRect);
      animation_->start();

      popup_->show();
      SetExpanded(true);

      if (current_index_ >= 0) {
        list_widget_->setCurrentRow(current_index_);
      }
    }
  }

  QWidget::mousePressEvent(event);
}

bool CustomComboBox::eventFilter(QObject* obj, QEvent* event) {
  if (obj == popup_ && event->type() == QEvent::MouseButtonPress) {
    QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);

    if (!popup_->rect().contains(mouseEvent->pos())) {
      popup_->hide();
      SetExpanded(false);
      update();
      return true;
    }
  }

  return QWidget::eventFilter(obj, event);
}

void CustomComboBox::leaveEvent(QEvent* event) {
  QWidget::leaveEvent(event);
  update();
}

void CustomComboBox::focusOutEvent(QFocusEvent* event) {
  if (expanded_ && !popup_->underMouse() && !underMouse()) {
    popup_->hide();
    SetExpanded(false);
    update();
  }
  QWidget::focusOutEvent(event);
}
// Event Handlers

/* Paint management */
void CustomComboBox::PaintBackground(QPainter& painter) {
  QRect rect = this->rect();
  QColor bg_color = underMouse() ? colors_.hover : colors_.background;

  painter.setPen(QPen(colors_.border, style_.border_width));

  if (expanded_) {
    PaintExpandedBackground(painter, rect, bg_color);
  } else {
    PaintCollapsedBackground(painter, rect, bg_color);
  }
}

void CustomComboBox::PaintExpandedBackground(QPainter& painter,
                                             const QRect& rect,
                                             const QColor& bg_color) {
  int radius = style_.border_radius;
  int correction = style_.border_correction;

  QPainterPath roundedPath;
  roundedPath.addRoundedRect(rect.adjusted(0, 0, -correction, -correction),
                             radius, radius);

  QPainterPath clipPath;
  clipPath.addRect(rect.left(), rect.top(), rect.width(),
                   rect.height() - radius);

  QPainterPath clippedPath = roundedPath.intersected(clipPath);

  QPainterPath bottomRectPath;
  int bottomRectTop = rect.top() + rect.height() - (radius + correction);
  bottomRectPath.addRect(rect.left(), bottomRectTop, rect.width() - correction,
                         radius);

  QPainterPath finalPath = clippedPath.united(bottomRectPath);

  painter.fillPath(finalPath, bg_color);
  painter.drawPath(finalPath);
}

void CustomComboBox::PaintCollapsedBackground(QPainter& painter,
                                              const QRect& rect,
                                              const QColor& bg_color) {
  int radius = style_.border_radius;
  int correction = style_.border_correction;

  QPainterPath path;
  path.addRoundedRect(rect.adjusted(0, 0, -correction, -correction), radius,
                      radius);

  painter.fillPath(path, bg_color);
  painter.drawPath(path);
}

void CustomComboBox::PaintArrow(QPainter& painter) {
  QRect arrow_area(0, 0, style_.minimum_arrow_area_width, height_);

  const QPixmap* arrow_pixmap =
      expanded_ ? &arrow_up_pixmap_ : &arrow_down_pixmap_;

  int icon_size =
      qMin(arrow_area.width(), arrow_area.height()) * style_.arrow_scale_factor;

  QRect icon_rect(arrow_area.left() + (arrow_area.width() - icon_size) / 2,
                  arrow_area.top() + (arrow_area.height() - icon_size) / 2,
                  icon_size, icon_size);

  QPixmap scaled_pixmap = arrow_pixmap->scaled(
      icon_size, icon_size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

  QRect drawRect(
      icon_rect.left() + (icon_rect.width() - scaled_pixmap.width()) / 2,
      icon_rect.top() + (icon_rect.height() - scaled_pixmap.height()) / 2,
      scaled_pixmap.width(), scaled_pixmap.height());

  painter.drawPixmap(drawRect, scaled_pixmap);
}
// Paint management

/* Internal Helpers */
void CustomComboBox::OnItemClicked(QListWidgetItem* item) {
  int index = list_widget_->row(item);
  SetCurrentIndex(index);
  SetExpanded(false);
  popup_->hide();
  update();
}

void CustomComboBox::OnAnimationFinished() {
  if (!expanded_) {
    popup_->hide();
    update();
  }
}
// Internal Helpers

}  // namespace s21
