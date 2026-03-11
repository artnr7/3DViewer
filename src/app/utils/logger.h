#ifndef LG_H_
#define LG_H_

#include <cmath>
#include <cstdint>
#include <fstream>
#include <memory>
#include <string>

#define LOGFILE "logs/3dviewer.log"

namespace s21 {

class Lg {

  enum class LogLevel : uint8_t {
    TRACE, // signals, events
    DEBUG,
    INFO,
    WARN,
    ERR,
    FATAL
  };

private:
  static std::unique_ptr<Lg> inst_;
  std::ofstream logfile_ = std::ofstream(LOGFILE);
  LogLevel log_lvl_ = LogLevel::INFO;

  Lg() = default;

public:
  static Lg *Log() {
    if (inst_ == nullptr) {
      inst_ = std::unique_ptr<Lg>(new Lg());
    }
    return inst_.get();
  }

  void SetLogLevel(LogLevel log_lvl) { log_lvl_ = log_lvl; }

  void LogToFile(const std::string &m) { logfile_ << m << std::endl; }

  void OutWithAttr(std::string attr, const std::string &m) {
    LogToFile(attr + m);
  }

  bool Throw(LogLevel local_log_lvl) {
    if (local_log_lvl < log_lvl_) {
      return true;
    }
    return false;
  }

  void Trace(const std::string &m) {
    if (Throw(LogLevel::TRACE)) {
      return;
    };

    OutWithAttr("TRACE: ", m);
  }
  void Debug(const std::string &m) {
    if (Throw(LogLevel::DEBUG)) {
      return;
    };

    OutWithAttr("DEBUG: ", m);
  }

  void Info(const std::string &m) {
    if (Throw(LogLevel::INFO)) {
      return;
    };

    OutWithAttr("INFO: ", m);
  }
  void Warn(const std::string &m) {
    if (Throw(LogLevel::WARN)) {
      return;
    };

    OutWithAttr("WARN: ", m);
  }

  void Err(const std::string &m) {
    if (Throw(LogLevel::WARN)) {
      return;
    };

    OutWithAttr("ERROR: ", m);
  }

  void Fatal(const std::string &m) {
    if (Throw(LogLevel::FATAL)) {
      return;
    };

    OutWithAttr("FATAL: ", m);
  }
};

} // namespace s21

#endif
