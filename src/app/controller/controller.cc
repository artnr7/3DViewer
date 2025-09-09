#include "controller.hpp"

#include "../model/model.hpp"

std::vector<float> &s21::Controller::GetVertices() {
  s21::Model *model = s21::Model::GetModel();

  return model->GetGLVertices();
}