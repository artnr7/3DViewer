#ifndef STATUS_BAR_BUILDER_H_
#define STATUS_BAR_BUILDER_H_

#include <functional>

#include "panel/panel.h"

namespace s21 {

class StatusBarBuilder {
 public:
  explicit StatusBarBuilder(StatusBar* status_bar);

  StatusBarBuilder& AddWidget(QWidget* widget);

  template <typename T, typename... Args>
  StatusBarBuilder& Add(std::function<void(T*)> config, Args&&... args);

 private:
  StatusBar* status_bar_;
};

template <typename T, typename... Args>
StatusBarBuilder& StatusBarBuilder::Add(std::function<void(T*)> config,
                                        Args&&... args) {
  T* widget = new T(std::forward<Args>(args)...);
  if (config) {
    config(widget);
  }
  status_bar_->AddWidget(widget);
  return *this;
}

}  // namespace s21

#endif  // STATUS_BAR_BUILDER_H_
