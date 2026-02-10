#include "menu_builder/builder_contexts.h"

namespace s21 {

SubPanelContext::SubPanelContext(SubPanel* sub_panel,
                                 PanelContext* panel_context,
                                 IBuilder* root_builder, int width, int height)
    : sub_panel_(sub_panel),
      parent_panel_context_(panel_context),
      root_builder_(root_builder),
      width_(width),
      height_(height),
      current_width_(width),
      current_height_(height) {}

PanelContext SubPanelContext::AddPanel(const QString& title) {
  return root_builder_->AddPanel(title);
}

SubPanelContext SubPanelContext::AddSubPanel(const QString& title) {
  return parent_panel_context_->AddSubPanel(title);
}

SubPanelContext& SubPanelContext::SetSize(int width, int height) {
  current_width_ = width;
  current_height_ = height;
  return *this;
}

PanelContext::PanelContext(Panel* panel, IBuilder* root, int widht, int height)
    : panel_(panel),
      root_builder_(root),
      item_width_(widht),
      item_height_(height) {}

PanelContext PanelContext::AddPanel(const QString& title) {
  return root_builder_->AddPanel(title);
}

SubPanelContext PanelContext::AddSubPanel(const QString& title) {
  SubPanel* sub_panel = new SubPanel(title);
  panel_->AddSubPanel(sub_panel);

  return SubPanelContext(sub_panel, this, root_builder_, item_width_,
                         item_height_);
}

}  // namespace s21
