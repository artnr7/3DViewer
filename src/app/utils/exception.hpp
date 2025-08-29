#include <exception>
#include <string>

namespace s21 {
class Exception : public std::exception {
public:
  explicit Exception(const std::string &message) noexcept : message_{message} {}
  /**  @todo хз что тут с деструкторами, говорят что он создастся автоматически
   * и уйдёт в базовый класс для освобождения памяти */
  virtual const char *what() const noexcept;

private:
  std::string message_;
};

class InvalidToken : public Exception {
public:
  explicit InvalidToken(const std::string &message) noexcept
      : Exception(message), message_{message} {}
  const char *what() const noexcept override { return message_.c_str(); }

private:
  std::string message_;
};

} // namespace s21