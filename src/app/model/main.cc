#include "object_class/object_class.hpp"

int main() {
  std::string file_name = "../objs/1.obj";
  s21::Object *obj = new s21::Object(file_name);

  obj->ObjectParser();

  // obj->PrintArray();
}