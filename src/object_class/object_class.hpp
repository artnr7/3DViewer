#include "../model.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace s21 {
class Object {
private:
  std::vector<long double> peaks_;
  std::vector<long double> surface_;
  std::string file_name_;

  void ObjectParser();

public:
  Object() = default;
  Object(std::string &file_name);
};
} // namespace s21