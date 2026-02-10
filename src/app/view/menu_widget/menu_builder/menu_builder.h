#ifndef MENU_BUILDER_H_
#define MENU_BUILDER_H_

#include "menu_builder/builder_contexts.h"

namespace s21 {

template <typename T>
concept Container = requires(T container, Panel* panel) {
  { container.AddPanel(panel) } -> std::same_as<void>;
};

template <Container T>
class MenuBuilder : public IBuilder {
 public:
  MenuBuilder(T* container, int item_width, int item_height);
  PanelContext AddPanel(const QString& title);

 private:
  /* Fields */
  T* parent_containter_;
  int width_;
  int height_;
};

template <Container T>
MenuBuilder<T>::MenuBuilder(T* container, int item_width, int item_height)
    : parent_containter_(container), width_(item_width), height_(item_height) {}

template <Container T>
PanelContext MenuBuilder<T>::AddPanel(const QString& title) {
  Panel* panel = new Panel(title);
  parent_containter_->AddPanel(panel);
  return PanelContext(panel, this, width_, height_);
}

}  // namespace s21

#endif  // MENU_BUILDER_H_
