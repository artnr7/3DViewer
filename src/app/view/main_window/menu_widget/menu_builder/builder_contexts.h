#ifndef BUILDER_CONTEXTS_H_
#define BUILDER_CONTEXTS_H_

#include "panel/panel.h"
#include <functional>
#include <utility>

namespace s21 {

class PanelContext;

class SubPanelContext {
 public:
  SubPanelContext(SubPanel* sub_panel, PanelContext* panel_context, int width, int height);

  template <typename T, typename... Args>
  SubPanelContext& Add(const QString& label, std::function<void(T*)> config, Args&&...args);
  SubPanelContext AddSubPanel(const QString& title);

  private:
  /* Fields */
  SubPanel* sub_panel_;
  PanelContext* parent_panel_context_;
  int width_;
  int height_;
};

template <typename Item, typename... Args>
SubPanelContext& SubPanelContext::Add(const QString& label,
                                      std::function<void(Item*)> config_func,
                                      Args&&...args) {
  Item* item = new Item(label, width_, height_, std::forward<Args>(args)...);
  if (config_func) {
    config_func(item);
  }
  sub_panel_->AddItem(item);
  return *this;
}

class PanelContext {
 public:
  PanelContext(Panel* panel, int width, int height);
  SubPanelContext AddSubPanel(const QString& title);

 private:
  /* Fields */
  Panel* panel_;
  int item_width_;
  int item_height_;
};


} // namespace s21

#endif // BUILDER_CONTEXTS_H_
