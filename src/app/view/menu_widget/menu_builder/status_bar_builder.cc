#include "status_bar_builder.h"

namespace s21 {

StatusBarBuilder::StatusBarBuilder(StatusBar* status_bar)
  : status_bar_(status_bar) {}

StatusBarBuilder& StatusBarBuilder::AddWidget(QWidget* widget) {
  status_bar_->AddWidget(widget);
  return *this;
}

}  // namespace s21
