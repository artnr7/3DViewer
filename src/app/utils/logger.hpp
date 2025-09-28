#include <fstream>
#include <memory>

#include "iostream"

// HOW TO USE
//**
// Include this header into your code
// Use s21::Logger::Log() to call logger getter
// Then Use him Method
// f.g
// s21::Logger::Log()->Msg("Error", s21::Logger::MessageType::Warning);
// You can find a list of error types below.
// If you want make custom color please use this notation:
// Font-thicknes(N,R)_Font-color(RED, etc.)_Background-color(BLACK, etc.)
//  */

// RED
#define N_RED_DEF ("\033[0;31m")
#define B_RED_DEF ("\033[1;31m")

#define N_DEF_RED ("\033[0;39;41m")
#define B_DEF_RED ("\033[1;39;41m")

#define B_DEF_GREEN ("\033[1;39;42m")
#define B_DEF_YELLOW ("\033[1;39;43m")

#define B_CYAN_CYAN ("\033[1;36;46m")
#define YELLOW
#define GREEN
#define DEFAULT ("\033[0m")
#define RESET DEFAULT
// Message Types Colors ---------→
#define PROCESS B_DEF_GREEN
#define WARNING N_RED_DEF
#define ERROR B_DEF_RED
#define VARIABLES B_DEF_YELLOW

namespace s21 {

class Logger {
 private:
  static std::unique_ptr<Logger> instance_;
  std::ofstream of_log_file_;
  std::string message_color_;

  Logger() : message_color_(DEFAULT) {
    std::string filename = {"../logs/app.log"};
    of_log_file_ = std::ofstream(filename);
    of_log_file_ << B_CYAN_CYAN << "App.log" << RESET << std::endl;
  }

  inline void DeterminateMessageColor(const int& message_type) noexcept {
    switch (message_type) {
      case MessageType::Warning:
        message_color_ = WARNING;
        break;
      case MessageType::Error:
        message_color_ = ERROR;
        break;
      case MessageType::Process:
        message_color_ = PROCESS;
        break;
      case MessageType::Variable:
        message_color_ = VARIABLES;
        break;
      case MessageType::Default:
        message_color_ = DEFAULT;
        break;
      default:
        of_log_file_ << B_CYAN_CYAN << "App.log" << RESET << std::endl;

        break;
    }
  }

  inline void PrintMessage(const std::string& msg) {
    of_log_file_ << message_color_ << msg << RESET << std::endl;
  }

  inline void CerrMessage(const std::string& msg) {
    std::cerr << message_color_ << msg << RESET << std::endl;
  }

 public:
  enum MessageType {
    Warning,
    Error,
    Default,
    Process,
    Variable,
  };
  static Logger* Log() {
    if (instance_ == nullptr) {
      instance_ = std::unique_ptr<Logger>(new Logger());
    }
    return instance_.get();
  }

  void Msg(const std::string& msg) {
    DeterminateMessageColor(MessageType::Default);
    PrintMessage(msg);
  }

  void Msg(const std::string& msg, int msg_type) {
    DeterminateMessageColor(msg_type);
    PrintMessage(msg);
  }

  void MsgCerr(const std::string& msg) {
    DeterminateMessageColor(MessageType::Default);
    PrintMessage(msg);
    CerrMessage(msg);
  }

  void MsgCerr(const std::string& msg, int msg_type) {
    DeterminateMessageColor(msg_type);
    PrintMessage(msg);
    CerrMessage(msg);
  }
};

}  // namespace s21