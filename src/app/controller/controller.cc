#include "controller.h"
#include "action_types.h"
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

void Controller::SetupConnections() {
  connect(model_, &Model::UpdateObjectInfo, this, &Controller::UpdateObjectInfo);
}

/*
 * TODO:
 * 1. Refactor this function
 * 2. Make a log output
 */
void Controller::OnActionTriggered(SceneAction action, ActionData data) {
  std::visit([this, action](auto&& arg) {
    using T = std::decay_t<decltype(arg)>;

    if constexpr (std::is_same_v<T, int>) {
      switch (action) {
        /* Translate */
        case SceneAction::kTranslateX:
          std::cout << "Model move X to: " << arg << "\n";
          break;
        case SceneAction::kTranslateY:
          std::cout << "Model move Y to: " << arg << "\n";
          break;
        case SceneAction::kTranslateZ:
          std::cout << "Model move Z to: " << arg << "\n";
          break;
        /* Rotate */
        case SceneAction::kRotateX:
          std::cout << "Model rotate X to: " << arg << "\n";
          break;
        case SceneAction::kRotateY:
          std::cout << "Model rotate Y to: " << arg << "\n";
          break;
        case SceneAction::kRotateZ:
          std::cout << "Model rotate Z to: " << arg << "\n";
          break;
        /* Scale */
        case SceneAction::kScale:
          std::cout << "Model scale to: " << arg << "\n";
          break;
        /* Vertexes */
        case SceneAction::kVertexSize:
          std::cout << "Vertex size to: " << arg << "\n";
          break;
        /* Edges */
        case SceneAction::kEdgeThickness:
          std::cout << "Edge thickness to: " << arg << "\n";
          break;

        default:
          /* Write Error to log */
          break;
      }
    } else if constexpr (std::is_same_v<T, QString>) {
      switch (action) {
        /* Vertexes */
        case SceneAction::kVertexColor:
          std::cout << "Vertex color to: " << arg << "\n";
          break;
        /* Edges */
        case SceneAction::kEdgeColor:
          std::cout << "Edge color to: " << arg << "\n";
          break;
        /* Open file */
        case SceneAction::kOpenFile:
          std::cout << "File with name: " << arg << "open\n";
          break;

        default:
          /* Write Error to log */
          break;
      }
    } else if constexpr (std::is_same_v<T, ComboBoxData>) {
      switch (action) {

        /* Vertexes */
        case SceneAction::kVertexStyle:
          std::cout << "Vertex style to: " << arg << "\n";
            break;
        /* Edges */
        case SceneAction::kEdgeStyle:
          std::cout << "Edge style to: " << arg << "\n";
          break;

        default:
          /* Write Error to log */
          break;
      }
    }
  }, data);
}

} // namespace s21
