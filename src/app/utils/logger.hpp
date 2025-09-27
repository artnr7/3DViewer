#include <fstream>
#include <memory>

#include "iostream"

// HOW TO USE
//**
// Include this header into your
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
//  */

// RED
#define N_RED_DEF ("\033[0;31m")
#define B_RED_DEF ("\033[1;31m")
#define N_RED_RED ("\033[0;31;41m")
#define B_RED_RED ("\033[1;31;41m")

#define CYAN
#define YELLOW
#define GREEN
#define DEFAULT ("\033[0m")
#define RESET DEFAULT

namespace s21 {

class Logger {
 private:
  static std::unique_ptr<Logger> instance_;
  std::ofstream of_log_file_;
  std::string message_color_;

  Logger() : message_color_(DEFAULT) {
    std::string filename = {"../logs/app.log"};
    of_log_file_ = std::ofstream(filename);
    of_log_file_ << "App.log" << std::endl;
  }

  inline void DeterminateMessageColor(const int& message_type) noexcept {
    switch (message_type) {
      case MessageType::Warning:
        message_color_ = RED;
        break;
      case MessageType::Error:
        message_color_ = B_RED_RED;
        break;
      default:
        message_color_ = DEFAULT;
        break;
    }
  }

  inline void PrintMessage(const std::string& msg) {
    of_log_file_ << message_color_ << msg << RESET << std::endl;
  }

  inline void CoutMessage(const std::string& msg) {
    std::cout << message_color_ << msg << RESET << std::endl;
  }

 public:
  enum MessageType {
    Warning,
    Error,
  };
  static Logger* Log() {
    if (instance_ == nullptr) {
      instance_ = std::unique_ptr<Logger>(new Logger());
    }
    return instance_.get();
  }

  void Msg(const std::string& msg) { PrintMessage(msg); }

  void Msg(const std::string& msg, int msg_type) {
    DeterminateMessageColor(msg_type);
    PrintMessage(msg);
  }

  void MsgCerr(const std::string& msg) {
    PrintMessage(msg);
    CoutMessage(msg);
  }

  void MsgCerr(const std::string& msg, int msg_type) {
    DeterminateMessageColor(msg_type);
    PrintMessage(msg);
    CoutMessage(msg);
  }
};

std::unique_ptr<s21::Logger> s21::Logger::instance_ = nullptr;
}  // namespace s21