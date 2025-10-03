#include "controller.hpp"

#include "../model/model.hpp"
#include "../utils/logger.hpp"

// s21::Controller::Controller(std::string &obj_filename) {
// [[maybe_unused]] s21::Model *model = new Model(obj_filename);
// SetObjFilename(obj_filename);
// }

[[nodiscard]] std::vector<float> *s21::Controller::GetVertices() {
  return s21::Model::GetModel()->GetGLVertices();
}

void s21::Controller::CreateNewObject(const std::string &obj_filename,
                                      const int &w, const int &h) noexcept {
  s21::Logger::Log()->Msg(std::string(__func__) + " Create new object...",
                          Logger::MessageType::Process);
  auto *model = s21::Model::GetModel();
  model->CreateNewObject(obj_filename);
  model->PerspectiveProjectionMatrix(w, h);
  model->SetDefaultLookAt();
}

void s21::Controller::SetPerspective(const int &w, const int &h) {
  s21::Model::GetModel()->PerspectiveProjectionMatrix(w, h);
}

void s21::Controller::SetOrtho() {
  s21::Model::GetModel()->OrthoProjectionMatrix();
}