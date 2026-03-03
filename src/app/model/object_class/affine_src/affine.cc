#include "object_class.h"

namespace s21 {
void Object::Affine::Translate(const uint8_t shift, float arg) {
  Lg::Log()->Info("Object::Affine" + std::string(__func__));
  // TODO(sundaeka): проверка на размера массива, должен быть минимум 3 и кратен
  // 3
  for (auto it = obj_.glvertices_.begin(); it != obj_.glvertices_.end();
       it += 3) {
    *(it + shift) += arg;
  }
}

void Object::Affine::TranslateX(float x) {
  Lg::Log()->Info("Object::Affine" + std::string(__func__));
  Translate(0, x);
}

void Object::Affine::TranslateY(float y) { Translate(1, y); }
void Object::Affine::TranslateZ(float z) { Translate(2, z); }

void Object::Affine::RotateX() {}

} // namespace s21
