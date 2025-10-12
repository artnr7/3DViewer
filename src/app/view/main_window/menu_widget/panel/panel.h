#ifndef PANEL_H_
#define PANEL_H_

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <qboxlayout.h>
#include <qlabel.h>

#include "panel_items.h"

namespace s21 {

class SubPanel : public QWidget {
  Q_OBJECT
public:
  explicit SubPanel(const QString &name, QWidget *parent = nullptr);
  void AddItem(PanelItem *item);
private:
  QLabel* name_label_;
  QHBoxLayout* items_layout_;
};

class Panel : public QWidget {
  Q_OBJECT

public:
  explicit Panel(const QString &name, QWidget *parent = nullptr);
  void AddMiniPanel(SubPanel *mini_panel);

private:
  QLabel *panel_name_label_;
  QVBoxLayout *main_layout_;
};

} // namespace s21

#endif // PANEL_H_