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
public:
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

  void LogT(LogLevel lvl, const std::string &mark, const std::string &m) {
    if (Throw(lvl)) {
      return;
    };

    OutWithAttr(mark + ": ", m);
  }
  void Trace(const std::string &m) { LogT(LogLevel::TRACE, "TRACE", m); }
  void Debug(const std::string &m) { LogT(LogLevel::DEBUG, "DEBUG", m); }
  void Info(const std::string &m) { LogT(LogLevel::INFO, "INFO", m); }
  void Warn(const std::string &m) { LogT(LogLevel::WARN, "WARN", m); }
  void Err(const std::string &m) { LogT(LogLevel::ERR, "ERR", m); }
  void Fatal(const std::string &m) { LogT(LogLevel::FATAL, "FATAL", m); }
};

} // namespace s21

#endif
