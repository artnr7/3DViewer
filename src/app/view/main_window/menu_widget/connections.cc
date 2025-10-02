#include <QTimer>

#include "menu_widget.hpp"
#include "../../../utils/logger.hpp"


void s21::MenuWidget::Connections() {
  s21::Logger::Log()->Msg(std::string(__func__) + " Connecting...",
                          Logger::MessageType::Process);

  temp_timer = new QTimer(this);
  temp_timer->start(0);

  connect(temp_timer, &QTimer::timeout, this,
          &s21::MenuWidget::CreateNewObjectImitated);
}