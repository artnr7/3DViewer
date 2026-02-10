#ifndef MODEL_H_
#define MODEL_H_

#include <QObject>

#include "model_core/model_core.h"
#include "model_core_types.h"
#include "model_types.h"

namespace s21 {

class Model : public QObject {
  Q_OBJECT

 public:
  Model() = default;

 signals:
  void UpdateObjectInfo(ModelUpdateData data);

 public:
  void OpenModelFile(const QString& file_path);

 private:
  ModelUpdateData ConvertData(LoadData);

  /* Fields */
  ModelCore* pimpl_;
};

}  // namespace s21

#endif  // MODEL_H_
