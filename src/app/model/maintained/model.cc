#include "model.h"
#include "model_core_types.h"

#include <type_traits>
#include <variant>

namespace s21 {

void Model::OpenModelFile(const QString& file_path) {
  LoadData data = pimpl_->OpenModelFile(file_path.toStdString());
  emit UpdateObjectInfo(ConvertData(data));
}

void Model::SetColor(ColorEntity entity, const QColor& color) {
  pimpl_->SetColor(entity, ConvertToRGB(color));
}

ColorRGB Model::ConvertToRGB(const QColor& color) {
  return {
    color.redF(),
    color.greenF(),
    color.blueF()
  };
}

ModelUpdateData Model::ConvertData(LoadData data) {
  return std::visit(
      [](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        ModelUpdateData result;

        if constexpr (std::is_same_v<T, std::string>) {
          result = QString::fromStdString(arg);
        } else {
          result = arg;
        }

        return result;
      },
      data);
}

}  // namespace s21
