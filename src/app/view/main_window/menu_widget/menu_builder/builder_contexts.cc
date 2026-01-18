#include "menu_builder/builder_contexts.h"

namespace s21 {

SubPanelContext::SubPanelContext(SubPanel* sub_panel, PanelContext* panel_context, int width, int height)
  : sub_panel_(sub_panel)
  , parent_panel_context_(panel_context)
  , width_(width)
  , height_(height) {
}

SubPanelContext SubPanelContext::AddSubPanel(const QString& title) {
  return parent_panel_context_->AddSubPanel(title);
}

PanelContext::PanelContext(Panel* panel, int widht, int height)
  : panel_(panel)
  , item_width_(widht)
  , item_height_(height) {
}

SubPanelContext PanelContext::AddSubPanel(const QString& title) {
  SubPanel* sub_panel = new SubPanel(title);
  panel_->AddSubPanel(sub_panel);

  return SubPanelContext(sub_panel, this, item_width_, item_height_);
}
} // namespace s21
