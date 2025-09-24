#include "controller.hpp"

#include "../model/model.hpp"
// s21::Controller::Controller(std::string &obj_filename) {
// [[maybe_unused]] s21::Model *model = new Model(obj_filename);
// SetObjFilename(obj_filename);
// }

[[nodiscard]] std::vector<float> &s21::Controller::GetVertices() {
  s21::Model *model = s21::Model::GetModel();

  return model->GetGLVertices();
}

void s21::Controller::CreateNewObject(
    const std::string &obj_filename) noexcept {
  s21::Model::GetModel()->CreateNewObject(obj_filename);
}
