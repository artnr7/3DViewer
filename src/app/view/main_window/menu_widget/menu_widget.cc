#include "menu_widget.hpp"

#include <string>

#include "../../../utils/logger.hpp"

s21::MenuWidget::MenuWidget(QWidget *parent) : QWidget(parent) {
  s21::Logger::Log()->Msg(std::string(__func__) + " Constructor...",
                          Logger::MessageType::Process);
  Connections();
}
