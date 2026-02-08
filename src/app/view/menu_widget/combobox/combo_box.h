#ifndef COMBOX_H
#define COMBOX_H

#include <QIcon>
#include <QLabel>
#include <QWidget>
#include <QListWidgetItem>
#include <QVector>
#include <QListWidget>
#include <QPropertyAnimation>

#include "style_configs/combo_box_style.h"

namespace s21 {

class CustomComboBox : public QWidget {
  Q_OBJECT

 public:
  explicit CustomComboBox(int width = 150, int height = 50,
                          QWidget* parent = nullptr);

  const ComboBoxStyle& GetStyle() const { return style_; }
  const ComboBoxStyle::Color& GetColor() const;

  /* Arrow Icon Management */
  void SetArrows(const QString& up_icon_path, const QString& down_icon_path);
  void SetUpArrow(const QString& up_icon_path);
  void SetDownArrow(const QString& down_icon_path);
  void SetArrowAreaWidth(int width);

  /* Size Calculations */
  int IconSize() const;
  int ItemMargin() const;
  int ItemHeight() const;

  /* Color Management Mutators*/
  void SetBackgroundColor(const QColor& color);
  void SetBorderColor(const QColor& color);
  void SetHoverColor(const QColor& color);
  void SetSelectedColor(const QColor& color);

  /* Color Management Accessors*/
  QColor GetBackgroundColor() const;
  QColor GetBorderColor() const;
  QColor GetHoverColor() const;
  QColor GetSelectedColor() const;
  QColor GetPopupBackgroundColor() const;

  /* Item Management */
  void AddItem(const QIcon& icon, int value);
  void AddItem(const QString& icon_path, int value);
  void AddItems(std::initializer_list<std::pair<QString, int>> items);

  void Clear();

  /* State Control */
  void SetCurrentIndex(int index);
  void SetExpanded(bool expanded);

 signals:
  void CurrentIndexChanged(int index);

 protected:
  /* Event Handlers */
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void leaveEvent(QEvent* event) override;
  void focusOutEvent(QFocusEvent* event) override;
  bool eventFilter(QObject* obj, QEvent* event) override;

 private:
  /* Arrow Icon Management */
  void SetArrow(QPixmap& pixmap, const QString& pixmap_path);

  /* Setup & Update */
  void SetupUI();
  void SetupConnections();
  void UpdateCurrentDisplay();

  /* Paint Management */
  void PaintBackground(QPainter& painter);
  void PaintExpandedBackground(QPainter& painter, const QRect& rect, const QColor& bg_color);
  void PaintCollapsedBackground(QPainter& painter, const QRect& rect, const QColor& bg_color);
  void PaintArrow(QPainter& painter);

  /* Internal Helpers */
  void OnItemClicked(QListWidgetItem* item);
  void OnAnimationFinished();

 private:
  int width_;
  int height_;

  QPixmap arrow_up_pixmap_;
  QPixmap arrow_down_pixmap_;

  ComboBoxStyle style_;
  ComboBoxStyle::Color& colors_;

  QVector<QIcon> items_;
  int current_index_;
  bool expanded_;

  QLabel* current_icon_label_;
  QListWidget* list_widget_;
  QWidget* popup_;
  QPropertyAnimation* animation_;
};

} // namespace s21

#endif  // COMBOX_H
