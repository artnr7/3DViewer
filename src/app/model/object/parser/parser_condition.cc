#include "object.h"

namespace s21 {

bool Parser::IsFLine() { return *ofl_it_ == 'f'; }

bool Parser::IsVLine() { return *ofl_it_ == 'v' and *(ofl_it_ + 1) == ' '; }

bool Parser::IsEndOfLine() { return ofl_it_ == eofl_it_; }

bool Parser::IsSlash() { return *ofl_it_ == '/'; }

bool Parser::IsNextSlash() { return *(ofl_it_ + 1) == '/'; }

bool Parser::IsSpace() { return *ofl_it_ == ' '; }

}  // namespace s21
