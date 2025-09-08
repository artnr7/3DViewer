#include "controller.hpp"

#include "../model/model.hpp"

std::vector<GLdouble> &s21::Controller::GetVertices() {
  s21::Model *model = s21::Model::GetModel();

  return model->GetGLVertices();
}