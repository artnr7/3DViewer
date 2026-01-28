#include "controller.h"
#include "model.h"
#include <type_traits>
#include <iostream>

namespace s21 {

// s21::Controller::Controller(std::string &obj_filename) {
// [[maybe_unused]] s21::Model *model = new Model(obj_filename);
// SetObjFilename(obj_filename);
// }

// [[nodiscard]] std::vector<float> &s21::Controller::GetVertices() {
//   return s21::Model::GetModel()->GetGLVertices();
// }

// void Controller::CreateNewObject(
//     const std::string &obj_filename) noexcept {
//   Model::GetModel()->CreateNewObject(obj_filename);
// }
//

Controller::Controller(Model* model)
  : model_(model)
  {
}

void Controller::OnActionTriggered(SceneAction action, ActionData data) {
  std::visit([this, action](auto&& arg) {
    using T = std::decay_t<decltype(arg)>;

    if constexpr (std::is_same_v<T, int>) {
      switch (action) {
        case SceneAction::kTranslateX: std::cout << "Model move X to: " << arg << "\n"; break;
        case SceneAction::kTranslateY: std::cout << "Model move Y to: " << arg << "\n"; break;
        case SceneAction::kTranslateZ: std::cout << "Model move Z to: " << arg << "\n"; break;
      }
    }
  }, data);
}

} // namespace s21
