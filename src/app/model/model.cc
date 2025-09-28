#include "model.hpp"

#include "object_class/object_class.hpp"

std::unique_ptr<s21::Model> s21::Model::instance = nullptr;


std::vector<float> &s21::Model::GetGLVertices() {
  std::cout << "obj-pointer: " << obj_ << std::endl;

  if (obj_ == nullptr) {
    throw std::runtime_error("obj is not initialized");
  }
  obj_->PrintArray();
  return obj_->GetGLVertices();
};

void s21::Model::CreateNewObject(const std::string &obj_filename) {
  obj_filename_ = obj_filename;

  obj_ = std::make_unique<Object>(obj_filename_);
}

void s21::Model::ScaleObject()