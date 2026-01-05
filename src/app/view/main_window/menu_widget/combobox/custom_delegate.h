#ifndef CUSTOM_DELEGATE_H_
#define CUSTOM_DELEGATE_H_

#include <QStyledItemDelegate>

#include "combo_box.h"

namespace s21 {

class CenterIconDelegate : public QStyledItemDelegate {
  Q_OBJECT

 public:
  explicit CenterIconDelegate(CustomComboBox* comboBox,
                              QObject* parent = nullptr);

  /* Paint Handlers */
  void paint(QPainter* painter, const QStyleOptionViewItem& option,
             const QModelIndex& index) const override;
  QSize sizeHint(const QStyleOptionViewItem& option,
                 const QModelIndex& index) const override;

 private:
  /* Internal Helpers */
  QSize CalculateIconSize(const QRect& rect, const QIcon& icon) const;
  void DrawBackground(QPainter* painter, const QRect& rect,
                      const QStyleOptionViewItem& option,
                      bool isLastItem) const;

 private:
  CustomComboBox* combo_box_;

  const ComboBoxStyle* style_;
  const ComboBoxStyle::Color& colors_;
};

} // namespace s21


#endif  // CUSTOM_DELEGATE_H_
