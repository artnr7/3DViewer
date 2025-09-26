#include "model.hpp"

#include "object_class/object_class.hpp"

std::unique_ptr<s21::Model> s21::Model::instance = nullptr;
// s21::Model::Model(std::string &obj_filename) {
//   obj_filename_ = obj_filename;
//   std::cout << "Haha\n";
//   obj_ = std::make_unique<Object>(obj_filename_);
//   std::cout << "obj-pointer: " << obj_ << std::endl;
// };

s21::Model::Model(const std::string &obj_filename)
    : obj_filename_(obj_filename) {
  obj_ = std::make_unique<s21::Object>(obj_filename_);
}

std::vector<float> &s21::Model::GetGLVertices() {
  std::cout << "obj-pointer: " << obj_ << std::endl;

  if (obj_ == nullptr) {
    throw std::runtime_error("obj is not initialized");
  }
  obj_->PrintArray();
  return obj_->GetGLVertices();
};

// void s21::Model::SetObjFilename(std::string &obj_filename) noexcept {
// obj_filename_ = obj_filename;
// }

void s21::Model::CreateNewObject(const std::string &obj_filename) {
  obj_filename_ = obj_filename;


  obj_ = std::make_unique<Object>(obj_filename_);
}