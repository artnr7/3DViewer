#include "object_class.hpp"

bool s21::Object::IsFLine() { return *ofl_it_ == 'f'; }

bool s21::Object::IsVLine() { return *ofl_it_ == 'v' && *(ofl_it_ + 1) == ' '; }

bool s21::Object::IsEndOfLine() { return ofl_it_ == eofl_it_; }

bool s21::Object::IsSlash() { return *ofl_it_ == '/'; }

bool s21::Object::IsNextSlash() { return *(ofl_it_ + 1) == '/'; }

bool s21::Object::IsSpace() { return *ofl_it_ == ' '; }