#include "object_class.h"

namespace s21 {

bool Object::Parser::IsFLine() { return *ofl_it_ == 'f'; }

bool Object::Parser::IsVLine() {
  return *ofl_it_ == 'v' and *(ofl_it_ + 1) == ' ';
}

bool Object::Parser::IsEndOfLine() { return ofl_it_ == eofl_it_; }

bool Object::Parser::IsSlash() { return *ofl_it_ == '/'; }

bool Object::Parser::IsNextSlash() { return *(ofl_it_ + 1) == '/'; }

bool Object::Parser::IsSpace() { return *ofl_it_ == ' '; }

} // namespace s21
