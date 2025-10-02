#include "model.hpp"

#include <span>
#include <string>

#include "../utils/logger.hpp"
#include "object_class/object_class.hpp"

std::unique_ptr<s21::Model> s21::Model::instance = nullptr;

void s21::Model::CreateNewObject(const std::string &obj_filename) {
  obj_filename_ = obj_filename;

  obj_ = std::make_unique<Object>(obj_filename_);
}

std::vector<float> *s21::Model::GetGLVertices() {
  s21::Logger::Log()->Msg(
      std::string(__func__) + " obj_ pointer = " +
          std::to_string(reinterpret_cast<uintptr_t>(obj_.get())),
      Logger::MessageType::Variable);

  if (obj_ == nullptr) {
    s21::Logger::Log()->Msg("Object in not initialized",
                            Logger::MessageType::Error);
    throw std::runtime_error("obj is not initialized");
  }
  // obj_->PrintArray();
  MatrixCombination();
  return obj_->GetGLVertices();
}
