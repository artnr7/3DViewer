#ifndef CONTROLLER_HPP_
#define CONTROLLER_HPP_

#include <qtmetamacros.h>

#include <QObject>
#include <string>
#include <vector>
// #include "spdlog/spdlog.h"

#include "action_types.h"
#include "model.h"

namespace s21 {
class Controller : public QObject {
  Q_OBJECT
 private:
  // Controller() = delete;
  // // explicit Controller(std::string &obj_filename);

 public:
  Controller(Model* model);
  [[nodiscard]] static std::vector<float>& GetVertices();
  static void CreateNewObject(const std::string& obj_filename) noexcept;

 signals:
  // void UpdateObjectInfo(ModelUpdateData data);

 public slots:
  void OnActionTriggered(SceneAction action, ActionData data);

 private:
  void SetupConnections();
  /* Fields */
  Model* model_;
};
}  // namespace s21

#endif
