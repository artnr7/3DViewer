#ifndef LG_H_
#define LG_H_

#include <cmath>
#include <fstream>
#include <memory>
#include <string>

#define LOGFILE "logs/3dviewer.log"

namespace s21 {

class Lg {
private:
  static std::unique_ptr<Lg> inst_;
  std::ofstream logfile_;

  Lg() { logfile_ = std::ofstream(LOGFILE); }

public:
  static Lg *Log() {
    if (inst_ == nullptr) {
      inst_ = std::unique_ptr<Lg>(new Lg());
    }
    return inst_.get();
  }

  void Msg(const std::string &m) { logfile_ << m << std::endl; }

  void Tmp(std::string attr, const std::string &m) { Msg(attr + m); }

  void Info(const std::string &m) { Tmp("INFO: ", m); }
  void Debug(const std::string &m) { Tmp("DEBUG: ", m); }
  void Err(const std::string &m) { Tmp("ERROR: ", m); }
  void Warn(const std::string &m) { Tmp("WARN: ", m); }
};

} // namespace s21

#endif
