#ifndef MENU_BUILDER_H_
#define MENU_BUILDER_H_

#include "menu_builder/builder_contexts.h"

namespace s21 {

template <typename Container>
class MenuBuilder {
 public:
  MenuBuilder(Container* container, int item_width, int item_height);
  PanelContext AddPanel(const QString& title);

 private:
 /* Fields */
 Container* parent_containter_;
 int width_;
 int height_;
};

template <typename Container>
MenuBuilder<Container>::MenuBuilder(Container* container, int item_width, int item_height)
  : parent_containter_(container)
  , width_(item_width)
  , height_(item_height){
}

template <typename Container>
PanelContext MenuBuilder<Container>::AddPanel(const QString& title) {
  Panel* panel = new Panel(title);
  parent_containter_->AddPanel(panel);
  return PanelContext(panel, width_, height_);
}

} // namespace s21

#endif // MENU_BUILDER_H_
