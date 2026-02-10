#ifndef BUILDER_CONTEXTS_H_
#define BUILDER_CONTEXTS_H_

#include <functional>
#include <utility>

#include "panel/panel.h"

namespace s21 {

class PanelContext;

class IBuilder {
 public:
  virtual ~IBuilder() = default;
  virtual PanelContext AddPanel(const QString& title) = 0;
};

class SubPanelContext {
 public:
  SubPanelContext(SubPanel* sub_panel, PanelContext* panel_context,
                  IBuilder* root_builder, int width, int height);

  template <typename T, typename... Args>
  SubPanelContext& Add(const QString& label, std::function<void(T*)> config,
                       Args&&... args);

  PanelContext AddPanel(const QString& title);
  SubPanelContext AddSubPanel(const QString& title);

  SubPanelContext& SetSize(int width, int height);

 private:
  /* Fields */
  SubPanel* sub_panel_;
  PanelContext* parent_panel_context_;
  IBuilder* root_builder_;
  int width_;
  int height_;
  int current_width_;
  int current_height_;
};

template <typename Item, typename... Args>
SubPanelContext& SubPanelContext::Add(const QString& label,
                                      std::function<void(Item*)> config_func,
                                      Args&&... args) {
  Item* item = new Item(label, current_width_, current_height_,
                        std::forward<Args>(args)...);
  current_width_ = width_;
  current_height_ = height_;

  if (config_func) {
    config_func(item);
  }
  sub_panel_->AddItem(item);
  return *this;
}

class PanelContext {
 public:
  PanelContext(Panel* panel, IBuilder* root, int width, int height);

  PanelContext AddPanel(const QString& title);
  SubPanelContext AddSubPanel(const QString& title);

 private:
  /* Fields */
  Panel* panel_;
  IBuilder* root_builder_;
  int item_width_;
  int item_height_;
};

}  // namespace s21

#endif  // BUILDER_CONTEXTS_H_
