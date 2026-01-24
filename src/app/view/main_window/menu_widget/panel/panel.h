#ifndef PANEL_H_
#define PANEL_H_

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>

#include "panel_items.h"

namespace s21 {

class SubPanel : public QWidget {
  Q_OBJECT
public:
  explicit SubPanel(const QString &name, QWidget *parent = nullptr);
  void AddItem(PIBase *item);
  int GetWidth() const;
private:
  QLabel* name_label_;
  QHBoxLayout* items_layout_;
};

class Panel : public QWidget {
 Q_OBJECT

public:
  explicit Panel(const QString &name, QWidget *parent = nullptr);
  void AddSubPanel(SubPanel *mini_panel);

private:
  QLabel *panel_name_label_;
  QVBoxLayout *main_layout_;
};

class ToolBar : public QWidget {
 Q_OBJECT

 public:
  explicit ToolBar(int width, int height, QWidget *parent = nullptr);
  void AddPanel(Panel *panel);
 private:
  QVBoxLayout* layout_;
  QWidget* background_;
};

} // namespace s21

#endif // PANEL_H_
